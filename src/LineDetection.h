#ifndef LINEDETECTION_H
#define LINEDETECTION_H
#include <Arduino.h>
#include <MCP3XXX.h>
#include <Calibration.h>

class LineDetection {
public:
    LineDetection();
    void getSensorValues();
    void getIntersectionAngle(int* sensorVals);
    double Output();
    double getChord();
    bool lineDetected;
    bool startLineFollow();
    int vals[24];
    double intersectionAngle;
    int calibrateVals[24];
    int lineDetectedVals[24];
    void sensorsDetectedLine();
    bool crossLine;
    bool lineDetectedFunc();
    double minChordLength = 0.4;




    private:
        MCP3008 adc1;
        MCP3008 adc2;
        MCP3008 adc3;


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
        double initialAngle;
        double currentAngle;
        double angleDiff;
        bool linefollow;
        double correctionValLineFollow;
        double chordThreshold = 1.97; // change to 1.85?
        int avoidanceAngle = -1;
        double anglebisc = -1;
        double prevChord = -1;
        double currChord = -1;
    // double chordDifferenceThres = 0.1;
};

#endif // LINEDETECTION_H
