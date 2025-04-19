#ifndef GOAL_H
#define GOAL_H
#include <elapsedMillis.h>
#include <CompassSensor.h>

class Goal {
    public:
        Goal(CompassSensor& CompassSensor);
        double retrieveAngle();
        double AngleToMovetoGoal();
        void score();
        void beginCamera();
        void sendColor(char c);
        bool haveBall();
    private:
        CompassSensor& compassSensor;
        int kickerPin = 26;
        int lightGate = 10;
        elapsedMillis timer;
        elapsedMillis active;
        int kickHold = 1000;
  

        
};

#endif // GOAL_H
