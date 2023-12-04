#include <Arduino.h>
#include <esp32_motor.hpp>
#include <Wire.h>
#include <MPU6050.h>
// #include <SimpleKalmanFilter.h>
#include <BluetoothSerial.h>

MPU6050 imu;
int16_t ax, ay, gz;
float accelX, accelY, gyroZ;
// float speedX=0, speedY=0;

#define aScale 16384.0
#define gScale 131.0


void task2(void *param);
void getMotion() {
    gz = imu.getRotationZ();
    gyroZ = gz/gScale;
}

void init_task2() {
    xTaskCreatePinnedToCore(
    task2,
    "Task2",
    10000,
    NULL,
    1,
    NULL,
    0        
    );
}

void straghtRun(esp32_motor firstMotor, esp32_motor secondMotor, int8_t dir) {
    firstMotor.RunPercentage(dir?-100:100);
    secondMotor.RunPercentage(dir?100:-100);
}