//Include statements
#include <SparkFun_RV1805.h> //Library for RTC
#include "SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h"

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class
SFE_MAX1704X lipo(MAX1704X_MAX17043);  //Create an object called 'lipo' of the SFE_MAX1704X class

//Declare variables
unsigned long lightBeforeSunriseMinutes; //duration in minutes that lights will be on before sunrise
unsigned long noAlarmBefore; //hhmm Lights will not turn on before this time
int dayCounter = 0;

String currentDateString;
String currentTimeString;

byte currentMonth;
byte currentDate;
byte currentHour;
byte currentMinute;
byte currentSecond;

byte alarmMonth;
byte alarmDate;
byte alarmHour;
byte alarmMinute;
byte alarmSecond;

const byte interruptPin = 2;

double voltage = 0; // Variable to keep track of LiPo voltage
double soc = 0; // Variable to keep track of LiPo state-of-charge (SOC)
bool alert; // Variable to keep track of whether alert has been triggered

void setup() {  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptPrint, LOW); //enable an interrupt pin to print a statement when grounded
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

  lipo.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  // Set up the MAX17043 LiPo fuel gauge:
  if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
  {
    Serial.println(F("MAX17043 not detected. Please check wiring. Freezing."));
    while (1)
      ;
  }

	// Quick start restarts the MAX17043 in hopes of getting a more accurate
	// guess for the SOC.
	lipo.quickStart();

	// We can set an interrupt to alert when the battery SoC gets too low.
	// We can alert at anywhere between 1% - 32%:
	lipo.setThreshold(20); // Set alert threshold to 20%.

}

void loop() {
  //Use the time from the Arduino compiler (build time) to set the RTC
  //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  }

  currentTimeString = rtc.stringTime();
  currentDateString = rtc.stringDateUSA();
  
  currentMonth = rtc.getMonth();
  currentDate = rtc.getDate();
  currentHour = rtc.getHours();
  currentMinute = rtc.getMinutes();
  currentSecond = rtc.getSeconds();

  alarmMonth = currentMonth;
  alarmDate = currentDate;
  alarmHour = currentHour;
  alarmMinute = currentMinute;
  alarmSecond = currentSecond + 15; //add 15 seconds

  if (alarmSecond >= 60)
  {
    alarmSecond = 59;
  }

  //Set the next day's alarm
  rtc.setAlarm(alarmSecond, alarmMinute, alarmHour, alarmDate, alarmMonth);
  rtc.setAlarmMode(6); //6 = Alarm goes off every minute
  rtc.enableInterrupt(INTERRUPT_AIE); //Enable the Alarm Interrupt

  // lipo.getVoltage() returns a voltage value (e.g. 3.93)
  voltage = lipo.getVoltage();
  // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
  soc = lipo.getSOC();
  // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
  alert = lipo.getAlert();

  // Print the variables:
  printStatus();

  Serial.print("Voltage: ");
  Serial.print(voltage);  // Print the battery voltage
  Serial.println(" V");

  Serial.print("Percentage: ");
  Serial.print(soc); // Print the battery state of charge
  Serial.println(" %");

  Serial.print("Alert: ");
  Serial.println(alert);
  Serial.println();

  //Put Board to sleep and wait for alarm interrupt

  //Junk Code
  delay(60000);
  Serial.println("I just waited 60 more seconds");
  printStatus();

  //Alarm Interrupt - check that it's dark, check battery. If dark and battery >x%, turn lights on.
  //Sunrise Detected - set alarm for next day and put the board to sleep

}

// Function definitions
void printStatus(){ //Prints status of all variables upon user request
  Serial.println(currentDateString + " " + currentTimeString);

  //DEBUG -  Print alarm date and time (Note that there is no year alarm register)
  char alarmBuffer[20];
  sprintf(alarmBuffer, "2024-%02d-%02dT%02d:%02d:%02d",
          rtc.getAlarmMonth(),
          rtc.getAlarmDate(),
          rtc.getAlarmHours(),
          rtc.getAlarmMinutes(),
          rtc.getAlarmSeconds());
  Serial.println("Alarm is set for: ");
  Serial.println(alarmBuffer);
}

void interruptPrint(){ //Interrupt print statement
  Serial.println("Interrupt triggered bitches!");
}