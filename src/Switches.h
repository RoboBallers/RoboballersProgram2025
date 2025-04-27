#ifndef SWITCHES_H
#define SWITCHES_H

class Switches {
    public:
    Switches();
    bool isCompassCalibration();
    bool isCalibrateLine();
    bool isStart();

    private:
    int startPin = 27;
    int comapssCalibrationPin = 29;
    int calibrateLinePin = 28;

};

#endif // SWITCHES_H