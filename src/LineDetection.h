#ifndef LINEDETECTION_H
#define LINEDETECTION_H
#include <Arduino.h>
#include <MCP3XXX.h>

class LineDetection {
public:
    LineDetection();
    int* getSensorValues();

private:
    MCP3008 adc1;
    MCP3008 adc2;
    MCP3008 adc3;
    MCP3008 adc4;
    MCP3008 adc5;
    MCP3008 adc6;
    int sensorVals[48];
    double sinValues[48];
    double cosValues[48];
    int cs1 = 30;
    int cs2 = 29;
    int cs3 = 28;
    int sck = 35;
    int mosi = 13;
    int miso = 14;
};

#endif // LINEDETECTION_H
