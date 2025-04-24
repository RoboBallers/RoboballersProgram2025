#ifndef BALLFINDING_H
#define BALLFINDING_H

#include <MCP3XXX.h>

class BallFinding {
    public:
    BallFinding();
    double ballAngle();
    double orbit(double ballAngle);
    double irDistance(int val);
    double ballDistance();
    double circleIntersection();
    int sensorVals[24];


    private:
    // Note need to change the chip selector pins to ensure that the ir sensor and line sensor r different
    int cs1 = 38;
    int cs2 = 37;
    int cs3 = 36;
    int sck = 13;
    int mosi = 11;
    int miso = 12;
    MCP3008 adc4;
    MCP3008 adc5;
    MCP3008 adc6;
    double sinValues[24];
    double cosValues[24];

};

#endif // BALLFINDING_H