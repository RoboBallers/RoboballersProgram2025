#include <BallFinding.h>
#include <trig.h>

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

double BallFinding::orbit(double ballAngle) {
    double orbit_val = 0;

     if (ballAngle>80 && ballAngle<280) {
        if (ballAngle > 160 && ballAngle < 180) {
            orbit_val = 210;
        } else if (ballAngle > 180 && ballAngle < 200) {
            orbit_val = 150;
        } else {
            orbit_val = 180;
        }
    }
    // if ball is right in front of the robot 
    else if (350 < ballAngle || ballAngle < 10) {
        orbit_val = 0;
    } 
    // tune these values
    // -> closer to 80 should be closer to 100 or 105 or 110
    else if (ballAngle > 10 && ballAngle < 70) { 
        orbit_val = 90;
    } 
    else if (ballAngle > 310 && ballAngle < 350) {
        orbit_val = 270;
    }
    // if the ball is in the second quadrant
    else if (ballAngle > 270) {
        ballAngle = 360-ballAngle;
        orbit_val = -min(110,1.4*exp(0.35*ballAngle)); // old 0.2
        orbit_val += 360;
    }
    else {
        orbit_val = min(110,1.4*exp(0.35*ballAngle));
    }

    return orbit_val;

    // add in dampen
}