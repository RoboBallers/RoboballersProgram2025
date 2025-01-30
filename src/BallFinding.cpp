#include <BallFinding.h>
#include <trig.h>

BallFinding::BallFinding() {
    adc4.begin(cs1,mosi,miso,sck);
    adc5.begin(cs2,mosi,miso,sck);
    adc6.begin(cs3,mosi,miso,sck);
}

double BallFinding::ballAngle() {
    int vals[24];
    double totalCos = 0;
    double totalSin = 0;

    for (int i = 0; i < 24; i++) {
        int adcnum = i / 8;
        int channel  = i%8;

        switch (adcnum) {
            case 0:
                vals[i] = adc4.analogRead(channel);
                break;
            case 1:
                vals[i] = adc5.analogRead(channel);
                break;
            case 2:
                vals[i] = adc6.analogRead(channel);
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

    for (int i = 0; i < 24; i++) {
        totalCos += (-vals[i] * Trig::Cos(i * 15));
        totalSin += (-vals[i] * Trig::Sin(i * 15));
    }

    double ballAngle = Trig::toDegrees(atan2(totalSin, totalCos));
    
     if (ballAngle < 0) {
        ballAngle += 360;
    }

    ballAngle = 360 - ballAngle;

    return ballAngle;
}

double BallFinding::orbit() {
    double orbit_val = 0;
    double ballAngle = BallFinding::ballAngle();

     if (ballAngle>80 && ballAngle<280) {
        orbit_val = 180;
        if (ballAngle>170 && ballAngle<190) {
            orbit_val = 90;
        }
    }

    // if ball is right in front of the robot
    else if (355 < orbit_val && orbit_val < 5) {
        orbit_val = 0;
    }
    // if the ball is in the second quadrant
    else if (ballAngle > 270) {
        ballAngle = 360-ballAngle;
        orbit_val = -min(110,1.4*exp(0.2*ballAngle));
        orbit_val += 360;
    }
    else {
        orbit_val = min(110,1.4*exp(0.2*ballAngle));
    }

    return orbit_val;

    // add in dampen
}