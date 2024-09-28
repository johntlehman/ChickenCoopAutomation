//Testing of full system (Solar panel, fuel gauge, and RTC) with solar panel and battery connected.

//Initialize Variables
#include "Wire.h" //Needed for serial
#include "SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h" //Needed for fuel gauge
#include "LowPower.h" //Load library for power saving
#include <SparkFun_RV1805.h> //include library for Sparkfun RTC

SFE_MAX1704X lipo(MAX1704X_MAX17043);  //instantiate an object 'lipo' of the SFE_MAX1704X (Fuel Gauge) class
RV1805 rtc; //instantiate an object 'rtc' of the RV1805 (RTC) class

double voltage = 0; // Variable to keep track of LiPo voltage
double soc = 0; // Variable to keep track of LiPo state-of-charge (SOC)
double changeRate = 0;
bool alert; // Variable to keep track of whether alert has been triggered

byte currentMonth;
byte currentDate;
byte currentYear;
byte currentHour;
byte currentMinute;
byte currentSecond;

void setup() {

  Serial.begin(115200); // Start serial, to output debug data
  Wire.begin();

  // Set up the MAX17043 LiPo fuel gauge:
  if (lipo.begin() == false) // Connect to the MAX17043 using the default wire port
  {
    Serial.println(F("MAX17043 Fuel Gauge not detected. Please check wiring. Freezing."));
    while (1);
  }
	
  // Quick start restarts the MAX17043 in hopes of getting a more accurate guess for the SOC.
	lipo.quickStart();

	// We can set an interrupt to alert when the battery SoC gets too low.
	// We can alert at anywhere between 1% - 32%:
	lipo.setThreshold(20); // Set alert threshold to 20%.

  if (rtc.begin() == false) {
    Serial.println("Something went wrong with RTC, check wiring");
  }

  //Use the time from the Arduino compiler (build time) to set the RTC
  //Keep in mind that Arduino does not get the new compiler time every time it compiles. to ensure the proper time is loaded, open up a fresh version of the IDE and load the sketch.
  if (rtc.setToCompilerTime() == false) {
    Serial.println("Something went wrong setting the time");
  }
  
  rtc.set24Hour(); //set the RTC to use 24 hour time
  Serial.println("RTC online!");
}

void loop() {
  //wake the board up

  //print battery %
  // lipo.getVoltage() returns a voltage value (e.g. 3.93)
  voltage = lipo.getVoltage();
  // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
  soc = lipo.getSOC();
  changeRate = lipo.getChangeRate();
  // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
  alert = lipo.getAlert();

  // Print the variables:
  Serial.print("Voltage: ");
  Serial.print(voltage);  // Print the battery voltage
  Serial.println(" V");
  Serial.print("Percentage: ");
  Serial.print(soc); // Print the battery state of charge
  Serial.println(" %");
  Serial.print("Change Rate (%/hr): ");
  Serial.println(changeRate);
  Serial.print("Alert: ");
  Serial.println(alert);
  Serial.println();

  //print current time
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.println("RTC failed to update");
  }
  
  currentMonth = rtc.getMonth();
  currentDate = rtc.getDate();
  currentYear = rtc.getYear();
  currentHour = rtc.getHours();
  currentMinute = rtc.getMinutes();
  currentSecond = rtc.getSeconds();

  Serial.print("Month ");
  Serial.println(currentMonth);
  Serial.print("Day ");
  Serial.println(currentDate);
  Serial.print("Year ");
  Serial.println(currentYear);
  Serial.print("Hour ");
  Serial.println(currentHour);
  Serial.print("Minute ");
  Serial.println(currentMinute);
  Serial.print("Second ");
  Serial.println(currentSecond);
  Serial.println();
  Serial.println();

  //delay long enough to print
  delay(250);
  
  //put the board in a low power state
  //LowPower.powerDown(SLEEP_8S,ADC_OFF,BOD_OFF);

  //Testing another lowpower state ATmega328P, ATmega168
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  
  //delay 5 seconds
  //delay(5000);

}