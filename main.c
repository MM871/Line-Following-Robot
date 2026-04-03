#include <Adafruit_MotorShield.h>
#include "Adafruit_BluefruitLE_SPI.h"

#define VERBOSE_MODE false

#define BLUEFRUIT_SPI_CS   8
#define BLUEFRUIT_SPI_IRQ  7
#define BLUEFRUIT_SPI_RST  4

// Motor terminals
#define MOTOR_A_TERMINAL 1
#define MOTOR_B_TERMINAL 2
#define MOTOR_C_TERMINAL 3
#define MOTOR_D_TERMINAL 4

// IR Sensor pins
#define s1 10  // Rightmost
#define s2 11
#define s3 5  // Center
#define s4 6
#define s5 9  // Leftmost

// Motor speeds
int mspeed = 255;

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// Motor Shield setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MOTOR_A = AFMS.getMotor(MOTOR_A_TERMINAL);
Adafruit_DCMotor *MOTOR_B = AFMS.getMotor(MOTOR_B_TERMINAL);
Adafruit_DCMotor *MOTOR_C = AFMS.getMotor(MOTOR_C_TERMINAL);
Adafruit_DCMotor *MOTOR_D = AFMS.getMotor(MOTOR_D_TERMINAL);

void error(const __FlashStringHelper *err) {
  Serial.println(err);
  while (1);
}

// Movement functions
void moveForward() {
  MOTOR_A->setSpeed(mspeed); MOTOR_A->run(FORWARD);
  MOTOR_B->setSpeed(mspeed); MOTOR_B->run(FORWARD);
  MOTOR_C->setSpeed(mspeed); MOTOR_C->run(FORWARD);
  MOTOR_D->setSpeed(mspeed); MOTOR_D->run(FORWARD);
}

void turnLeft() {
  MOTOR_A->setSpeed(15); MOTOR_A->run(FORWARD);
  MOTOR_B->setSpeed(15);  MOTOR_B->run(FORWARD);
  MOTOR_C->setSpeed(120);  MOTOR_C->run(FORWARD);
  MOTOR_D->setSpeed(120); MOTOR_D->run(FORWARD);
}

void turnRight() {
  MOTOR_A->setSpeed(120); MOTOR_A->run(FORWARD);
  MOTOR_B->setSpeed(120);  MOTOR_B->run(FORWARD);
  MOTOR_C->setSpeed(15);  MOTOR_C->run(FORWARD);
  MOTOR_D->setSpeed(5); MOTOR_D->run(FORWARD);
}

void sharpleft() {
  MOTOR_A->setSpeed(100); MOTOR_A->run(BACKWARD);
  MOTOR_B->setSpeed(100);  MOTOR_B->run(BACKWARD);
  MOTOR_C->setSpeed(255);  MOTOR_C->run(FORWARD);
  MOTOR_D->setSpeed(255); MOTOR_D->run(FORWARD);
}

void sharpright() {
  MOTOR_A->setSpeed(255); MOTOR_A->run(FORWARD);
  MOTOR_B->setSpeed(255);  MOTOR_B->run(FORWARD);
  MOTOR_C->setSpeed(100);  MOTOR_C->run(BACKWARD);
  MOTOR_D->setSpeed(100); MOTOR_D->run(BACKWARD);
}



void stopAllMotors() {
  MOTOR_A->setSpeed(0); MOTOR_A->run(RELEASE);
  MOTOR_B->setSpeed(0); MOTOR_B->run(RELEASE);
  MOTOR_C->setSpeed(0); MOTOR_C->run(RELEASE);
  MOTOR_D->setSpeed(0); MOTOR_D->run(RELEASE);
}

// Line-following logic
void followline() {

  int val_s1 = digitalRead(s1);
  int val_s2 = digitalRead(s2);
  int val_s3 = digitalRead(s3);
  int val_s4 = digitalRead(s4);
  int val_s5 = digitalRead(s5);

  // Debugging output
  Serial.print("S1: "); Serial.print(val_s1);
  Serial.print(" | S2: "); Serial.print(val_s2);
  Serial.print(" | S3: "); Serial.print(val_s3);
  Serial.print(" | S4: "); Serial.print(val_s4);
  Serial.print(" | S5: "); Serial.println(val_s5);


  // Line-following decisions
  if (val_s1 == 0 && val_s5 == 0 && val_s2 == 1 && val_s3 == 1 && val_s4 == 1) {
    moveForward();
  }
  else if((val_s1 == 1 && val_s5 == 1 && val_s2 == 1 && val_s3 == 1 && val_s4 == 1) || (val_s1 == 0 && val_s5 == 0 && val_s2 == 0 && val_s3 == 0 && val_s4 == 0)){
    moveForward();
  }
  else if ((val_s1 == 1 && val_s2 == 1 && val_s3 == 1 && val_s4 == 0 && val_s5 == 0) || (val_s1 == 1 && val_s2 == 1 && val_s3 == 0 && val_s4 == 0 && val_s5 == 0) || (val_s1 == 1 && val_s2 == 0 && val_s3 == 0 && val_s4 == 0 && val_s5 == 0)) {
    turnRight();
  }
  else if ((val_s1 == 0 && val_s2 == 0 && val_s3 == 1 && val_s4 == 1 && val_s5 == 1) || (val_s1 == 0 && val_s2 == 0 && val_s3 == 0 && val_s4 == 1 && val_s5 == 1) || (val_s1 == 0 && val_s2 == 0 && val_s3 == 0 && val_s4 == 0 && val_s5 == 1)) {
    turnLeft();
  }
  else if((val_s1 == 0 && val_s2 == 1 && val_s3 == 1 && val_s4 == 1 && val_s5 == 1)){
    sharpleft();
    delay(150);
  }
  else if((val_s1 == 1 && val_s2 == 1 && val_s3 == 1 && val_s4 == 1 && val_s5 == 0)){
    sharpright();
    delay(150);
  }
  // else if(val_s1 == 1 && val_s2 == 1 && val_s3 == 1 && val_s4 == 1 && val_s5 == 1) {
  //   stopAllMotors();  // Line lost or junction
  // }
}


void setup() {
  Serial.begin(9600); // For debugging
  AFMS.begin();

  stopAllMotors();

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);

  if (!ble.begin(VERBOSE_MODE)) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  if (!ble.factoryReset()) {
    error(F("Couldn't factory reset"));
  }

  ble.echo(false);
  ble.verbose(false);  // Less debug output

  while (!ble.isConnected()) {
    delay(500);
  }

  ble.setMode(BLUEFRUIT_MODE_DATA);

}

int mode = 0; // 0 = idle, 1 = followline, 2 = stop


void loop() {
  // Check for Bluetooth input
  if (ble.available()) {
    char input[4] = {0};
    int i = 0;

    // Read up to 4 bytes
    while (ble.available() && i < 4) {
      input[i++] = ble.read();
    }

    if (i >= 4) {
      char button = input[2];
      char action = input[3];

      if (action == '1') {  // Button pressed
        if (button == '1') {
          mode = 1;  // Line-following mode
        } else if (button == '2') {
          mode = 0;  // Idle (Stop everything)
          stopAllMotors();
        } else if (button == '5' || button == '6' || button == '7' || button == '8') {
          mode = 2;  // Manual control mode
          if (button == '5') {
            moveForward();
          } else if (button == '6') {
            // backward function not yet defined, add this:
            MOTOR_A->setSpeed(mspeed); MOTOR_A->run(BACKWARD);
            MOTOR_B->setSpeed(mspeed); MOTOR_B->run(BACKWARD);
            MOTOR_C->setSpeed(mspeed); MOTOR_C->run(BACKWARD);
            MOTOR_D->setSpeed(mspeed); MOTOR_D->run(BACKWARD);
          } else if (button == '7') {
            turnLeft();
          } else if (button == '8') {
            turnRight();
          }
        }
      } 
      else if (action == '0') {  // Button released
        if (mode == 2) {
          stopAllMotors();
        }
      }
    }
  }

  // Run the mode logic
  if (mode == 1) {
    followline(); // Line-following mode
  }
  // Mode 2 (manual) is handled above on Bluetooth input
}
