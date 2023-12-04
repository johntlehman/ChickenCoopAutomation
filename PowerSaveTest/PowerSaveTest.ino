//LowPower Test
//Check status of Pin A0 every 8 seconds. If Low turn LED stick on, If High Leave Off

// #include <Wire.h> //Used for LED stick
// #include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick
#include "LowPower.h" //Load library for power saving

// Use pin 2 as wake up pin
const int wakeUpPin = 2;

//#include < avr/power.h>
//#include < avr/sleep.h>

// LED LEDStick; //Create an object of the LED class
 
//declare test variables
int analogPin = A0; // Read solar panel voltage at analog pin A0
int sensorValue = 0; // variable to store the value read
float voltage; //variable to convert reading to voltage
float NightVoltage = .75; //this or lower voltage on solar panel determines night

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

void setup() {
  Serial.begin(115200); //run at 115200 for LED stick, 9600 for serial monitor
  // Wire.begin(); //needed for LED stick
  // LEDStick.begin(); //needed for LED stick

  pinMode(wakeUpPin, INPUT);   

  //CLKPR = 0x80;
  //CLKPR = 0x02; //Set registers to lowest possible clock speed 62.6 kHz

}

void loop() {    
    //Run in normal mode
    Serial.print("Nothin' to see here jes runnin in normal mode.");
    Serial.print("millis: ");
    Serial.println(millis());
    delay (2000); //Allow time to measure voltage

    //check that millis still works
    Serial.print("millis: ");
    Serial.println(millis());
    Serial.println("Going to sleeep for 8 seconds zzzz");
    delay(500); //allow time to print
    // ATmega328P, ATmega168 - Sparkfun Redboard plus uses the ATMega328P
    LowPower.powerStandby(SLEEP_8S,ADC_ON,BOD_ON);

    //---------------------
    //Interrupt Power Save Test
    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUp, LOW);
    
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    Serial.println("Going to sleepin Interrupt mode, wake me up by shocking pin 2");
    delay(1000); //allow time to print
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
    
    Serial.println("Yowza! Why'd ya shock me like that? Waiting 5 seconds before sleeping again.");
    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0); 
    delay(5000);
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.
    //-----------------------



}
