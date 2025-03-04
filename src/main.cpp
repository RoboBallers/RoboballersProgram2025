#include <Arduino.h>
#include <Motor.h>
#include <Movement.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <BallFinding.h>
#include <Switches.h>

#define FLIN1 1
#define FLIN2 2
#define FLEnable 9

#define FRIN1 3
#define FRIN2 4
#define FREnable 10

#define BLIN1 5
#define BLIN2 6
#define BLEnable 11

#define BRIN1 7
#define BRIN2 8
#define BREnable 12

double OffsetedOrientation = 0;
int countCalibrate = 0;

// Motor FLMotor(FLIN1, FLIN2, FLEnable);
// Motor FRMotor(FRIN1, FRIN2, FREnable);
// Motor BLMotor(BLIN1, BLIN2, BLEnable);
// Motor BRMotor(BRIN1, BRIN2, BREnable);

BallFinding ballFinding;
CompassSensor compassSensor;
Switches switches;


// Movement move(&FLMotor, &FRMotor, &BLMotor, &BRMotor);
// LineDetection line;
// CompassSensor DirectionSensor;
// BallFinding ballFinding;
// Switches switches;

void setup() {
  // put your setup code here, to run once:
  // pinMode(FLIN1, OUTPUT);
  // pinMode(FLIN2, OUTPUT);
  // pinMode(FLEnable, OUTPUT);

  // pinMode(FRIN1, OUTPUT);
  // pinMode(FRIN2, OUTPUT);
  // pinMode(FREnable, OUTPUT);

  // pinMode(BLIN1, OUTPUT);
  // pinMode(BLIN2, OUTPUT);
  // pinMode(BLEnable, OUTPUT);

  // pinMode(BRIN1, OUTPUT);
  // pinMode(BRIN2, OUTPUT);
  // pinMode(BREnable, OUTPUT);

  Serial.begin(9600);

  compassSensor.callibrate();
}

void testingballSensors() {
  double ballAngle = ballFinding.ballAngle();
  Serial.println("Ball Angle: " + String(ballAngle));
  for (int i = 0; i < 24; i++) {
    Serial.println("Sensor " + String(i) + String(" ") + String(ballFinding.sensorVals[i]));
  }
}

void testingCompass() {
  Serial.println("Current Desired Angle is " + String(compassSensor.zeroedAngle));
  Serial.println("Current offset is: " + String(compassSensor.currentOffset()));
}

void loop() {
  if (switches.isCalibrateAngle()) {
    compassSensor.zeroedAngle = compassSensor.getOrientation();
  }

 
  delay(300);

  
  // if (line.lineDetected) {
    // move.movement(line.Output(), 1);
  // } else {
  //   move.movement(ballFinding.orbit(), 1);
  // }
 
}

