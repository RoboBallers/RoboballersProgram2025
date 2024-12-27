#include <CompassSensor.h>
#include <Wire.h>

CompassSensor::CompassSensor() {
    // Both 0x29 and 0x28 are slave, does it matter what we use?
    bno = Adafruit_BNO055(55, 0x29, &Wire);
    if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

void CompassSensor::callibrate() {
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    while (mag<3) {
        Serial.print("Mag: ");
        Serial.print(mag);
        Serial.println("/3");
        delay(500);
        bno.getCalibration(&system, &gyro, &accel, &mag);
    }
}

int CompassSensor::getOrientation() {
    bno.getEvent(&event);
    return event.orientation.x;
}