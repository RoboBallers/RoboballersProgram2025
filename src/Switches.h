#ifndef SWITCHES_H
#define SWITCHES_H

class Switches {
    public:
    Switches();
    bool isBlue();
    // bool isStart();
    bool isCalibrateAngle();
    bool isCalibrateLine();
    bool isStart();

    private:
    int startPin = 27;
    int bluePin = -1;
    int calibrateAnglePin = 29;
};

#endif // SWITCHES_H