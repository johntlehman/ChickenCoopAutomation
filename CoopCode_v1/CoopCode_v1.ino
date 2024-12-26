//Include necessary libraries
#include <SparkFun_RV1805.h>; //Library for RTC
#include <Qwiic_LED_Stick.h>; //Library for LED stick
#include <LowPower.h> //Library for power saving

RV1805 RTC; //instantiate an object 'rtc' of the RV1805 class
LED LEDStick; //Create an object of the LED class

//Declare variables
int dayCounter = 0;

unsigned long currentEpoch;
unsigned long sunriseEpoch;
unsigned long sunsetEpoch;
unsigned long wakeyEpoch;

const char analogPinLightSensor = A0; // Read light sensor voltage at analog pin
const char analogPinBattery = A3; //Read battery voltage at analog pin

//Code compares following two values and selects value which results in later WakeyTime
const unsigned long delayFromSunset = 10; //*3600; //Minimum time without light used in fall/spring. default 10 hours (stored in seconds)
const unsigned long delayFromSunrise = 22; //*3600; //Maximum Light-On time. used in midwinter. default of 22 hours (stored in seconds) results in lights on for 2 hours

float lightSensorVoltage; //used to track current light sensor voltage
const float daylightVoltage = 3.3; //above this voltage is considered 'daylight'
const float nightVoltage = 1.5; //below this voltage is considered 'night'

float batteryVoltage; //used to track current battery voltage
const float minBatteryVoltage = 11.8; //minimum battery voltage to enable lights

//Variables for LED RGB values
int LEDRed; 
int LEDGreen;
int LEDBlue;
const int LEDRatioGreen_Red = 0.83; //Ratio of Green to Red
const int LEDRatioBlue_Red = 0.377; //Ratio of Blue to Red
const int LEDBrightnessSetpoint = 200; //Brightness Level for LEDs, 255 is HW limit


void setup() 
{  
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Serial Comms Online");

  if (LEDStick.begin() == false)
  {
    Serial.println("Something went wrong with LEDStick");
  }

  else 
  { 
    Serial.println("LEDStick online!");
  }

  if (RTC.begin() == false) 
  {
    Serial.println("Something went wrong with RTC");
  }  
  
  else 
  { 
    Serial.println("RTC online!");
  }
  
  if (RTC.setToCompilerTime() == false) 
  {
    Serial.println("Something went wrong setting the time");
  }
  
  RTC.set24Hour(); //set the RTC to use 24 hour time

  //Use the time from the Arduino compiler (build time) to set the RTC
  //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (RTC.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.println("RTC failed to update");
  }
}

void loop() 
{  
  //Sunrise time, alarm goes off
  wakeyEpoch = GetCurrentEpoch(); //call function to update RTC with current Epoch and store it as wakeytime
  batteryVoltage = GetBatteryVoltage(); //Get battery voltage
  lightSensorVoltage = GetLightSensorVoltage(); //Get light sensor voltage

  PrintStatus(); //Print status of all variables
  Serial.println("Wakey wakey sleepy chickens! It's day " + String(dayCounter));

  lightSensorVoltage = 1.0; //remove after debug
  batteryVoltage = 12.0; //remove after debug
  //If it's dark and this is not the first loop, turn the lights on
  if (dayCounter >= 0 & lightSensorVoltage < daylightVoltage & batteryVoltage > minBatteryVoltage)
  {
    LEDRed = 0;
    
    //turn on lights
    while(LEDRed < LEDBrightnessSetpoint)
    {
      //digitalWrite(LED_BUILTIN, HIGH);   // turn the board LED on (HIGH is the voltage level)
      LEDRed = LEDRed + 20;
      LEDGreen = LEDRed*LEDRatioGreen_Red;
      LEDBlue = LEDRed*LEDRatioBlue_Red;
      LEDStick.setLEDColor(LEDRed, LEDGreen, LEDBlue); //Set LED stick values
      Serial.println("LEDRed: " + String(LEDRed));
      delay(250);
    }

    Serial.println("Lights on!");
  }

  else
  {
    LEDStick.LEDOff(); //make sure LED stick is off if conditions aren't met.
  }

  dayCounter++; //increment day counter
  
  //Monitor for sunrise and battery level
  while (lightSensorVoltage < daylightVoltage & batteryVoltage > minBatteryVoltage) //& time is less than sunrise time?
  {
    //update light sensor voltage and battery voltage
    lightSensorVoltage = GetLightSensorVoltage();
    batteryVoltage = GetBatteryVoltage();
    Serial.println("Waiting for sunrise");
    PrintStatus(); //print for debugging

    delay(3000); //remove after debug
    lightSensorVoltage = 3.3; //remove after debug
  }

  //Sunrise occurs - store sunrise time and turn off the lights
  Serial.println("Sunrise!!");
  LEDStick.LEDOff();
  sunriseEpoch = GetCurrentEpoch();
  
  //Monitor for sunset
  while (lightSensorVoltage > nightVoltage) //& time is less than sunset time?
  {
    CatNap();

    //check light sensor voltage
    lightSensorVoltage = GetLightSensorVoltage();

    Serial.println("Waiting for sunset. Current light sensor voltage: " + String(lightSensorVoltage,2)); //remove after debug

    lightSensorVoltage = 1.0; //remove after debug
  }
  
  //Sunset occurs, store next wakeup time
  sunsetEpoch = GetCurrentEpoch();
  unsigned long sunriseWakey = sunriseEpoch + delayFromSunrise;
  unsigned long sunsetWakey = sunsetEpoch + delayFromSunset;

  if (sunriseWakey > sunsetWakey)
  {
    wakeyEpoch = sunriseWakey;
    Serial.println("sunriseWakey > sunsetWakey, Next wakeup time: " + String(wakeyEpoch));
  }

  else
  {
    wakeyEpoch = sunsetWakey;
    Serial.println("sunsetWakey > sunriseWakey, Next wakeup time: " + String(wakeyEpoch));
  }

  //Wait for wakeup time
  while (currentEpoch < wakeyEpoch)
  {
    currentEpoch = GetCurrentEpoch();
    Serial.println("Waiting for next wakeup time. Current Epoch: " + String(currentEpoch) + " Wakey Epoch: " + String(wakeyEpoch)); 
    
    CatNap();
  }
}

// Function definitions----------------------------------------------
void PrintStatus()
{ //Prints status of all variables upon user request
  float statusLightSensorVoltage = GetLightSensorVoltage();
  float statusBatteryVoltage = GetBatteryVoltage();
  unsigned long statusEpoch = GetCurrentEpoch();

  Serial.println("Current Light Sensor Voltage: " + String(statusLightSensorVoltage,2));
  Serial.println("Current Battery Voltage: " + String(statusBatteryVoltage,2));
  Serial.println("Current Epoch: " + String(statusEpoch));
}

void CatNap()
{
  delay(200); //brief delay to finish printing or any other tasks

  //Testing a lowpower state ATmega328P, ATmega168. May need to leave some things on for functionality
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF); //sleep 8 seconds
}

float GetLightSensorVoltage()
{
  float lightSensorValue = 0;
  float lightSensorCalc;
  float lightSensorSum = 0;
  float averageLightSensorVoltage = 0;
    
  for (int i = 1; i < 5; i++){
    lightSensorValue = analogRead(analogPinLightSensor);  // read the input pin
    lightSensorCalc = lightSensorValue * (3.3 / 1023.0);
    lightSensorSum = lightSensorSum + lightSensorCalc;
    averageLightSensorVoltage = lightSensorSum/i;
    delay(500);
  }

  return averageLightSensorVoltage;
}
// Need to update battery voltage calc 
float GetBatteryVoltage()
{  
  int batteryValue = 0; //variable to store battery voltage raw value
  float batteryVoltageCalc = 12.0; //update with actual calc

  return batteryVoltageCalc;
}

unsigned long GetCurrentEpoch()
{
  if (RTC.updateTime() == false) //Updates the time variables from RTC
  {
  Serial.println("RTC failed to update");
  }
  
  currentEpoch = RTC.getEpoch();
  return currentEpoch;
}