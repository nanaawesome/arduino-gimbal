#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);

Servo servo_yaw;  // create servo object to control a servo
Servo servo_pitch;
Servo servo_roll;

void setup() {
  servo_yaw.attach(3);  
  servo_pitch.attach(5);  
  servo_roll.attach(6);  

  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
    mpu.update();
    int servo0Value = map(mpu.getAngleZ(), -90, 90, 180, 0);
    int servo1Value = map(mpu.getAngleX(), -90, 90, 180, 0);
    int servo2Value = map(mpu.getAngleY(), -90, 90, 180, 0);

    servo_yaw.write(servo0Value);
    servo_pitch.write(servo1Value);
    servo_roll.write(servo2Value);
  
}
