/////////////////////////////////////////////////////////////////////////////////// 
// This sketch contains 5 gesture animations for 3 servo motors, triggered over serial 
// for a voice robot prototype created as part of the Emotional Machines project -- 
// Emma Young & Libby Miller - BBC R&D - emma.young02@bbc.co.uk | libby.miller@bbc.co.uk
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
// BASE SERVO - NEUTRAL = 180
int topServoMaxLeft = 40;
int topServoMaxRight = 100;
int topServoNeutral = 70;

int midServoMaxBack = 75;
int midServoMaxForward = 130;
int midServoNeutral = 100;

//int baseServoMaxLeft = 0; // flip if working in reverse on checking
int baseServoMaxBack = 180; // "
int baseServoNeutral = 30;

int baseServoPin = 4;
int midServoPin = 5;
int topServoPin = 6;

void setup() {
  Serial.begin(115200);

  //neutral handles detatch and attach
  neutral();
   
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
        if(command == 0){
          Serial.println("neutral() invoked");
          neutral();
          delay(3000);      
        }
        if(command == 1){
          Serial.println("turnAway(); invoked");
          turnAway();
          neutral();      
        }
        if(command == 2){
          Serial.println("frustration(); invoked");
          frustration();
          neutral();      
        }
        if(command == 3){
          Serial.println("hesitancy(); invoked");
          hesitancy();
          neutral();      
        }
        if(command == 4){
          Serial.println("joy() invoked");
          joy();
          neutral();      
        }        
        if(command == 5){
          Serial.println("anticipation() invoked");
          anticipation();
          neutral();      
        }
        if(command == 6){
          Serial.println("curiosity() invoked");
          curiosity();
          neutral();      
        }
    }  
}
 
void neutral() {
  baseServo.attach(baseServoPin); 
  midServo.attach(midServoPin);
  topServo.attach(topServoPin);
  delay(15);
  baseServo.write(baseServoNeutral);
  midServo.write(midServoNeutral);
  topServo.write(topServoNeutral);
  delay(15);  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}


void turnAway() {
  Serial.println("moving mid and base");
  baseServo.attach(baseServoPin);
  midServo.attach(midServoPin);

  midServo.write(midServoMaxForward);
  delay(500);

  for (pos = baseServoNeutral; pos <= baseServoMaxBack; pos += 1) {
    baseServo.write(pos);
    delay(40);
  }
  delay(5000);
  for (pos = baseServoMaxBack; pos <= baseServoNeutral; pos -= 1) {
    baseServo.write(pos);
    delay(40);
  }
  midServo.write(midServoNeutral);
  delay(500);
  
  baseServo.detach();  
  midServo.detach();
}
void curiosity() {

  baseServo.attach(baseServoPin);  
  midServo.attach(midServoPin);
  topServo.attach(topServoPin);

  neutral();
  
  midServo.write(midServoNeutral - 20);
  delay(1000);
  topServo.write(topServoMaxRight);
  delay(1500);
  topServo.write(topServoNeutral);
  delay(600);
  midServo.write(midServoNeutral);
  delay(700);
  topServo.write(topServoMaxLeft + 20);
  delay(600);
  //midServo.write(midServoNeutral + 10);
  //delay(600);
 // topServo.write(topServoMaxRight - 20);
  //delay(1500);
  topServo.write(topServoNeutral);
  delay(600);
  //midServo.write(midServoNeutral + 30);
  //delay(500);
  //topServo.write(topServoMaxLeft + 20);
  //delay(1500);
  //midServo.write(midServoNeutral + 40);
  //delay(500);
  //topServo.write(topServoMaxLeft);
  //delay(1000);
  //for (pos = topServoMaxLeft; pos <= topServoNeutral; pos += 1) {
    //topServo.write(pos);
    //delay(15);
  //}
  //for (pos = (midServoNeutral + 40); pos >= midServoNeutral; pos -= 1) {
   // midServo.write(pos);
    //delay(15);
  //}

  //delay(15);
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}

void frustration() {
    baseServo.attach(baseServoPin); 
    midServo.attach(midServoPin);
    topServo.attach(topServoPin);

    neutral();
 
    midServo.write(midServoMaxForward);
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
    topServo.write(topServoNeutral);
    
    for (pos = midServoMaxForward; pos >= midServoNeutral; pos -= 1) {
      midServo.write(pos);
      delay(15);
    }

    neutral();
    
    baseServo.detach();  
    midServo.detach();
    topServo.detach(); 
}

void hesitancy() {
  baseServo.attach(baseServoPin); 
  midServo.attach(midServoPin);
  topServo.attach(topServoPin);

  neutral();
  
  midServo.write(midServoMaxBack);
  delay(1000);
  for (pos = midServoMaxBack; pos <= (midServoNeutral); pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(100);
  midServo.write(midServoNeutral);
  delay(500);
  //baseServo.write(baseServoNeutral + 20);
  //delay(100);
  //for (pos = (baseServoNeutral + 20); pos <= baseServoNeutral + 50; pos += 1) {
    //baseServo.write(pos);
    //delay(15);
  //}
  //baseServo.write(baseServoNeutral);
  //delay(500);
  for (pos = (midServoNeutral); pos <= (midServoNeutral + 20); pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(100);
  midServo.write(midServoNeutral + 20);
  delay(1000);
  //for (pos = (midServoNeutral + 20); pos <= (midServoNeutral + 60); pos += 1) {
    //midServo.write(pos);
    //delay(15);
  //}
  //delay(100);
  //midServo.write(midServoNeutral + 40);
  //delay(1000);
  //for (pos = (midServoNeutral + 40); pos >= midServoNeutral; pos -= 1) {
    //midServo.write(pos);
    //delay(15);
  //}
  //delay(15);  

  neutral();
  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}

void joy() {
  baseServo.attach(baseServoPin); 
  midServo.attach(midServoPin);
  topServo.attach(topServoPin);

  neutral();

  midServo.write(midServoMaxBack);
  delay(15);
  for (pos = topServoMaxLeft; pos <= topServoMaxRight; pos += 1) {
    topServo.write(pos);
    baseServo.write(pos + 30);
    delay(15);
  }
  for (pos = topServoMaxRight; pos >= topServoMaxLeft; pos -= 1) {
    topServo.write(pos);
    baseServo.write(pos + 30);
    delay(15);
    }
  for (pos = topServoMaxLeft; pos <= topServoMaxRight; pos += 1) {
    topServo.write(pos);
    baseServo.write(pos + 30);
    delay(15);
    }
  for (pos = topServoMaxRight; pos >= topServoMaxLeft; pos -= 1) {
    topServo.write(pos);
    baseServo.write(pos + 30);
    delay(15);
  }
  for (pos = topServoMaxLeft; pos <= topServoNeutral; pos += 1) {
    topServo.write(pos);
    baseServo.write(pos + 30);
    delay(15);
  }
  delay(100);
  for (pos = midServoMaxBack; pos <= midServoNeutral; pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(15); 

  neutral();
  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
}


void anticipation() {
  baseServo.attach(baseServoPin); 
  midServo.attach(midServoPin);
  topServo.attach(topServoPin);

  neutral();
  
  
  midServo.write(midServoNeutral + 10);
  delay(500);
  
  for (pos = midServoNeutral; pos <= (midServoNeutral + 10); pos += 1) {
    midServo.write(pos);
    delay(15);
  }
  for (pos = (midServoMaxBack + 10); pos >= midServoNeutral; pos -= 1) {
    midServo.write(pos);
    delay(15);
  }
  delay(700);

  neutral();
  
  baseServo.detach();  
  midServo.detach();
  topServo.detach(); 
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
