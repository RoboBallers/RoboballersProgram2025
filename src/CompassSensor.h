#ifndef COMPASSSENSOR_H
#define COMPASSSENSOR_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class CompassSensor {
    public:
    CompassSensor();
    void callibrate();
    int getOrientation();
    int currentOffset();
    double zeroedAngle;

    private:
    Adafruit_BNO055 bno;
    sensors_event_t event;
};
#endif // COMPASSSENSOR_H