//CoopCode v0
//Code turns on lights in a chicken coop when natural daylight <14 hours
//Max light burntime is 2 hours
//Lights turn on before sunrise
//Solar panel is used to determine day/night
//System is powered by solar panel, charge controller, and battery
//Behavior
//System started when it's dark - skips next light on cycle and resumes the following morning
//System started when it's light - calculates light-on time at sunset (delay from sunset)

#include <Wire.h> //Used for LED stick
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick
#include <LowPower.h> //Load library for power saving
#include "RunningAverage.h" //included to average sensor values

LED LEDStick; //Create an object of the LED class

//Declare variables
unsigned long WakeyTime;
unsigned long SunriseTime;
unsigned long SunsetTime;
//Code compares following two values and selects value which results in later WakeyTime
const unsigned long DelayFromSunset = 21600000; //Minimum time without light used in fall/spring. default 10 hours (36,000,000 milliseconds)
const unsigned long DelayFromSunrise = 22000; //Maximum Light-On time. used in midwinter. default 22 hours (79,200,000 milliseconds)

const float SunriseVoltage = 1.25; //This or higher voltage on panel determines sunrise
const float SunsetVoltage = .75; //This or lower voltage on panel determines sunset
float LEDRed = 0; //Working value while LEDs are turned on
float LEDGreen = 0;
float LEDBlue = 0;
const float LEDMaxBrightness = 100; //Max Brightness Level of LED, 255 is HW limit (this is set point)

int DayCounter = 0;

RunningAverage AverageVoltage(10);
float Voltage; //variable to hold average panel voltage

void setup() {
  Serial.begin(115200); //run at 115200 due to LED stick
  Wire.begin(); //needed for LED stick
  LEDStick.begin(); //needed for LED stick
  pinMode(LED_BUILTIN, OUTPUT); //initialize digital pin LED_BUILTIN as an output.
  
}

//Daily loop
void loop() {

  Serial.print("This here coop's been lit for ");
  Serial.print(DayCounter);
  Serial.println(" days.");
  
  //Wakey Wakey sleepy chickens
  WakeyTime = millis();
  Serial.print("WakeyTime: ");
  Serial.println(WakeyTime);
  
  //Read panel voltage to check for darkness
  ReadPanelVoltage();
  
  if(Voltage < SunriseVoltage & DayCounter > 0){ //Make sure it's dark before turning on LEDs, don't turn on LEDs on first board powerup
    //Turn on LED
    LEDRed = 0;
    while(LEDRed < LEDMaxBrightness){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the board LED on (HIGH is the voltage level)
      LEDRed = LEDRed + 5;
      LEDGreen = LEDRed*0.83; //Ratio for Orange
      LEDBlue = LEDRed*0.377;
      LEDStick.setLEDColor(LEDRed, LEDGreen, LEDBlue); //Turn on LED stick
      Serial.print("LEDRed: ");
      Serial.println(LEDRed);
      delay(250);
      }
  }
  else
  LEDStick.LEDOff();   // turn LED Sticks off if they're on
  
  //Read panel voltage
  ReadPanelVoltage();

  //Monitor Solar panel for sunrise
  while(Voltage < SunriseVoltage){
      ReadPanelVoltage();
   }
  
   //Sunrise
   //Turn off all LEDs
   digitalWrite(LED_BUILTIN, LOW);   // turn built-in LED off (LOW is the voltage level)
   LEDStick.LEDOff();   // turn LED Sticks off
   //Record sunrise time
   SunriseTime = millis();
   Serial.print("SunriseTime: ");
   Serial.println(SunriseTime);
   //Go to low power and wake every 8s to check for sunset
   while(Voltage > SunsetVoltage){
   //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
   //            SPI_OFF, USART0_OFF, TWI_OFF);
    ReadPanelVoltage();
   }    

   //Sunset
   SunsetTime = millis();
   Serial.print("SunsetTime: ");
   Serial.println(SunsetTime);
   //Calculate time to turn lights on. If millis() rolls over, lights won't turn on that day
   if(DayCounter < 1){
   WakeyTime = SunsetTime + DelayFromSunset;
   Serial.print("First sunset since powerup - WakeyTime based on delay from sunset");
   }
   else if(SunsetTime + DelayFromSunset > SunriseTime + DelayFromSunrise) {
   WakeyTime = SunsetTime + DelayFromSunset;
   Serial.print("SunsetTime + DelayFromSunset: ");
   Serial.println(SunsetTime + DelayFromSunset);
   Serial.print("SunriseTime + DelayFromSunrise: ");
   Serial.println(SunriseTime + DelayFromSunrise);
   Serial.print("WakeyTime based on delay from sunset");
   }
   else {
   WakeyTime = SunriseTime + DelayFromSunrise;
   Serial.print("WakeyTime based on delay from sunrise: ");
   }
   
   Serial.print("WakeyTime: ");
   Serial.println(WakeyTime);
   
   //Turn board to low power state, wake every 8 sec to check timer
   //***Add code to check panel voltage
    while(millis() < WakeyTime && Voltage < SunsetVoltage){
    //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
    //           SPI_OFF, USART0_OFF, TWI_OFF);  
    ReadPanelVoltage();
    Serial.print("Overnight, millis = : ");
    Serial.println(millis());
    }

    DayCounter++;
    //Restart loop to turn lights on
}


//functions defined below

void ReadPanelVoltage(){
    
    const int analogPin = A0; // Read solar panel voltage at analog pin A0
    int sensorValue = 0; // variable to store the value read
    
    unsigned long LoopStartTime = millis();
    float SampleVoltage;

    AverageVoltage.clear();
    
    for (int i = 0; i < 10; i++){
      sensorValue = analogRead(analogPin);  // read the input pin
      SampleVoltage = (sensorValue * 5.0 / 1023.0);
      AverageVoltage.addValue(SampleVoltage);
      //Serial.print("Sample Voltage: ");
      //Serial.println(SampleVoltage);
      delay(250);
    }

    Voltage = AverageVoltage.getAverage();
    
    unsigned long LoopTime = millis()-LoopStartTime;

    Serial.print("Average Voltage Last ");
    Serial.print(LoopTime/1000);
    Serial.print(" seconds: ");
    Serial.println(Voltage);

 
}
