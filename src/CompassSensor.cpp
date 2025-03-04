#include <CompassSensor.h>
#include <Wire.h>

CompassSensor::CompassSensor() {
    Wire.begin();
    bno = Adafruit_BNO055(55, 0x28, &Wire);
    if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  } else {
    Serial.print("Successful");
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

int CompassSensor::currentOffset() {
  int currentOrientation = getOrientation();
  int offset = currentOrientation - zeroedAngle;

  if (offset < -180) {
    return offset + 360;  // Wrap around from negative to positive angle
  } else if (offset > 180) {
    return offset - 360;  // Wrap around from positive to negative angle
  } else {
    return offset;  // Offset is within the normal range (-180 to 180)
  }
}
