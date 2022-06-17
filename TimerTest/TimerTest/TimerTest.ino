unsigned long RunTime;
unsigned long SunriseTime;
unsigned long LoopStartTime;
unsigned long LoopDuration;

void setup() {
  Serial.begin(9600);

  RunTime = millis();
  SunriseTime = 5000;

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
 
}

void loop() {  

  LoopStartTime = millis();
  
  if (RunTime > SunriseTime) {  
    while(millis() < RunTime + 2000){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      //wait approx. [period] ms
    }
   }

  //Print
  Serial.print("RunTime: "); // prints time since program started
  Serial.println(RunTime);
  Serial.print("SunriseTime: ");
  Serial.println(SunriseTime);
  Serial.print("LoopDuration: ");
  Serial.println(LoopDuration);
  
  RunTime = millis();

  while(millis() < RunTime + 1000){
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off (LOW is the voltage level)
        //wait approx. [period] ms

  LoopDuration = millis() - LoopStartTime;
  
  }
}
