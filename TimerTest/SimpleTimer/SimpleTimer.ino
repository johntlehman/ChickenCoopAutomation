unsigned long RunTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  RunTime = millis();

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(13, OUTPUT); //setup pin to run external LED
}

void loop() {
  // put your main code here, to run repeatedly:
  while(millis() < RunTime + 1000){
      //wait approx. [period] ms
      digitalWrite(LED_BUILTIN, HIGH);   // turn built in LED on (HIGH is the voltage level)
      digitalWrite(13, HIGH); //turn external LED on
   }

  Serial.print("RunTime: "); // prints time since program started
  Serial.println(RunTime);
  
  while(millis() < RunTime + 2000){
      //wait approx. [period] ms
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off (LOW is the voltage level)
      digitalWrite(13, LOW); //turn external LED off
   }
  RunTime = millis();
}
