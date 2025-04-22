#ifndef Calibration_H
#define Calibration_H

// Forward declarations instead of includes
class LineDetection;  // Forward declaration
class CompassSensor;  // Forward declaration

class Calibration {
    public:
        Calibration(LineDetection& lineDetection);
        void calibrateLineSensors(); 
        void calibrateCompassSensor();
        int calibrateVal[24];
    private:
        LineDetection& lineDetection;
};

#endif // Calibration_H
