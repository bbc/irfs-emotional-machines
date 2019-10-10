/////////////////////////////////////////////////////////////////////////////////// 
//This sketch contains 5 lighting animations for an 8-LED Neopixel stick, triggered by 5 seperate buttons-- 
// written for user testing purposes for the Emotional Machines project -- 
// Emma Young - BBC R&D - emma.young02@bbc.co.uk
///////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>
#define LED_PIN 6
#define LED_COUNT 8
#define BUTTON_PIN_1 7 // Digital IO pin 7 connected to Button 1  (Hesitancy) (and Ground)
#define BUTTON_PIN_2 8 // Pin 8 --> Button 2  (Joy)
#define BUTTON_PIN_3 9 // Pin 9 --> Button 3  (Curiosity)
#define BUTTON_PIN_4 10 // Pin 10 --> Button 4  (Frustration)
#define BUTTON_PIN_5 11 // Pin 11 --> Button 5  (Anticipation)

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

bool oldStateButton1 = HIGH;
bool oldStateButton2 = HIGH;
bool oldStateButton3 = HIGH;
bool oldStateButton4 = HIGH;
bool oldStateButton5 = HIGH;
int showType = 0;
//states: 10: checking; 0: breathing; 1: button 1; 2: button 2; 3: button 3; 4: button 4: 5: button 5
int state = 0;


void setup() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //strip.setBrightness(50); // Set BRIGHTNESS to 1/5 (to save your eyes, uncomment if diffusing light)
  Serial.begin(115200); //for debugging
}
void loop() {
  Serial.println(state);
  for (int i = 0; i < 65535; i++) {
    float intensity = 127 /2.0 * (1.0 + sin(0.01 * i));
    strip.setBrightness(intensity);
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, 75, 75, 75);
    }
    strip.show();
    delay(5);
    checkButton();
  }
  
}
void checkButton(){
    bool newStateButton1 = digitalRead(BUTTON_PIN_1);
    if(newStateButton1==LOW && oldStateButton1==HIGH){
        Serial.println("button 1 pressed");
        hesitancy();
        //strip.clear();
        //strip.show();
    }
    bool newStateButton2 = digitalRead(BUTTON_PIN_2);
    if(newStateButton2==LOW && oldStateButton2==HIGH){
        Serial.println("button 2 pressed");
        joy();
    }
    bool newStateButton3 = digitalRead(BUTTON_PIN_3);
    if(newStateButton3==LOW && oldStateButton3==HIGH){
        Serial.println("button 3 pressed");
        curiosity();
    }
    bool newStateButton4 = digitalRead(BUTTON_PIN_4);
    if(newStateButton4==LOW && oldStateButton4==HIGH){
        Serial.println("button 4 pressed");
        frustration();
    }
    bool newStateButton5 = digitalRead(BUTTON_PIN_5);
    if(newStateButton5==LOW && oldStateButton5==HIGH){
        Serial.println("button 5 pressed");
        anticipation();
    }
}

void hesitancy(){
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
}
