#ifndef BALLFINDING_H
#define BALLFINDING_H

#include <MCP3XXX.h>

class BallFinding {
    public:
    BallFinding();
    double ballAngle();
    double orbit();

    private:
    // Note need to change the chip selector pins to ensure that the ir sensor and line sensor r different
    int cs1 = 30;
    int cs2 = 29;
    int cs3 = 28;
    int sck = 35;
    int mosi = 13;
    int miso = 14;
    MCP3008 adc4;
    MCP3008 adc5;
    MCP3008 adc6;
    int sensorVals[48];
    double sinValues[48];
    double cosValues[48];

};

#endif // BALLFINDING_H