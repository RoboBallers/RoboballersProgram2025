#ifndef LINEDETECTION_H
#define LINEDETECTION_H
#include <Arduino.h>
#include <MCP3XXX.h>
#include <Calibration.h>

class LineDetection {
public:
    LineDetection();
    void getSensorValues();
    void getIntersectionAngle(int* calibrateVal, int* sensorVals);
    double Output();
    double getChord();
    bool lineDetected;
    bool startLineFollow();


private:
    MCP3008 adc1;
    MCP3008 adc2;
    MCP3008 adc3;

    // Calibration *cal;

    int sensorVals[48];
    double sinValues[48];
    double cosValues[48];
    int sensorAngles[48];
    double sensorAngle;
    int cs1 = 30;
    int cs2 = 29;
    int cs3 = 28;
    int sck = 35;
    int mosi = 13;
    int miso = 14;
    bool crossLine;
    double intersectionAngle;
    double initialAngle;
    double currentAngle;
    double angleDiff;
    bool linefollow;
    double correctionValLineFollow;
    double chordThreshold = 0.85;
    int vals[24];
};

#endif // LINEDETECTION_H
