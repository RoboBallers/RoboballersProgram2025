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

    CompassSensor compassSensor;
    PID myPID;

    double max_power; 
    double Setpoint, Input, Output;

    double kp = 0.35;
    double ki = 0;
    double kd = 0.001;

public:
    Movement(Motor& FLMotor, Motor& FRMotor, Motor& BLMotor, Motor& BRMotor);
    void movement(double intended_movement_angle, double speedfactor, double desiredOrientation);
    double findCorrection(double desiredOrientation);
    double CorrectionAngle();
    void circle();
    

};

#endif
