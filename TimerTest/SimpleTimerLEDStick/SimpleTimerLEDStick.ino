#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

unsigned long RunTime;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  LEDStick.begin();

   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  RunTime = millis();

  Serial.print("RunTime: "); // prints time since program started
  Serial.println(RunTime);
  
 
  //Don't put LED command (stick) within while loop, it get stuck
  
  LEDStick.setLEDColor(50,50,50); //Turn on LED stick
  digitalWrite(LED_BUILTIN, HIGH); //turn on embedded LED
  
  while(millis() - RunTime < 5000){
      //wait 5000 ms
   }

  RunTime = millis();

  LEDStick.LEDOff();   // turn LED Sticks off
  digitalWrite(LED_BUILTIN, LOW); //turn off embedded LED
  
  while(millis() - RunTime < 2000){
      //wait approx. [period] ms    
   }
}
