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

MCP3008 adc2;


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
  adc2.begin(37,11,12,13);

  Serial.begin(9600);
}

void loop() {
  // if (!switches.isCalibrate()) {
  //   countCalibrate = 0;
  // } else {
  //   countCalibrate++;
  //   if (countCalibrate == 0) {
  //     DirectionSensor.callibrate();
  //   }
  //   DirectionSensor.zeroedAngle = DirectionSensor.getOrientation();
  // }

  
  // if (line.lineDetected) {
  //   move.movement(line.Output(), 1);
  // } else {
  //   move.movement(ballFinding.orbit(), 1);
  // }
  // Serial.println(ballFinding.ballAngle());
  Serial.println(adc2.analogRead(3));
  delay(100);
  // Serial.println("Hello World");
}

