// Phase II TABLEBot Code

#include <Servo.h>               // Load "Servo" library
Servo servoLeft;                 // Left drive servo
Servo servoRight;                // Right drive servo
const int BumpLeft = 4;          // Left bumper Pin 4
const int BumpRight = 5;         // Right bumper Pin 5
int BumpStateLeft = 0;           // Set Left Bump State value
int BumpStateRight = 0;          // Set Right Bump State value
int pingPin = 10;                // Set Ping Sensor Pin
long raw_distance;               // Value for Raw Distance Ping Pulse
int val6 = 0;                    // Value for Left Front IR
int val7 = 0;                    // Value for Right Front IR
int val8 = 0;                    // Value for Left Rear IR
int val9 = 0;                    // Value for Right Rear IR
int x = 0;                       // Counter Variable
int y = 0;                       // Counter Variable

void setup() {
  Serial.begin(9600);                   // Setup serial monitor for debug
  servoLeft.attach(2);                  // Set left servo to pin 2
  servoRight.attach(3);                 // Set right servo to pin 3
  pinMode(BumpLeft, INPUT_PULLUP);             // Set BumperLeft to input with pullup resistor
  pinMode(BumpRight, INPUT_PULLUP);            // Set BumperRight to input with pullup resistor
}

void loop() {
  read_ping();

  if (raw_distance < 5000) {
    forward();
  }

  if (raw_distance > 5000) {
    x = 0;
    while (x < 100) {
      clockwise();
      x++;
    }
    x = 0;
    while (x < 100) {
      stop();
      x++;
    }
    y++;
    if (y > 10) {
      x = 0;
      while (x < 200) {
        forward();
        x++;
        y = 0;
      }
    }
  }
}

void read_ping() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  raw_distance = pulseIn(pingPin, HIGH);

  //  Serial.print(raw_distance);
  //  Serial.println();
  //  delay(10);
}

void stop() {
  servoLeft.write(90);
  servoRight.write(90);
  delay (2);
  //  ir_check();
}

void left_forward() {
  servoLeft.write(180);
  servoRight.write(90);
  delay (2);
  //  ir_check();
}

void left_reverse() {
  servoLeft.write(0);
  servoRight.write(90);
  delay (2);
  //  ir_check();
}

void right_forward() {
  servoLeft.write(90);
  servoRight.write(0);
  delay (2);
  //  ir_check();
}

void forward() {
  servoLeft.write(180);
  servoRight.write(0);
  delay(2);
  ir_check();
}

void counterclockwise() {
  servoLeft.write(0);
  servoRight.write(0);
  delay(2);
  //  ir_check();
}

void right_reverse() {
  servoLeft.write(90);
  servoRight.write(180);
  delay (2);
  //  ir_check();
}

void clockwise() {
  servoLeft.write(180);
  servoRight.write(180);
  delay(2);
  //  ir_check();
}

void reverse() {
  servoLeft.write(0);
  servoRight.write(180);
  delay(2);
  //  ir_check();
}

void ir_check() {
  val6 = digitalRead(6);
  Serial.println(val6);              // debug value
  if (val6 == 1) {

    x = 0;
    while (x < 100) {
      stop();
      x++;
    }

    x = 0;
    while (x < 100) {
      reverse();
      x++;
    }

    x = 0;
    while (x < 200) {
      clockwise();
      x++;
    }
  }

  val7 = digitalRead(7);
  Serial.println(val7);             // debug value
  if (val7 == 1) {

    x = 0;
    while (x < 100) {
      stop();
      x++;
    }

    x = 0;
    while (x < 100) {
      reverse();
      x++;
    }

    x = 0;
    while (x < 100) {
      counterclockwise();
      x++;
    }
  }
}
