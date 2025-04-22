#include <LineDetection.h>
#include <trig.h>

LineDetection::LineDetection() {
    lineDetected = false;
    sensorAngle = 0;
    adc1.begin(cs1,mosi,miso,sck);
    adc2.begin(cs2,mosi,miso,sck);
    adc3.begin(cs3,mosi,miso,sck);

    // Assuming that sensor 1 on adc 1 is at the front and center of the robot
    for (int i = 0; i < 24; i++) {
        // sensorAngles = [0,15,30,45,60] - think of this as relative to how our robot moves when we put this angle in to movement function
        // if say adc 3 last sensor is front and center, then sensorAngle[0] should be 345, sensorAngle[1] should be 0 and so on - you can gpt a loop for this or something if this issue occurs 
        // this is all assuming that adc 1,2,3 are directly in order with there being 8 sensors of adc1, then right after (clockwise) all sensors of adc 2 and so on - if not just call Prem or figure it out by looking at ballAngle() method in BallFinding.cpp
        sensorAngles[i] = (i * 15) + 7.5;
        // sinValues[i] = sin(sensorAngles[i]);
        cosValues[i] = Trig::Cos(sensorAngles[i]);
    }
    crossLine = false;
    initialAngle = -1;
    linefollow = false;
    correctionValLineFollow = 25;

}

void LineDetection::getSensorValues() {
    for (int i = 0; i < 24; i++) {   
        if (i >= 0 && i <= 2) {
            vals[i] = adc3.analogRead(5+i);
        } else if (i >= 3 && i <= 10) {
            vals[i] = adc1.analogRead(i-3);
        } else if (i >= 11 && i <= 18) {
            vals[i] = adc2.analogRead(i-11);
        } else {
            vals[i] = adc3.analogRead(i-19);
        }
    }

    for (int i = 0; i < 24; i++) {
        if (vals[i] > 1020 || vals[i] < 5) {
            if (i == 0) {
                vals[i] = vals[i+1];
            } else if (i == 23) {
                vals[i] = vals[i-1];
            } else {
            vals[i] = (vals[i+1] + vals[i-1]) / 2;
        }
        }
    }
}


void LineDetection::getIntersectionAngle(int* inputVals) {
    Serial.println("Getting intersection angle");

    for (int i = 0; i < 24; i++) {
        if (vals[i] >  calibrateVals[i]) {
            lineDetectedVals[i] = 1;
            lineDetected = true;
            // Serial.println("Line has been detected");
        } else {
            lineDetectedVals[i] = 0;
        }
    }

    if (!lineDetected) {
        return;
    }

    int theta1 = 0;
    int theta2 = 0;
    double minDotProduct = 2;
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            if (lineDetectedVals[i] == 1 && lineDetectedVals[j] == 1) {
                double dotProduct = Trig::Cos(sensorAngles[j] - sensorAngles[i]);
                if (dotProduct < minDotProduct) {
                    minDotProduct = dotProduct;
                    theta1 = i;
                    theta2 = j;
            }
            }
            
        }
    }
    
    int temp = theta1;
    theta1 = min(theta1, theta2);
    theta2 = max(temp, theta2);



    // Serial.println("The greatest distance between the two sensors that see lines are: " + String(theta1) + " and " + String(theta2));

    if (abs(sensorAngles[theta2] - sensorAngles[theta1]) < 180) {
        intersectionAngle = Trig::avg(sensorAngles[theta1], sensorAngles[theta2]);
        sensorAngle = abs(sensorAngles[theta2] - sensorAngles[theta1]);
    } else {
        double angle1 = sensorAngles[theta1];
        double angle2 = sensorAngles[theta2];

        if (angle1 < angle2) angle1 += 360;
        else angle2 += 360;

        intersectionAngle = Trig::avg(angle1, angle2);
        if (intersectionAngle >= 360) intersectionAngle -= 360;

        sensorAngle = 360 - abs(sensorAngles[theta2] - sensorAngles[theta1]);
    }
    anglebisc = intersectionAngle;


}

double LineDetection::getChord() {
    // diam/maxdiam

    // Maximum chord length is 2 meaning that half of the robot is on the other side of the line
    // 2 means that the greatest distance between sensors that see the lines is 180 degrees
    // Serial.println("Chord length detected: " + String(2 * Trig::Sin(sensorAngle/2)));
    return (2 * Trig::Sin(sensorAngle/2));
}

void LineDetection::sensorsDetectedLine() {
    for (int i = 0; i < 24; i++) {
        if (lineDetectedVals[i] == 1) {
            Serial.println("Sensor " + String(i) + " detected line");
        }
    }
}

double LineDetection::Output() {
    getSensorValues();
    getIntersectionAngle(vals);

    if (lineDetected) {
        double currChord = getChord();
        Serial.print("Chord length: ");
        Serial.println(currChord);

        // if (currChord >= chordThreshold  && abs(prevChord - currChord) > chordDifferenceThres) {
        if (currChord >= chordThreshold) {
            crossLine = true;
        }

        if (crossLine) {
            avoidanceAngle = anglebisc;  
        } else {
            avoidanceAngle = anglebisc + 180;
            if (avoidanceAngle >= 360) {
                avoidanceAngle -= 360;
            }
        }

        // Serial.print("Avoidance Angle: ");
        Serial.println(avoidanceAngle);

        lineDetected = false;

        prevChord = currChord;
    } else {
        crossLine = false;
        initialAngle = -1;
        avoidanceAngle = -1;

        // Serial.println("No line detected — state reset");
    }

     if (crossLine) {
        Serial.println("Crossline is TRUE");
    } else {
        Serial.println("Crossline is FALSE");
    }


    angleDiff = 0;
    return avoidanceAngle;
}