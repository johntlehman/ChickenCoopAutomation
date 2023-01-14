//CoopCode v0
//Code turns on lights in a chicken coop when natural daylight <14 hours
//Max light burntime is 2 hours
//Lights turn on before sunrise
//Solar panel is used to determine day/night
//System is powered by solar panel, charge controller, and battery
//Behavior
//System started when it's dark - skips next light on cycle and resumes the following morning
//System started when it's light - calculates light-on time at sunset (delay from sunset)

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class
int n = 0;

void setup() {
  Serial.begin(115200); //run at 115200 for LED stick
  Wire.begin(); //needed for LED stick
  LEDStick.begin(); //needed for LED stick
  pinMode(LED_BUILTIN, OUTPUT); //initialize digital pin LED_BUILTIN as an output.
  
  LEDStick.LEDOff();
  delay(2000);
}

//Daily loop
void loop() {
Serial.print("Loop completions:");
Serial.println(n);
Serial.print("time in ms");
Serial.println(millis());

int LEDRed = 100;
int LEDGreen = 0;
int LEDBlue = 0;

  //Turn on LED
  for(int i = 0; i < 4; i++) {
    digitalWrite(LED_BUILTIN, LOW);   // turn the board LED on (HIGH is the voltage level)
    LEDRed = LEDRed + 50;
    LEDGreen = LEDRed*0.83; //Ratio for Orange
    LEDBlue = LEDRed*0.377;
    LEDStick.setLEDColor(LEDRed, LEDGreen, LEDBlue); //Turn on LED stick
    delay(10000);
    LEDStick.LEDOff();
    Wire.end();
    Serial.end();
    delay(2000);
    Serial.begin(115200);
    Wire.begin();
    LEDStick.begin();

    n++;

  }

}
  
  
