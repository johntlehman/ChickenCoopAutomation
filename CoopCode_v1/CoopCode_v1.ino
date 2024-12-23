//Include statements
#include <SparkFun_RV1805.h>; //Library for RTC
#include <Qwiic_LED_Stick.h>; //Library for LED stick

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class
LED LEDStick; //Create an object of the LED class

//Declare variables
unsigned long lightBeforeSunriseMinutes; //duration in minutes that lights will be on before sunrise
unsigned long noAlarmBefore; //hhmm Lights will not turn on before this time
int dayCounter = 0;

unsigned long currentEpoch;
unsigned long wakeyEpoch;
unsigned long sunriseEpoch;
unsigned long sunsetEpoch;

const char analogPinLightSensor = A0; // Read solar panel voltage at analog pin
const char analogPinBattery = A3; //Read battery voltage at analog pin

//Code compares following two values and selects value which results in later WakeyTime
const unsigned long delayFromSunset = 10*3600; //Minimum time without light used in fall/spring. default 10 hours (stored in seconds)
const unsigned long delayFromSunrise = 22*3600; //Maximum Light-On time. used in midwinter. default of 22 hours (stored in seconds) results in lights on for 2 hours

float lightSensorVoltage; //used to track current light sensor voltage
const float daylightVoltage = 3.3; //above this voltage is considered 'daylight'
const float nightVoltage = 1.5; //below this voltage is considered 'night'

float batteryVoltage; //used to track current battery voltage
const float minBatteryVoltage = 11.8; //minimum battery voltage to enable lights

void setup() 
{  
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Serial Comms Online");

  if (rtc.begin() == false) 
  {
    Serial.println("Something went wrong with RTC, check wiring");
  }  
  
  else 
  { 
    Serial.println("RTC online!");
  }
  
  if (rtc.setToCompilerTime() == false) 
  {
    Serial.println("Something went wrong setting the time");
  }
  
  rtc.set24Hour(); //set the RTC to use 24 hour time

  //Use the time from the Arduino compiler (build time) to set the RTC
  //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  }
}

void loop() 
{  
  //Waiting for sunrise, as code returns to loop start after alarm is set
  
  //alarm goes off

  //call function to update RTC with current Epoch and store it as wakeytime
  wakeyEpoch = GetCurrentEpoch();

  //Get battery voltage
  batteryVoltage = GetBatteryVoltage();

  //Get light sensor voltage
  lightSensorVoltage = GetLightSensorVoltage();

  PrintStatus(); //Print status of all variables
  Seril.println("Wakey wakey sleepy chickens!");

  //If it's dark and this is not the first loop, turn the lights on
  if (dayCounter > 0 & lightSensorVoltage < daylightVoltage & batteryVoltage > minBatteryVoltage)
  {
    //turn on lights
    Serial.println("Lights on!");
  }
  
  //Monitor for sunrise and battery level
  while (lightSensorVoltage < daylightVoltage & batteryVoltage > minBatteryVoltage) //& time is less than sunrise time?
  {
      //sleep 8 seconds ish
      

      //update light sensor voltage and battery voltage
      lightSensorVoltage = GetLightSensorVoltage();
      batteryVoltage = GetBatteryVoltage();
      Serial.println("Waiting for sunrise");
      PrintStatus(); //print for debugging
  }

  //Sunrise occurs - store sunrise time, next wakeup time, and turn off the lights
  sunriseEpoch = GetCurrentEpoch();
  
  //Monitor for sunset
  while (lightSensorVoltage > nightVoltage) //& time is less than sunset time?
  {
    //sleep 8 seconds ish
    lightSensorVoltage = GetLightSensorVoltage();
  }
  
  //Sunset occurs, store next wakeup time
  sunsetEpoch = GetCurrentEpoch();
  unsigned long sunriseWakey = sunriseEpoch + delayFromSunrise;
  unsigned long sunsetWakey = sunsetEpoch + delayFromSunset;

  if (sunriseWakey > sunsetWakey)
  {
    wakeyEpoch = sunriseWakey;
  }

  else
  {
    wakeyEpoch = sunsetWakey;
  }

  //Wait for wakeup time
  while (currentEpoch < wakeyEpoch)
  {
    //sleep 8 seconds ish
    currentEpoch = GetCurrentEpoch();
  }
  
  //check that it's dark, check battery. If dark and battery >x%, turn lights on.
  //Sunrise Detected - set alarm for next day and put the board to sleep

  delay(1000); //delay for debug
}

// Function definitions----------------------------------------------
void PrintStatus()
{ //Prints status of all variables upon user request
  float statusLightSensorVoltage = GetLightSensorVoltage();
  float statusBatteryVoltage = GetBatteryVoltage();
  unsigned long statusEpoch = GetCurrentEpoch();

  Serial.print("Current Light Sensor Voltage: " + String(lightSensorVoltage,2));
  Serial.print("Current Battery Voltage: " + String(batteryVoltage,2));
  Serial.print("Current Epoch: " + String(currentEpoch));
  
  //Serial.printf("Current Light Sensor Voltage: %.2f", lightSensorVoltage);
  // Serial.println("Current Light Sensor Voltage: " + lightSensorVoltage);
  // Serial.println("Current Battery Voltage: " + batteryVoltage);
  // Serial.println("Current Epoch: " + currentEpoch);
}

float GetLightSensorVoltage()
{
    float lightSensorValue = 0;
    float lightSensorCalc;
    float lightSensorSum = 0;
    float averageLightSensorVoltage = 0;
    
    for (int i = 1; i < 11; i++){
      lightSensorValue = analogRead(analogPinLightSensor);  // read the input pin
      lightSensorCalc = lightSensorValue * (3.3 / 1023.0);
      lightSensorSum = lightSensorSum + lightSensorCalc;
      averageLightSensorVoltage = lightSensorSum/i;
      Serial.println(averageLightSensorVoltage); //remove after debug
      delay(500);
    }

    return averageLightSensorVoltage;

}
// Need to update battery voltage calc 
float GetBatteryVoltage()
{  
  int batteryValue = 0; //variable to store battery voltage raw value
  float batteryVoltageCalc;

  return batteryVoltageCalc;
}

unsigned long GetCurrentEpoch()
{
    if (rtc.updateTime() == false) //Updates the time variables from RTC
    {
    Serial.println("RTC failed to update");
    }
  
  currentEpoch = rtc.getEpoch();
  return currentEpoch;
}