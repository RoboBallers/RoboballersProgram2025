#include <Arduino.h>
#include <Motor.h>
#include <Movement.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <BallFinding.h>
#include <Switches.h>
#include <Goal.h>

const int FLIN1 = 2;
const int FLIN2 = 3;
const int FLEnable = 24;

const int FRIN1 = 4;
const int FRIN2 = 5;
const int FREnable = 25;

const int BRIN1 = 6;
const int BRIN2 = 9;
const int BREnable = 22;

const int BLIN1 = 31;
const int BLIN2 = 32;
const int BLEnable = 23;

double OffsetedOrientation = 0;
int countCalibrate = 0;



BallFinding ballFinding;
CompassSensor compassSensor;
Switches switches;
LineDetection linedetection;
Goal goal;
Motor FL(FLIN1, FLIN2, FLEnable);
Motor FR(FRIN1, FRIN2, FREnable);
Motor BL(BLIN1, BLIN2, BLEnable);
Motor BR(BRIN1, BRIN2, BREnable);
// Movement movement(FL, FR, BL, BR,compassSensor);


// Movement move(&FLMotor, &FRMotor, &BLMotor, &BRMotor);
// LineDetection line;
// CompassSensor DirectionSensor;
// BallFinding ballFinding;
// Switches switches;

void setup() {
  // put your setup code here, to run once:
  pinMode(FLIN1, OUTPUT);
  pinMode(FLIN2, OUTPUT);
  pinMode(FLEnable, OUTPUT);

  pinMode(FRIN1, OUTPUT);
  pinMode(FRIN2, OUTPUT);
  pinMode(FREnable, OUTPUT);

  pinMode(BLIN1, OUTPUT);
  pinMode(BLIN2, OUTPUT);
  pinMode(BLEnable, OUTPUT);

  pinMode(BRIN1, OUTPUT);
  pinMode(BRIN2, OUTPUT);
  pinMode(BREnable, OUTPUT);

  Serial.begin(9600);
  // goal.beginCamera();

  

  // compassSensor.callibrate();
}

void testingballSensors() {
  double ballAngle = ballFinding.ballAngle();
  Serial.println("Ball Angle: " + String(ballAngle));
  for (int i = 0; i < 24; i++) {
    Serial.println("Sensor " + String(i) + String(" ") + String(ballFinding.sensorVals[i]));
  }
}

void testingLineSensors() {
  linedetection.getSensorValues();
  for (int i = 0; i < 24; i++) {
    Serial.println("Sensor " + String(i) + String(" ") + String(linedetection.vals[i]));
  }
}

void testingCompass() {
  Serial.println("Current Desired Angle is " + String(compassSensor.zeroedAngle));
  Serial.println("Current offset is: " + String(compassSensor.currentOffset()));
}

void testingSensors() {
  testingballSensors();
  Serial.println("LINE SENSORS");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println();
  testingLineSensors();

  Serial.println("IR SENSORS");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println();
 
}

void testingMotors() {
  FL.setSpeed(0.2);
  delay(200);
  FR.setSpeed(0.2);
  delay(200);
  BL.setSpeed(0.2);
  delay(200);
  BR.setSpeed(0.2);
  delay(200);
}

void loop() {
  if (switches.isCalibrateAngle()) {
    compassSensor.zeroedAngle = compassSensor.getOrientation();
  }

  // digitalWrite(FLIN1, HIGH);
  // digitalWrite(FLIN2, LOW);
  // analogWrite(FLEnable, 200);

  // digitalWrite(FRIN1, HIGH);
  // digitalWrite(FRIN2, LOW);
  // analogWrite(FREnable, 200);

  // digitalWrite(BRIN1, HIGH);
  // digitalWrite(BRIN2, LOW);
  // analogWrite(BREnable, 200);

  digitalWrite(BLIN1, HIGH);
  digitalWrite(BLIN2, LOW);
  analogWrite(BLEnable, 200);


  // testingMotors();
  // BL.setSpeed(0.7);
  // movement.movement(0,0.2);

  // delay(500);




  
  // if (line.lineDetected) {
    // move.movement(line.Output(), 1);
  // } else {
  //   move.movement(ballFinding.orbit(), 1);
  // }
 
}

