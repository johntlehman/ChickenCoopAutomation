#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

int analogPin = A0; // Solar panel voltage 
int sensorValue = 0; // variable to store the value read
float voltage;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  //Start up communication with the LED Stick
  if (LEDStick.begin() == false){
    Serial.println("Qwiic LED Stick failed to begin. Please check wiring and try again!");
    while(1);
  }

  Serial.println("Qwiic LED Stick ready!");
}

void loop() {
  delay(250);
  sensorValue = analogRead(analogPin);  // read the input pin
  voltage = (sensorValue * 5.0 / 1023.0);

  if(voltage < 0.5)
    //Turn on LEDs and delay 250 millis
    LEDStick.setLEDColor(50, 50, 50);
  
  else
  //Turn off all LEDs
  LEDStick.LEDOff();
  

}
