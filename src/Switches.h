// 19 - start
// 20 - blue
// 21 - calibrate
#ifndef SWITCHES_H
#define SWITCHES_H

class Switches {
    public:
    Switches();
    bool isBlue();
    bool isStart();
    bool isCalibrate();

    private:
    int startPin = 19;
    int bluePin = 20;
    int calibratePin = 21;
};

#endif // SWITCHES_H