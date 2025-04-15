#include <Calibration.h>
#include <math.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <Movement.h>

Calibration::Calibration(LineDetection& lineDetection, CompassSensor& compassSensor, Movement& movement) 
: lineDetection(lineDetection), compassSensor(compassSensor), movement(movement) {
}


void Calibration::calibrateLineSensors() {
    lineDetection.getSensorValues();
    for (int i = 0; i < 24; i++) {
        calibrateVal[i] = fmax(calibrateVal[i],lineDetection.vals[i]+40);
    }
    movement.circle();
}

void Calibration::calibrateCompassSensor() {
    compassSensor.zeroedAngle = compassSensor.getOrientation();
}