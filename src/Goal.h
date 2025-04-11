#ifndef GOAL_H
#define GOAL_H

class Goal {
    public:
        Goal();
        double retrieveAngle();
        double AngleToMovetoGoal();
        void score();
        void beginCamera();
        void requestColor(char c);
    private:
        int kickerPin = 26;
  

        
};

#endif GOAL_H
