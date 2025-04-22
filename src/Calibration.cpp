#include <Calibration.h>
#include <math.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <Movement.h>

Calibration::Calibration(LineDetection& lineDetection)
    : lineDetection(lineDetection) {
}


void Calibration::calibrateLineSensors() {
    lineDetection.getSensorValues();
    for (int i = 0; i < 24; i++) {
        lineDetection.calibrateVals[i] = fmax(lineDetection.calibrateVals[i],lineDetection.vals[i] * 1.5);
    }
}