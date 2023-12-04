#include <main.hpp>

esp32_motor leftMotor(25,33,2,3,10000,12);
esp32_motor rightMotor(27,26,4,5,10000,12);
esp32_motor backMotor(18,19,6,7,10000,12);
// SimpleKalmanFilter kf();
BluetoothSerial SerBT;

void setup() {
    SerBT.begin("OmniTriple");
    Wire.begin();
    // imu.initialize();
    leftMotor.init();
    rightMotor.init();
    backMotor.init();
    Serial.begin(115200);
    // imu.CalibrateGyro();
    init_task2();
}
long unsigned timer = micros(), deltaTime;
char cmd;
void loop() {
    if (SerBT.available()) {
        cmd = SerBT.read();
        switch (cmd)
        {
        case 'F':
            straghtRun(leftMotor, rightMotor, 1);
            backMotor.Stop();
            break;
        case 'B':
            straghtRun(leftMotor, rightMotor, 0);
            backMotor.Stop();
            break;
        case 'I':
            straghtRun(backMotor, leftMotor, 0);
            rightMotor.Stop();
            break;
        case 'G':
            straghtRun(rightMotor, backMotor, 0);
            leftMotor.Stop();
            break;
        case 'H':
            straghtRun(backMotor, leftMotor, 1);;
            rightMotor.Stop();
            break;
        case 'J':
            straghtRun(rightMotor, backMotor, 1);
            leftMotor.Stop();
            break;
        case 'L':
            leftMotor.RunPercentage(100);
            rightMotor.RunPercentage(100);
            backMotor.RunPercentage(100);
            break;
        case 'R':
            leftMotor.RunPercentage(-100);
            rightMotor.RunPercentage(-100);
            backMotor.RunPercentage(-100);
            break;
        case 'S':
            leftMotor.Stop();
            rightMotor.Stop();
            backMotor.Stop();
        default:
            break;
        }
    }
    // getMotion();
    
    // delay(1);
}

void task2(void *param) {
    for (;;) {
        Serial.print(gyroZ);
        Serial.print("\t");
        Serial.println();
        delay(100);
    }
}