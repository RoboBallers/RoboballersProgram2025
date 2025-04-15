#ifndef SWITCHES_H
#define SWITCHES_H

class Switches {
    public:
    Switches();
    bool isBlue();
    bool isCalibrateAngle();
    bool isCalibrateLine();
    bool isStart();

    private:
    int startPin = 27;
    int bluePin = 28;
    int calibrateAnglePin = 29; //Compass sensor
    int calibrateLinePin = 28;

};

#endif // SWITCHES_H