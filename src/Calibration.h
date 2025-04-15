#ifndef Calibration_H
#define Calibration_H

class Calibration {
    public:
        Calibration(LineDetection& lineDetection, CompassSensor& compassSensor, Movement& movement);
        void calibrateLineSensors(); 
        void calibrateCompassSensor();
        int calibrateVal[24];
    private:
        LineDetection& lineDetection;
        CompassSensor& compassSensor;
        Movement& movement;

};

#endif // Calibration_H