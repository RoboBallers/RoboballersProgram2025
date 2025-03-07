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
    int vals[24];



private:
    MCP3008 adc1;
    MCP3008 adc2;
    MCP3008 adc3;

    // Calibration *cal;

    int sensorVals[24];
    double sinValues[24];
    double cosValues[24];
    int sensorAngles[24];
    double sensorAngle;
    int cs1 = 33;
    int cs2 = 34;
    int cs3 = 35;
    int sck = 13;
    int mosi = 11;
    int miso = 12;
    bool crossLine;
    double intersectionAngle;
    double initialAngle;
    double currentAngle;
    double angleDiff;
    bool linefollow;
    double correctionValLineFollow;
    double chordThreshold = 0.85;
};

#endif // LINEDETECTION_H
