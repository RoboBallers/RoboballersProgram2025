#include <LineDetection.h>
#include <trig.h>
#include <tuple>

LineDetection::LineDetection() {
    // uint8_t csPin, uint8_t mosiPin, uint8_t misoPin, uint8_t sckPin
    lineDetected = false;
    sensorAngle = 0;
    adc1.begin(cs1,mosi,miso,sck);
    adc2.begin(cs2,mosi,miso,sck);
    adc3.begin(cs3,mosi,miso,sck);

    // Assuming that sensor 1 on adc 1 is at the front and center of the robot
    for (int i = 0; i < 24; i++) {
        sensorAngles[i] = i * 15;
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
        int adcnum = i / 8;
        int channel  = i%8;

        switch (adcnum) {
            case 0:
                vals[i] = adc1.analogRead(channel);
                break;
            case 1:
                vals[i] = adc2.analogRead(channel);
                break;
            case 2:
                vals[i] = adc3.analogRead(channel);
                break;
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


void LineDetection::getIntersectionAngle(int* calibrateVal, int* sensorVals) {
    for (int i = 0; i < 24; i++) {
        if (sensorVals[i] > calibrateVal[i]) {
            sensorVals[i] = 1;
            lineDetected = true;
        } else {
            sensorVals[i] = 0;
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
            if (sensorVals[i] == 1 && sensorVals[j] == 1) {
                double dotProduct = Trig::Cos(j * 15 - i * 15);
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

    if (theta2 - theta1 < 180) {
        intersectionAngle = Trig::avg(theta1, theta2);
        sensorAngle = theta2-theta1;
    } else {
        intersectionAngle = Trig::avg(theta1, theta2 - 360);
        sensorAngle = (360-(theta2 - theta1));
    }

}

double LineDetection::getChord() {
    // diam/maxdiam
    return (2 * Trig::Sin(sensorAngle/2));
}



double LineDetection::Output() {
    if (lineDetected) {
        // getIntersectionAngle(cal->calibrateVal, getSensorValues());
        if (linefollow) {
            if ((crossLine && (getChord() < chordThreshold)) ) {
                if (getChord() < 1) {
                    return -correctionValLineFollow;
                } else {
                    return correctionValLineFollow;
                }
            }
        } else {
            if (initialAngle == -1) {
            initialAngle = intersectionAngle;
            }
            currentAngle = intersectionAngle;
            angleDiff = abs(currentAngle - initialAngle);
            initialAngle = currentAngle;
            if (angleDiff > 180) {
                angleDiff = 360 - angleDiff;
            }
            if (angleDiff > 100 && !crossLine) {
                crossLine = true;
                angleDiff = 0;
            }
            if (crossLine) {
                intersectionAngle += 180;
                if (intersectionAngle > 360) {
                    intersectionAngle -= 360;
                }
                if (angleDiff > 100) {
                    crossLine = false;
                }
            }
        }
    } else {
        crossLine = false;
        initialAngle = -1;
        intersectionAngle = -1;
    }

    angleDiff = 0;
    return intersectionAngle;
}