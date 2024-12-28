#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Motor.h>
#include <CompassSensor.h>

class Movement {
private:
    Motor *FLMotor;
    Motor *FRMotor;
    Motor *BLMotor;
    Motor *BRMotor;

    double speedfactor = 1;
    double max_power; 

    CompassSensor *compass;

public:
    Movement(Motor *FLMotor, Motor *FRMotor, Motor *BLMotor, Motor *BRMotor);
    void movement(double degrees, double orientation);
    double orbit(double degrees);
    

};

#endif // MOVEMENT_H
