//LowPower Test
//Check status of Pin A0 every 8 seconds. If Low turn LED stick on, If High Leave Off

#include <Wire.h> //Used for LED stick
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick
#include <LowPower.h> //Load library for power saving

//#include < avr/power.h>
//#include < avr/sleep.h>

LED LEDStick; //Create an object of the LED class

//declare test variables
int analogPin = A0; // Read solar panel voltage at analog pin A0
int sensorValue = 0; // variable to store the value read
float voltage; //variable to convert reading to voltage
float NightVoltage = .75; //this or lower voltage on solar panel determines night

void setup() {
  Serial.begin(115200); //run at 115200 for LED stick, 9600 for serial monitor
  Wire.begin(); //needed for LED stick
  LEDStick.begin(); //needed for LED stick

  CLKPR = 0x80;
  CLKPR = 0x02; //Set registers to lowest possible clock speed 62.6 kHz

}

void loop() {

  //LEDStick.LEDOff();   // turn LED Sticks off

  //High voltage (daytime) put board to sleep
  
  //while(voltage > NightVoltage){
    //sensorValue = analogRead(analogPin);  // read the input pin
    //voltage = (sensorValue * 5.0 / 1023.0);
    //Serial.print("voltage: ");
    //Serial.println(voltage);
    
    //check that millis still works
    Serial.print("millis: ");
    Serial.println(millis());
    Serial.println("Going to sleeep zzzz");
    delay(500); //allow time to print
    // ATmega328P, ATmega168 - Sparkfun Redboard plus uses the ATMega328P
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                  SPI_OFF, USART0_OFF, TWI_OFF);
    //LowPower.idle(); //fails
    //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    //LowPower.powerSave(SLEEP_8S, ADC_OFF, BOD_OFF, TIMER2_ON);
    //LowPower.powerStandby(SLEEP_8S, ADC_OFF, BOD_OFF);
    //LowPower.standby();  //Why the EFF doesn't this work?
    //LowPower.idle();
  //}
  
  //LEDStick.setLEDColor(50, 50, 50); //Turn on LED stick
  
  //Low voltage (night time) keep board awake and monitor voltage
  //while(voltage < NightVoltage){
      //sensorValue = analogRead(analogPin);  // read the input pin
      //voltage = (sensorValue * 5.0 / 1023.0);
      //Serial.print("voltage: ");
      //Serial.println(voltage);
      //delay(2000);
  //}

}
