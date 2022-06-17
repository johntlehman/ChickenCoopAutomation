//LowPower Test with timers

#include <LowPower.h> //Load library for power saving

//declare test variables
float elapsedTime; //keep track of time when sleepin


void setup() {
  Serial.begin(115200);

  //Drop the clock speed
  //CLKPR = 0x80;
  //CLKPR = 0x02; //Set registers to lowest possible clock speed 62.6 kHz

  elapsedTime = millis(); //oughta be 0

}

void loop() {
    
    //print the time (millis)
    Serial.print("millis: ");
    Serial.println(millis());
    Serial.print("elapsedTime, seconds: ");
    Serial.println(elapsedTime/1000);
    Serial.println("Going to sleeep zzzz");
    delay(500); //allow time to print
    elapsedTime = elapsedTime + 500;
    // ATmega328P, ATmega168 - Sparkfun Redboard plus uses the ATMega328P
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                  SPI_OFF, USART0_OFF, TWI_OFF);
    //LowPower.idle(); //fails
    //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    //LowPower.powerSave(SLEEP_8S, ADC_OFF, BOD_OFF, TIMER2_ON);
    //LowPower.powerStandby(SLEEP_8S, ADC_OFF, BOD_OFF);
    //LowPower.standby();  //Why the EFF doesn't this work?
    //LowPower.idle();
    elapsedTime = elapsedTime + 8000; //correct for idle time
    
    
  //}
  

}
