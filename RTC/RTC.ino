#include <SparkFun_RV1805.h>

RV1805 rtc; //instantiate an object 'rtc' of the RV1805 class

//The below variables control what the date will be set to
int hund = 50;
int sec = 2;
int minute = 18;
int hour = 7;
int date = 25;
int month = 6;
int year = 2018;
int day = 5;

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
    Serial.print("RTC failed to update");
  }
  
  String currentDate = rtc.stringDateUSA();
  String currentTime = rtc.stringTime();
  Serial.println(currentDate + " " + currentTime);
}