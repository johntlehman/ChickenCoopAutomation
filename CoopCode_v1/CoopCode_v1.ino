//Include statements
#include <SparkFun_RV1805.h> //Library for RTC

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class

//Declare variables
unsigned long lightBeforeSunriseMinutes; //duration in minutes that lights will be on before sunrise
unsigned long noAlarmBefore; //hhmm Lights will not turn on before this time
int dayCounter = 0;

String currentDate;
String currentTime;

const byte interruptPin = 2;

void setup() {  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), printStatus, LOW); //enable an interrupt pin to print status when grounded
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

//---------------------Get Started with Actual Code--------------------------
//Set first alarm for 6 a.m. the following morning
}

void loop() {
  //Use the time from the Arduino compiler (build time) to set the RTC
  //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  }
  currentDate = rtc.stringDateUSA();
  currentTime = rtc.stringTime();

  //Junk Code
  delay(5000);
  Serial.println("I just waited 5 more seconds");

//Put Board to sleep and wait for alarm interrupt

//Alarm Interrupt - check that it's dark, check battery. If dark and battery >x%, turn lights on.
//Sunrise Detected - set alarm for next day and put the board to sleep

}

// Function definitions

void printStatus(){ //Prints status of all variables upon user request
  Serial.println(currentDate + " " + currentTime);
}