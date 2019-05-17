// This sketch contains 5 lighting animations for an 8-LED Neopixel stick, triggered by 5 seperate buttons-- 
// written for user testing purposes for the Emotional Machines project -- 
// By Emma Young - BBC R&D
// once it gets a '1' over serial it starts the heartbeat and keeps going.

#include <Adafruit_NeoPixel.h>

#define LED_PIN 9 //digital pin to connect the LED strip
#define LED_COUNT 8


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int showType = 0;

int state = 0;

void setup() {
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50); // Set BRIGHTNESS to 1/5 (to save your eyes, uncomment if diffusing light)
  //for debugging
  Serial.begin(115200);
}

void loop() {

 //Serial.println(state);
 checkSerial();


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
  }
  
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
          Serial.println("heartbeat invoked");
          heartbeat();    
        }
    }  
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
