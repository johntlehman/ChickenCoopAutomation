unsigned long RunTime;
unsigned long SunriseTime;
unsigned long SunsetTime;
unsigned long DayDuration;
unsigned long WakeUpTime;
unsigned long LoopStartTime;
unsigned long LoopDuration;
unsigned long LightsOnTime;
unsigned long LEDBurnTime;

void setup() {
  Serial.begin(9600);

  RunTime = millis();
  LEDBurnTime = 2000;

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
 
}

void loop() {  

  //Wakey Wakey sleepy chickens
  LightsOnTime = millis();
  Serial.print("LightsOnTime: ");
  Serial.println(LightsOnTime);
  
  while(millis() < LightsOnTime + LEDBurnTime){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }

  //Sunrise
  //Start Daylight Timer
  SunriseTime = millis();
  Serial.print("SunriseTime: ");
  Serial.println(SunriseTime);
  //Turn off LEDs
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off (LOW is the voltage level)

  //test day is 5 seconds long
  while(millis() < SunriseTime + 5000){
    //wait approx. [period] ms
   }

    //Sunset
    //Calculate Daylight Duration
    SunsetTime = millis();
    Serial.print("SunsetTime: ");
    Serial.println(SunsetTime);
     
    DayDuration = SunsetTime-SunriseTime;

    //Print
    Serial.print("DayDuration: "); // prints time since program started
    Serial.println(DayDuration);
    Serial.print("Millis: ");
    Serial.println(millis());
    
    WakeUpTime = SunriseTime + 10000;
    Serial.print("WakeUpTime: ");
    Serial.println(WakeUpTime);
    
    //Test delay turns lights on 10 seconds after sunrise
    while(millis() < WakeUpTime){
    //wait approx. [period] ms
    }
    
    }
