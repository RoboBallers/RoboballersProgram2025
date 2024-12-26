#include <CompassSensor.h>

#include <Wire.h>
// https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/2524/SEN0140_Web.pdf?_gl=1*1ede07m*_up*MQ..*_gs*MQ..&gclid=CjwKCAiAmrS7BhBJEiwAei59i-Luoc5CZYHogxVixjw9irO8tuZnK75sG2ziE49FmObDTnte4KsJ2xoCUw8QAvD_BwE&gclsrc=aw.ds
// #include <FreeSixIMU.h>
// #include <FIMU_ADXL345.h>
// #include <FIMU_ITG3200.h>
// #include <HMC5883L.h>
// float angles[3]; // yaw pitch roll
// float heading;
// short temperature;
// long pressure;
// // Set the FreeSixIMU object
// FreeSixIMU sixDOF = FreeSixIMU();
// HMC5883L compass;
// // Record any errors that may occur in the compass.
// int error = 0;
// void setup(){
//  Serial.begin(9600);
//  Wire.begin();
//  delay(5);
//  sixDOF.init(); //init the Acc and Gyro
//  delay(5);
//  compass = HMC5883L(); // init HMC5883 