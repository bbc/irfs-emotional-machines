///////////////////////////////////////////////////////////////////////////////////////// 
// This sketch contains lighting animations for a Neopixel 144 LED strip -- 
// driving lighting fx triggered over serial for a voice robot prototype
// created as part of the Emotional Machines project -- 
// Emma Young & Libby Miller - BBC R&D - emma.young02@bbc.co.uk | libby.miller@bbc.co.uk
//this version doesn't work!

/////////////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>
#define LED_PIN 9
#define LED_COUNT 144

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include <Servo.h>

Servo baseServo;  // create servo object to control a servo
Servo midServo;
Servo topServo;
int pos = 0;    // variable to store the servo position

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
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(10); // Set BRIGHTNESS to 1/10 (to save your eyes, uncomment if diffusing light)

  baseServo.attach(4);  // attaches the base servo on pin 5 to the servo object
  midServo.attach(5);
  topServo.attach(6);
  
  Serial.begin(115200); //for debugging
  Serial.println("ok");
}
void loop() {
  heartbeat();
  //checkSerial();
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
        if(command == 6){
          Serial.println("cold light invoked");
          cold();    
        }
        else if(command == 7){
          Serial.println("warm light invoked");
          warm();
        }
        else if(command == 1){
          Serial.println("heartbeat again");
          warm();
        }
        else {
          Serial.println("no serial value for light received");  
        }
    }
} 

void heartbeat(){
  for (int i = 0; i < 65535; i++) {
    //float intensity = 25;
    float intensity = 127 /2.0 * (1.0 + sin(0.01 * i));
    strip.setBrightness(intensity);
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, 75, 75, 75);
    }
    strip.show();
    delay(5);
    checkSerial();
    // cold(); 
    // warm();
  } 
}

void cold() {
  for(int j=0; j<strip.numPixels(); j++) { //to scale for any number of pixels in strip
      strip.setPixelColor(j, 0, 0, 255); //add extra blue to increasing brightness
  }
  strip.show();
  delay(5);
}

void warm() {
  for(int j=0; j<strip.numPixels(); j++) { //to scale for any number of pixels in strip
      strip.setPixelColor(j, 255, 128, 0); //add extra blue to increasing brightness
  }
  strip.show();
  delay(5);
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

/*void hesitancy(){
    delay(20); //Short delay to debounce button
    bool newStateButton1 = digitalRead(BUTTON_PIN_1); // Check if button is still low after debounce
    if(newStateButton1 == LOW){
      strip.clear();
      strip.show();
      creepAndRetreat(strip.Color(200, 225, 0), 4); // yellow-green, pass limit (pixel to wipe to)
      delay(500);
      creepAndRetreat(strip.Color(200, 225, 0), 6);
      delay(500);
      creepAndRetreat(strip.Color(200, 225, 0), 4); // yellow-green, pass limit (pixel to wipe to)
      delay(500);
      creepAndRetreat(strip.Color(200, 225, 0), 6);
      delay(500);
      strip.clear();
      strip.show();
    }
}

void joy(){
    delay(20); //Short delay to debounce button
    bool newStateButton2 = digitalRead(BUTTON_PIN_2); // Check if button is still low after debounce
    if(newStateButton2 == LOW){
      strip.clear();
      strip.show();
      for(int i=0; i<4; i++){ 
        colorWipe(strip.Color(255, 5, 5), 10); // Light Red
        delay(100);
        reverseWipe(strip.Color(255, 128, 0), 50); // Orange
        delay(100);
        colorWipe(strip.Color(240, 160, 0), 5); // Light Yellow
        delay(100);
        reverseWipe(strip.Color(255, 128, 0), 50); // Orange
        delay(100);
      }
      strip.clear();
      strip.show();
    } 
}

void curiosity(){
    delay(20); //Short delay to debounce button
    bool newStateButton3 = digitalRead(BUTTON_PIN_3); // Check if button is still low after debounce
    if(newStateButton3 == LOW){
      strip.clear();
      strip.show();
      creep(strip.Color(127, 127, 127), 1000); // White, half brightness
      delay (400);
      pulse();
      delay(400);
      strip.clear();
      delay(400);
      strip.clear();
      strip.show();
    }
}

void frustration(){
    delay(20); //Short delay to debounce button
    bool newStateButton4 = digitalRead(BUTTON_PIN_4); // Check if button is still low after debounce
    if(newStateButton4 == LOW){
      strip.clear();
      strip.show();
      colorWipe(strip.Color(255, 0, 0), 30); // red
      colorWipe(strip.Color(0, 0, 0), 50); // off
      firstPixelFlash(strip.Color(255, 0, 255)); // purple
      delay(400);
      lastPixelFlash(strip.Color(202, 229, 0)); // yellow-green
      delay(50);
      colorWipe(strip.Color(255, 5, 5), 30); // dark red
      colorWipe(strip.Color(0, 0, 0), 50);
      lastHalfFlash(strip.Color(255, 0, 255)); // purple
      delay(500);
      firstHalfFlash(strip.Color(202, 229, 0)); // yellow-green
      delay(200);
      lastHalfFlash(strip.Color(255, 0, 255)); // purple
      delay(200);
      colorWipe(strip.Color(255, 0, 0), 30); // red
      colorWipe(strip.Color(0, 0, 0), 50);
      firstHalfFlash(strip.Color(202, 229, 0)); // yellow-green
      delay(100);
      strip.clear();
      strip.show();
    }
}

void anticipation(){
    delay(20); //Short delay to debounce button
    bool newStateButton5 = digitalRead(BUTTON_PIN_5); // Check if button is still low after debounce
    if(newStateButton5 == LOW){
      strip.clear();
      strip.show();
      for(int i=0; i<4; i++){
        beat();
        delay(150);
        pulse();
        delay(400);
        strip.clear();         //   Set all pixels in RAM to 0 (off)
      }
      strip.clear();
      strip.show();
    }
}

///////////////////////////////////////////////////////////////////////////////////
// Button 1 Function (Hesitancy sequence)
void creepAndRetreat(uint32_t color, int limit){ // forward wipe to limit
  for(int i=0; i<=limit; i++){
    strip.setPixelColor(i, color);
    strip.show();
    delay(100);
  }
  for(int i=limit; i>=limit-2; i--) { // reverse wipe from limit -2
    strip.setPixelColor(i, 0, 0, 0);         
    strip.show();                      
    delay(100); 
  }
  strip.setPixelColor(limit-2, 255, 50, 0); //colour to hold at pixel stop point - dark orange
  strip.setPixelColor(limit-3, 255, 50, 0); //include adjacent pixel for more brightness
  strip.show();                      
  delay(1000);
}
///////////////////////////////////////////////////////////////////////////////////
// Button 2 Functions (Joy Sequence)
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause
  }
}
void reverseWipe(uint32_t colour, int wait) {
  for(int i=(strip.numPixels()-1); i>=0; i--) { // For each pixel in strip...
    strip.setPixelColor(i, colour);         //  Set pixel's color
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause
  }
}
///////////////////////////////////////////////////////////////////////////////////
// Button 3 Functions (Curiosity Sequence)
void creep(uint32_t color, int wait) {
  for(int i=0; i<=(strip.numPixels()-1); i++) { // For each pixel in strip...
    strip.clear();
    strip.setPixelColor(i, color);
    strip.show(); //  Update strip to match
    delay(wait);
    push(i);
  }
}
void push(int i) {
  if (i!=7){
    for (int p=0; p<i; p++){
    strip.setPixelColor(p, 255, 75, 0);
    strip.show();
    delay(15);
    strip.clear();
    }
  }
}
void pulse() {
  for (int i; i < 50 ; i++) {
    for(int j=0; j<strip.numPixels(); j++) { //to scale for any number of pixels in strip
      strip.setPixelColor(j, i, i, i+25); //add extra blue to increasing brightness
    }
    strip.show();
    delay(20);
  }
  for (int i = 50; i > 0; i--) {
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, i, i, i+25);//add extra blue to decreasing brightness
    }
    strip.show();
    delay(20);
  }
}
///////////////////////////////////////////////////////////////////////////////////
// Button 4 Functions (Frustration Sequence)
void firstPixelFlash(uint32_t color){
  strip.setPixelColor(0, color);
  strip.show();
  delay(100);
  strip.clear();
  strip.show();
  delay(100);
  strip.setPixelColor(0, color);
  strip.show();
  delay(100);
  strip.clear();
  strip.show();
  delay(100);
}

void lastPixelFlash(uint32_t color){
  strip.setPixelColor(7, color);
  strip.show();
  delay(200);
  strip.clear();
  strip.setPixelColor(7, color);
  strip.show();
  delay(200);
  strip.clear();
}

void lastHalfFlash(uint32_t color){
  for(int t=0; t<=3; t++){
    for (int i=4; i<=7; i++){
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
    strip.clear();
    strip.show();
    delay(10);
    //i--;
    }
  }
}

void firstHalfFlash(uint32_t color){
  for(int t=0; t<=5; t++){
    for (int i=0; i<=3; i++){
    strip.setPixelColor(i, color);
    strip.show();
    delay(5);
    strip.clear();
    strip.show();
    delay(10);
    }
   delay(50);
  }
}
///////////////////////////////////////////////////////////////////////////////////
// Button 5 Functions (Frustration Sequence)
void beat(){
    strip.show();
    strip.setPixelColor(0, 255, 40, 0); 
    strip.setPixelColor(1, 255, 40, 0); // set 1st and 2nd pixels in strip to red-orange
    strip.show();
    delay(200);
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.show();
    delay(150);
    strip.setPixelColor(0, 255, 40, 0); 
    strip.setPixelColor(1, 255, 40, 0); // set 1st and 2nd pixels in strip to red-orange
    strip.show();
    delay(200);
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.show();
    delay(150);
}*/
