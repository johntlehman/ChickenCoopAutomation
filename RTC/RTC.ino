#include <SparkFun_RV1805.h>;

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class

//The below variables control what the date will be set to
int testHund = 50;
int testSec = 2;
int testMinute = 18;
int testHour = 7;
int testDate = 25;
int testMonth = 6;
int testYear = 2018;
int testDay = 5;

unsigned long currentEpoch;
int currentDate;
byte currentMonth;
byte currentYear;
byte currentHour;
byte currentMinute;
byte currentSecond;

unsigned long alarmEpoch;
byte alarmMonth;
byte alarmDate;
byte alarmHour;
byte alarmMinute;
byte alarmSecond;

String currentDateString;
String currentTimeString;

void setup() {

  Wire.begin();

  Serial.begin(115200);
  Serial.println("Read Time from RTC Example");

  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
  }

  //Use the time from the Arduino compiler (build time) to set the RTC
  //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (rtc.setToCompilerTime() == false) {
    Serial.println("Something went wrong setting the time");
  }

  //Uncomment the below code to set the RTC to your own time
  /*if (rtc.setTime(hund, sec, minute, hour, date, month, year, day) == false) {
    Serial.println("Something went wrong setting the time");
    }*/
  
  rtc.set24Hour(); //set the RTC to use 24 hour time
  Serial.println("RTC online!");
}

void loop() {
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.println("RTC failed to update");
  }

  currentDateString = rtc.stringDateUSA();
  currentTimeString = rtc.stringTime();
  Serial.println(currentDate + " " + currentTimeString);
  
  currentEpoch = rtc.getEpoch();
  currentDate = rtc.getDate();
  currentMonth = rtc.getMonth();
  currentYear = rtc.getYear();
  currentHour = rtc.getHours();
  currentMinute = rtc.getMinutes();
  currentSecond = rtc.getSeconds();

  Serial.print("Epoch ");
  Serial.println(currentEpoch);
  Serial.print("Month ");
  Serial.println(currentMonth);
  Serial.print("Date ");
  Serial.println(currentDate);
  Serial.print("Year ");
  Serial.println(currentYear);
  Serial.print("Hour ");
  Serial.println(currentHour);
  Serial.print("Minute ");
  Serial.println(currentMinute);
  Serial.print("Second ");
  Serial.println(currentSecond);

  alarmEpoch = currentEpoch + 15;
  
  Serial.print("Alarm Epoch ");
  Serial.println(alarmEpoch);

  alarmMonth = currentMonth;
  alarmDate = currentDate;
  alarmHour = currentHour;
  alarmMinute = currentMinute;
  alarmSecond = currentSecond + 15; //add 15 seconds
  
  // Set the alarm with the values initialized above
  rtc.setAlarm(alarmSecond, alarmMinute, alarmHour, alarmDate, alarmMonth);

  while (rtc.getEpoch() < alarmEpoch)
  {
    delay(50);
    if (rtc.updateTime() == false) //Updates the time variables from RTC
    {
    Serial.println("RTC failed to update");
    }
  }

  Serial.println("alarm bitches!");
}
  
  