#include <Goal.h>
#include <Arduino.h>

Goal::Goal() {

}

void Goal::beginCamera() {
    Serial2.begin(9600); 
}

void Goal::requestColor(char color) {
    Serial2.write(color);
}


double Goal::retrieveAngle() {
    double value = 0.0;
    uint8_t *data = reinterpret_cast<uint8_t *>(&value);

    if (Serial2.available() >= sizeof(double)) {
        for (size_t i = 0; i < sizeof(double); i++) {
            data[i] = Serial2.read();
        }
        return value;
    }

    Serial.println("ERROR: COULD NOT READ FROM OPENMV");
    return 0.0;
}
