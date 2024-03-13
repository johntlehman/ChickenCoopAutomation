//Include statements
#include <SparkFun_RV1805.h> //Library for RTC

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class

//Declare variables
unsigned long lightBeforeSunriseMinutes; //duration in minutes that lights will be on before sunrise
unsigned long noAlarmBefore; //hhmm Lights will not turn on before this time
int dayCounter = 0;

String currentDate;
String currentTime;

byte currentHour;
byte currentMinute;
byte currentSecond;
byte alarmHour;
byte alarmMinute;
byte alarmSecond;

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
  currentHour = rtc.getHours();
  currentMinute = rtc.getMinutes();
  currentSecond = rtc.getSeconds();

  alarmHour = currentHour;
  alarmMinute = currentMinute;
  alarmSecond = currentSecond + 15; //add 15 seconds

  //Set the next day's alarm
  rtc.setAlarm(alarmSecond, alarmMinute, alarmHour, 0, 0);
  rtc.setAlarmMode(6); //6 = Alarm goes off every minute
  rtc.enableInterrupt(INTERRUPT_AIE); //Enable the Alarm Interrupt

  //DEBUG -  Print alarm date and time (Note that there is no year alarm register)
  char alarmBuffer[20];
  sprintf(alarmBuffer, "2020-%02d-%02dT%02d:%02d:%02d",
          rtc.getAlarmMonth(),
          rtc.getAlarmDate(),
          rtc.getAlarmHours(),
          rtc.getAlarmMinutes(),
          rtc.getAlarmSeconds());
  Serial.println(alarmBuffer);

//Put Board to sleep and wait for alarm interrupt

  //Junk Code
  delay(60000);
  Serial.println("I just waited 60 more seconds");

//Alarm Interrupt - check that it's dark, check battery. If dark and battery >x%, turn lights on.
//Sunrise Detected - set alarm for next day and put the board to sleep

}

// Function definitions

void printStatus(){ //Prints status of all variables upon user request
  Serial.println(currentDate + " " + currentTime);
}