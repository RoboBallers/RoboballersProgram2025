#include <LineDetection.h>

LineDetection::LineDetection() {
    // uint8_t csPin, uint8_t mosiPin, uint8_t misoPin, uint8_t sckPin
    int sensorVals[24];
    adc1.begin(cs1,mosi,miso,sck);
    adc2.begin(cs2,mosi,miso,sck);
    adc3.begin(cs3,mosi,miso,sck);

}

int* LineDetection::getSensorValues() {
    int* vals = new int[24];

    for (int i = 0; i < 24; i++) {
        int adcnum = i / 8;
        int channel  = i%8;

        switch (adcnum) {
            case 0:
                vals[i] = adc1.analogRead(channel);
                break;
            case 1:
                vals[i] = adc2.analogRead(channel);
                break;
            case 2:
                vals[i] = adc3.analogRead(channel);
                break;
            case 3:
                vals[i] = adc4.analogRead(channel);
                break;
            case 4:
                vals[i] = adc5.analogRead(channel);
                break;
            case 5:
                vals[i] = adc6.analogRead(channel);
                break;
        }   

    }

    for (int i = 0; i < 24; i++) {
        if (vals[i] > 1020 || vals[i] < 5) {
            if (i == 0) {
                vals[i] = vals[i+1];
            } else if (i == 23) {
                vals[i] = vals[i-1];
            } else {
            vals[i] = (vals[i+1] + vals[i-1]) / 2;
        }
        }
    }

    return vals;

}