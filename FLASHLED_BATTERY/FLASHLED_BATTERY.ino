//Turn on a group of LEDs using an NPN transistor, monitor fuel gauge

#include "Wire.h" //Needed for serial
#include "SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h"

//Declarations
const unsigned long outputPin = 3;
const unsigned long PWMSetPoint = 125;

SFE_MAX1704X lipo(MAX1704X_MAX17043);  //Create an object called 'lipo' of the SFE_MAX1704X class

double voltage = 0; // Variable to keep track of LiPo voltage
double soc = 0; // Variable to keep track of LiPo state-of-charge (SOC)
bool alert; // Variable to keep track of whether alert has been triggered

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin (115200);
    pinMode(outputPin, OUTPUT); //Pin 3 will turn drive voltage to the transistor which will switch on the LED

    Wire.begin();

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

void loop()
{

  // lipo.getVoltage() returns a voltage value (e.g. 3.93)
  voltage = lipo.getVoltage();
  // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
  soc = lipo.getSOC();
  // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
  alert = lipo.getAlert();

  // Print the variables:
  Serial.print("Voltage: ");
  Serial.print(voltage);  // Print the battery voltage
  Serial.println(" V");

  Serial.print("Percentage: ");
  Serial.print(soc); // Print the battery state of charge
  Serial.println(" %");

  Serial.print("Alert: ");
  Serial.println(alert);

//Turn LEDs on for 5 seconds
    digitalWrite(LED_BUILTIN,HIGH);
    analogWrite(outputPin, PWMSetPoint); //PWM at PWMSetPoint duty cycle
    Serial.println((String) "PWM on set to " + PWMSetPoint);
    delay(5000);

//Turn LEDs off 5 seconds
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(outputPin, LOW);
    Serial.println("G'night zzzzz");
    Serial.println();
    delay(5000);
}