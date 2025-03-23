#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Motor.h>
#include <CompassSensor.h>
#include <PID_v1.h>

class Movement {
private:
    Motor FLMotor;
    Motor FRMotor;
    Motor BLMotor;
    Motor BRMotor;

    CompassSensor& DirectionSensor;
    PID myPID;

    double max_power; 
    double Setpoint, Input, Output;

    double kp = 0.35;
    double ki = 0;
    double kd = 0.001;

public:
    Movement(Motor& FLMotor, Motor& FRMotor, Motor& BLMotor, Motor& BRMotor, CompassSensor& sensor);
    void movement(double degrees, double speed_factor);
    double findCorrection(double orientationOffsetFix);
    double CorrectionAngle();
    

};

#endif
