#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 110
#define SERVOMAX 480
#define SWITCH_PIN_1 13
#define SWITCH_PIN_2 12
#define SWITCH_PIN_3 14
#define SWITCH_PIN_4 27

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pwm.begin();
  pwm.setPWMFreq(50);

  Servo_begin();

  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);
  pinMode(SWITCH_PIN_4, INPUT_PULLUP);

  Serial.println("\n初始化");
}

int begin[3] = { 90, 180, 0 };
int start[3] = { 90, 120, 80 };

int angle(int n) {
  return map(n, 0, 180, SERVOMIN, SERVOMAX);
}

void Servo_begin() {
  int j = 0;
  for (int i = 0; i < 9; i++) {
    pwm.setPWM(i, 0, angle(begin[j]));
    j++;
    if (j >= 3) {
      j = 0;
    }
  }
  delay(1000);  //舵机初始化
  j = 0;
  for (int i = 0; i < 9; i++) {
    pwm.setPWM(i, 0, angle(start[j]));
    j++;
    if (j >= 3) {
      j = 0;
    }
  }
}


void loop() {
  int up = digitalRead(SWITCH_PIN_1);
  int down = digitalRead(SWITCH_PIN_2);
  int move = digitalRead(SWITCH_PIN_3);
  int zero = digitalRead(SWITCH_PIN_4);

  if (up == LOW) {
    pwm.setPWM(1, 0, angle(160));
    pwm.setPWM(2, 0, angle(120));
  }

  if (down == LOW) {
    pwm.setPWM(1, 0, angle(120));
    pwm.setPWM(2, 0, angle(80));
  }

  if (move == LOW) {
    pwm.setPWM(1, 0, angle(160));
    pwm.setPWM(2, 0, angle(120));
    pwm.setPWM(0, 0, angle(120));
    delay(500);

    pwm.setPWM(2, 0, angle(80));
    pwm.setPWM(1, 0, angle(120));
    delay(500);

    pwm.setPWM(0, 0, angle(90));
    delay(500);
  }

  if (zero == LOW) {
    int j = 0;
    for (int i = 0; i < 9; i++) {
      pwm.setPWM(i, 0, angle(begin[j]));
      j++;
      if (j >= 3) {
        j = 0;
      }
    }
  }
}
