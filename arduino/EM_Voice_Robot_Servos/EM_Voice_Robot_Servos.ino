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

  //neutral handles detatch and attach
  neutral(); 

  //for debugging
  Serial.begin(115200);
  
}
void loop() {
   checkSerial();
}



String str;

void checkSerial(){
    if(Serial.available() > 0)
    {
        str = Serial.readStringUntil('\n');
        Serial.println("str is ");
        Serial.println(str);
        String val = getValue(str, ' ', 0);
        int command = val.toInt();
        if(command == 1){
          Serial.println("curiosity() invoked");
          curiosity();
          neutral();      
        }
        if(command == 2){
          Serial.println("frustration(); invoked");
          frustration();
          neutral();      
        }
        if(command == 3){
          Serial.println("hesitancy(); invoked");
          curiosity();
          hesitancy();      
        }
        if(command == 4){
          Serial.println("joy() invoked");
          joy();
          neutral();      
        }        
        if(command == 5){
          Serial.println("anticipation invoked");
          anticipation();
          neutral();      
        }
    }  
}
 
void breathe(){
  //do something - if having idle state?
}
  

void neutral() {
  
  baseServo.attach(4); 
  midServo.attach(5);
  topServo.attach(6);
  delay(15);
  baseServo.write(baseServoNeutral);
  midServo.write(midServoNeutral);
  topServo.write(topServoNeutral);
  delay(15);  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}

void curiosity() {

  neutral();

  baseServo.attach(4);  
  midServo.attach(5);
  topServo.attach(6);  
  delay(15);
  
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

  delay(15);
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}

void frustration() {
  
    neutral();
    baseServo.attach(4); 
    midServo.attach(5);
    topServo.attach(6);
    delay(15);
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
    delay(15);  
    baseServo.detach();  
    midServo.detach();
    topServo.detach(); 
    neutral();
}

void hesitancy() {
  neutral();
  baseServo.attach(4); 
  midServo.attach(5);
  topServo.attach(6);
  delay(15);
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
  delay(15);  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}

void joy() {
  neutral();
  baseServo.attach(4); 
  midServo.attach(5);
  topServo.attach(6);
  delay(15);
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
  delay(15);  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}


void anticipation() {
  neutral();
  baseServo.attach(4); 
  midServo.attach(5);
  topServo.attach(6);
  delay(15);
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
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
  neutral();
}


// https://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
