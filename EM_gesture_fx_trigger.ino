/////////////////////////////////////////////////////////////////////////////////// 
//This sketch contains 5 gesture animations for 3 servo motors, triggered by 5 seperate buttons-- 
// written for user testing purposes for the Emotional Machines project -- 
// Emma Young - BBC R&D - emma.young02@bbc.co.uk
///////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>

Servo baseServo;  // create servo object to control a servo
Servo midServo;
Servo topServo;
int pos = 0;    // variable to store the servo position

#define BUTTON_PIN_1 7 // Digital IO pin 7 connected to Button 1  (Hesitancy) (and Ground)
#define BUTTON_PIN_2 8 // Pin 8 --> Button 2  (Joy)
#define BUTTON_PIN_3 9 // Pin 9 --> Button 3  (Curiosity)
#define BUTTON_PIN_4 10 // Pin 10 --> Button 4  (Frustration)
#define BUTTON_PIN_5 11 // Pin 11 --> Button 5  (Anticipation)

bool oldStateButton1 = HIGH;
bool oldStateButton2 = HIGH;
bool oldStateButton3 = HIGH;
bool oldStateButton4 = HIGH;
bool oldStateButton5 = HIGH;
int showType = 0;
//states: 10: checking; 0: breathing; 1: button 1; 2: button 2; 3: button 3; 4: button 4: 5: button 5
int state = 0;

// RANGE OF MOTION LIMITATIONS 
// TOPSERVO - NEUTRAL  = 90 | MIN POS (LEFT)  = 50 | MAX POS (RIGHT) = 130 (for symmetry)
// MIDSERVO - NEUTRAL = 35 | MIN POS (BACK) = 0 | MAX POS (FORWARD) = 180 (reverse mounting)
// BASE SERVO - NEUTRAL = 90
int topServoMaxLeft = 50;
int topServoMaxRight = 130;
int topServoNeutral = 80;

int midServoMaxBack = 0;
int midServoMaxForward = 180;
int midServoNeutral = 35;

int baseServoMaxLeft = 0; // flip if working in reverse on checking
int baseServoMaxRight = 180; // "
int baseServoNeutral = 90;

void setup() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  
  Serial.begin(9600);
  baseServo.attach(4);  // attaches the base servo on pin 5 to the servo object
  midServo.attach(5);
  topServo.attach(6);
  neutral(); 
}
void loop() {
  
  //breathe(); // idle state - to have one or not? Risk motor burn out?
  checkButton();
}
 
void breathe(){
  //do something - if having idle state?
}
  
void checkButton(){
  bool newStateButton1 = digitalRead(BUTTON_PIN_1);
  if(newStateButton1==LOW && oldStateButton1==HIGH){
      Serial.println("button 1 pressed");
      curiosity();
      neutral();
  }
  bool newStateButton2 = digitalRead(BUTTON_PIN_2);
  if(newStateButton2==LOW && oldStateButton2==HIGH){
      Serial.println("button 2 pressed");
      frustration();
      neutral();
  }
  bool newStateButton3 = digitalRead(BUTTON_PIN_3);
  if(newStateButton3==LOW && oldStateButton3==HIGH){
      Serial.println("button 3 pressed");
      hesitancy();
      neutral();
  }
  bool newStateButton4 = digitalRead(BUTTON_PIN_4);
  if(newStateButton4==LOW && oldStateButton4==HIGH){
      Serial.println("button 4 pressed");
      joy();
      neutral();
  }
  bool newStateButton5 = digitalRead(BUTTON_PIN_5);
  if(newStateButton5==LOW && oldStateButton5==HIGH){
      Serial.println("button 5 pressed");
      anticipation();
      neutral();
  } 
}

void neutral() {
  baseServo.write(baseServoNeutral);
  midServo.write(midServoNeutral);
  topServo.write(topServoNeutral);
}

void curiosity() {
  neutral();
  midServo.write(midServoNeutral - 30);
  delay(1000);
  topServo.write(topServoMaxRight - 30);
  delay(1500);
  topServo.write(topServoNeutral);
  delay(600);
  //topServo.write(topServoMaxRight - 20);
  //delay(1000);
  midServo.write(midServoNeutral);
  delay(700);
  topServo.write(topServoNeutral);
  delay(600);
  midServo.write(midServoNeutral + 10);
  delay(600);
  topServo.write(topServoMaxRight - 20);
  delay(1500);
  topServo.write(topServoNeutral);
  delay(600);
  midServo.write(midServoNeutral + 30);
  delay(500);
  topServo.write(topServoMaxLeft + 20);
  delay(1500);
  midServo.write(midServoNeutral + 40);
  delay(500);
  topServo.write(topServoMaxLeft);
  delay(1000);
  for (pos = topServoMaxLeft; pos <= topServoNeutral; pos += 1) {
    topServo.write(pos);
    delay(15);
  }
  for (pos = (midServoNeutral + 40); pos >= midServoNeutral; pos -= 1) {
    midServo.write(pos);
    delay(15);
  }
}

void frustration() {
    neutral();
    midServo.write(midServoMaxForward - 70);
    delay(300);
    for (pos = topServoMaxLeft; pos <= topServoMaxRight; pos += 4) {
      topServo.write(pos);
      delay(15);
    }
    for (pos = topServoMaxRight; pos >= topServoMaxLeft; pos -= 4) {
      topServo.write(pos);
      delay(15);
    }
    for (pos = topServoMaxLeft; pos <= topServoMaxRight; pos += 4) {
      topServo.write(pos);
      delay(15);
    }
    for (pos = topServoMaxRight; pos >= topServoMaxLeft; pos -= 4) {
      topServo.write(pos);
      delay(15);
    }
    neutral();
    delay(200);
    midServo.write(midServoMaxBack);
    delay(500);
    for (pos = (baseServoMaxRight - 45); pos >= (baseServoMaxLeft + 45); pos -= 1) {
      baseServo.write(pos);
      delay(15);
    }
    delay(100);
    for (pos = (baseServoMaxLeft + 45); pos <= (baseServoMaxRight - 45); pos += 1) {
      baseServo.write(pos);
      midServo.write(midServoMaxBack + pos);
      delay(15);
    }
    delay(100);
    neutral();
}

void hesitancy() {
  neutral();
  midServo.write(midServoMaxBack);
  delay(1000);
  for (pos = (midServoMaxBack); pos <= (midServoNeutral + 20); pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(100);
  midServo.write(midServoNeutral);
  delay(500);
  baseServo.write(baseServoNeutral - 20);
  delay(100);
  for (pos = (baseServoNeutral - 20); pos <= baseServoNeutral + 20; pos += 1) {
    baseServo.write(pos);
    delay(15);
  }
  baseServo.write(baseServoNeutral);
  delay(500);
  for (pos = (midServoNeutral); pos <= (midServoNeutral + 40); pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(100);
  midServo.write(midServoNeutral + 20);
  delay(1000);
  for (pos = (midServoNeutral + 20); pos <= (midServoNeutral + 60); pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(100);
  midServo.write(midServoNeutral + 40);
  delay(1000);
  for (pos = (midServoNeutral + 40); pos >= midServoNeutral; pos -= 1) {
    midServo.write(pos);
    delay(15);
  }
}

void joy() {
  neutral();
  midServo.write(midServoMaxBack);
  delay(15);
  for (pos = topServoMaxLeft; pos <= topServoMaxRight; pos += 1) {
    topServo.write(pos);
    baseServo.write(pos);
    delay(15);
  }
  for (pos = topServoMaxRight; pos >= topServoMaxLeft; pos -= 1) {
    topServo.write(pos);
    baseServo.write(pos);
    delay(15);
    }
  for (pos = topServoMaxLeft; pos <= topServoMaxRight; pos += 1) {
    topServo.write(pos);
    baseServo.write(pos);
    delay(15);
    }
  for (pos = topServoMaxRight; pos >= topServoMaxLeft; pos -= 1) {
    topServo.write(pos);
    baseServo.write(pos);
    delay(15);
  }
  for (pos = topServoMaxLeft; pos <= topServoNeutral; pos += 1) {
    topServo.write(pos);
    baseServo.write(pos + 10);
    delay(15);
  }
  delay(100);
  for (pos = midServoMaxBack; pos <= midServoNeutral; pos += 1) {
    midServo.write(pos);
    delay(15);
  }
}

void anticipation() {
  neutral();
  baseServo.write(baseServoNeutral - 40);
  delay(500);
  for (pos = (baseServoNeutral - 40); pos <= baseServoNeutral + 40; pos += 1) {
    baseServo.write(pos);
    delay(15);
  }
  baseServo.write(baseServoNeutral);
  delay(1000);
  baseServo.write(baseServoNeutral - 20);
  delay(500);
  for (pos = (baseServoNeutral - 20); pos <= baseServoNeutral + 20; pos += 1) {
    baseServo.write(pos);
    delay(15);
  }
  delay(700);
  baseServo.write(baseServoNeutral);
  delay(500);
  midServo.write(midServoMaxBack + 10);
  delay(500);
  baseServo.write(baseServoNeutral - 20);
  delay(500);
  for (pos = (baseServoNeutral - 20); pos <= baseServoNeutral + 20; pos += 1) {
    baseServo.write(pos);
    delay(15);
  }
  baseServo.write(baseServoNeutral);
  delay(500);
  for (pos = (midServoMaxBack + 10); pos <= midServoNeutral; pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(700);
  baseServo.write(baseServoNeutral - 40);
  delay(500);
  for (pos = (baseServoNeutral - 40); pos <= baseServoNeutral + 40; pos += 1) {
    baseServo.write(pos);
    delay(15);
  }
  baseServo.write(baseServoNeutral);
  delay(700);
  neutral();
}
