#include <Servo.h>

int sonar_trig_pin = A1;
int sonar_echo_pin = A2;

Servo servo_ear_left;
Servo servo_ear_right;
Servo servo_eyes;

int ear_left_open = 1100;
int ear_left_middle = 1500;
int ear_left_closed = 1900;
int ear_right_open = 1900;
int ear_right_middle = 1500;
int ear_right_closed = 1100;

int servo_eyes_up = 1700;
int servo_eyes_normal = 1500;

void setup() {
  servo_ear_left.attach(3);
  servo_ear_right.attach(4);
  servo_eyes.attach(2);

  pinMode(sonar_trig_pin, OUTPUT);
  pinMode(sonar_echo_pin, INPUT);
}

#define STATE_OPEN 0
#define STATE_CLOSED 1

void loop() {
  static bool is_open = true;
  static int state = STATE_OPEN;

  if (state == STATE_CLOSED) {
    
    delay(2000);
    servo_ear_left.writeMicroseconds(ear_left_middle);
    servo_ear_right.writeMicroseconds(ear_right_middle);
    delay(500);
    state = STATE_OPEN;
  }
  else if (state == STATE_OPEN) {

    int distance = getDistance();
    
    if (distance >= 30) {
      servo_eyes.writeMicroseconds(servo_eyes_normal);
      delay(200);
      servo_ear_left.writeMicroseconds(ear_left_open);
      servo_ear_right.writeMicroseconds(ear_right_open);
    }
    else if (distance < 30 && distance >= 15) {
      servo_eyes.writeMicroseconds(servo_eyes_up);
      delay(200);
      servo_ear_left.writeMicroseconds(ear_left_open);
      servo_ear_right.writeMicroseconds(ear_right_open);
    }
    else if (distance < 15 && distance > 7) {
      servo_ear_left.writeMicroseconds(ear_left_closed);
      servo_ear_right.writeMicroseconds(ear_right_closed);
      delay(200);
      servo_eyes.writeMicroseconds(servo_eyes_up);
      state = STATE_CLOSED;
    }
  }
  
}

float getDistance() {
  digitalWrite(sonar_trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonar_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar_trig_pin, LOW);
  unsigned long duration = pulseIn(sonar_echo_pin, HIGH);
  float distance = duration / 29.0 / 2.0;

  return distance;
}

