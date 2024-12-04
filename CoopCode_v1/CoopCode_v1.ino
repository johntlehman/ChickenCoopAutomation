//Include statements
#include <SparkFun_RV1805.h>; //Library for RTC
#include <Qwiic_LED_Stick.h>; //Library for LED stick

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class
LED LEDStick; //Create an object of the LED class

//Declare variables
unsigned long lightBeforeSunriseMinutes; //duration in minutes that lights will be on before sunrise
unsigned long noAlarmBefore; //hhmm Lights will not turn on before this time
int dayCounter = 0;

//Use the time_t type to store timestamps in seconds. Allows use of TimeLib library functions
unsigned long currentEpoch;
unsigned long wakeyEpoch;
unsigned long sunriseEpoch;
unsigned long sunsetEpoch;

//Code compares following two values and selects value which results in later WakeyTime
const unsigned long delayFromSunset = 10*3600; //Minimum time without light used in fall/spring. default 10 hours (stored in seconds)
const unsigned long delayFromSunrise = 22*3600; //Maximum Light-On time. used in midwinter. default of 22 hours (stored in seconds) results in lights on for 2 hours

void setup() {  
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Serial Comms Online");

  if (rtc.begin() == false) {
    Serial.println("Something went wrong with RTC, check wiring");
  }  
  else { 
      Serial.println("RTC online!");
    }
  
  if (rtc.setToCompilerTime() == false) {
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

void loop() {  
  //call function to update RTC with current Epoch, then store it as wakeytime
  GetCurrentEpoch();
  wakeyEpoch = currentEpoch;

  //Store Wakeup Time

  //Check light sensor reading

  //If it's dark and this is not the first loop, turn the lights on

  //Leave lights on while monitoring for sunrise and battery level

  //Sunrise occurs - store sunrise time, next wakeup time, and turn off the lights

  //Monitor for sunset

  //Sunset occurs, store next wakeup time

  //Wait for wakeup time


  // Print the variables:
  PrintStatus();

  //first 
  
  //check that it's dark, check battery. If dark and battery >x%, turn lights on.
  //Sunrise Detected - set alarm for next day and put the board to sleep

  delay(1000); //delay for debug
}

// Function definitions
void PrintStatus(){ //Prints status of all variables upon user request

  ReadLightSensor();
  GetCurrentEpoch();

}

void ReadLightSensor(){
    
    const char analogPinLightSensor = A3; // Read solar panel voltage at analog pin A0
    
    unsigned long LoopStartTime = millis();
    float lightSensorValue = 0;
    float lightSensorCalc;
    float lightSensorSum = 0;
    float averageLightSensorVoltage = 0;
    
    for (int i = 1; i < 11; i++){
      lightSensorValue = analogRead(analogPinLightSensor);  // read the input pin
      lightSensorCalc = lightSensorValue * (3.3 / 1023.0);
      lightSensorSum = lightSensorSum + lightSensorCalc;
      averageLightSensorVoltage = lightSensorSum/i;
      Serial.println(averageLightSensorVoltage);
      delay(500);
    }
    
    unsigned long LoopTime = millis()-LoopStartTime;

    Serial.print("Average Light Sensor Voltage Last ");
    Serial.print(LoopTime/1000);
    Serial.print(" seconds: ");
    Serial.println(averageLightSensorVoltage);

}
// Need to update battery voltage calc 
void ReadBatteryVoltage(){
    const char analogPinBattery = A3; //Read battery voltage at analog pin A3
    
    int batteryValue = 0; //variable to store battery voltage raw value
    float batteryVoltageCalc;
}

void GetCurrentEpoch(){
    if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.println("RTC failed to update");
  }
  
  currentEpoch = rtc.getEpoch();
  Serial.print("GetCurrentEpoch ran successfully. Epoch: ");
  Serial.println(currentEpoch);
}