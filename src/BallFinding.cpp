#include <BallFinding.h>
#include <trig.h>
#include <Circle.h>

BallFinding::BallFinding() {
    adc4.begin(cs1,mosi,miso,sck);
    adc5.begin(cs2,mosi,miso,sck);
    adc6.begin(cs3,mosi,miso,sck);
}

double BallFinding::ballAngle() {
    double totalCos = 0;
    double totalSin = 0;

    for (int i = 0; i < 24; i++) {
        int adcnum = i / 8;
        int channel  = i%8;

        switch (adcnum) {
            case 0:
                sensorVals[i] = adc4.analogRead(7-channel);
                break;
            case 1:
                sensorVals[i] = adc5.analogRead(7-channel);
                break;
            case 2:
                sensorVals[i] = adc6.analogRead(7-channel);
                break;
        }   

    }

    for (int i = 0; i < 24; i++) {
        if (sensorVals[i] > 1020 || sensorVals[i] < 5) {
            if (i == 0) {
                // Serial.println("Finding average of sensor 0");
                sensorVals[i] = (sensorVals[23] + sensorVals[1]) / 2;
            } else if (i == 23) {
                sensorVals[i] = (sensorVals[0] + sensorVals[22]) / 2;
            } else {
            sensorVals[i] = (sensorVals[i+1] + sensorVals[i-1]) / 2;
            }
        }

        sensorVals[15] = Trig::avg(sensorVals[14], sensorVals[16]);
    }

    // Front and Center is on the side of the main switch and battery
    for (int i = 0; i < 24; i++) {
        totalCos += (sensorVals[i] * Trig::Cos(i * 15));
        totalSin += (sensorVals[i] * Trig::Sin(i * 15));
    }

    // Serial.println("Total Cos" + String(totalCos));
    // Serial.println("Total Sin" + String(totalSin));

    double ballAngle = Trig::toDegrees(atan2(totalSin, totalCos));
    
     if (ballAngle < 0) {
        ballAngle += 360;
    }

    // ballAngle = (360-ballAngle);

    ballAngle += 180;

    if (ballAngle > 360) {
        ballAngle -= 360;
    }


    return ballAngle;
}

double BallFinding::irDistance(int val) {
    return (6.99 * pow(0.99, val));
}

double BallFinding::ballDistance() {
   std::vector<std::pair<int, int>> valWithIndex;

    for (int i = 0; i < 24; i++) {
        valWithIndex.push_back({sensorVals[i], i});
    }

    std::sort(valWithIndex.begin(), valWithIndex.end());

    int angle1 = valWithIndex[0].second * 15;
    int angle2 = valWithIndex[1].second * 15;

    auto [x0, y0, r0] = convertToStandard(-11 * Trig::Cos(angle1), -11 * Trig::Sin(angle2), irDistance(valWithIndex[0].first));
    auto [x1, y1, r1] = convertToStandard(-11 * Trig::Cos(angle2), -11 * Trig::Sin(angle2), irDistance(valWithIndex[0].first));

    auto points = circleIntersections(x0, y0, r0, x1, y1, r1);

    double dist1 = (pow(points[0].x,2) + pow(points[0].y,2));
    double dist2 = (pow(points[1].x,2) + pow(points[1].y,2));

    return min(dist1, dist2);
}

double BallFinding::orbit(double ballAngle) {
    double orbit_val = 0;

    // if ball is right in front of the robot
    if (350 < ballAngle || ballAngle < 10) {
        orbit_val = 0;
    } else {
        orbit_val = ballAngle + exp(-0.06 * (ballDistance() - 90));
        if (orbit_val > 360) {
            orbit_val -= 360;
        }
        orbit_val = min(90,orbit_val);
    }

    return orbit_val;
}