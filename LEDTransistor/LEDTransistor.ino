//Turn on a group of LEDs using an NPN transistor

//Declarations
const unsigned long outputPin = 3;
const unsigned long PWMSetPoint = 125;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin (115200);
    pinMode(outputPin, OUTPUT); //Pin 3 will turn drive voltage to the transistor which will switch on the LED
}

void loop()
{
//Turn LEDs on for 5 seconds
    digitalWrite(LED_BUILTIN,HIGH);
    analogWrite(outputPin, PWMSetPoint); //PWM at PWMSetPoint duty cycle
    Serial.println((String) "PWM on set to " + PWMSetPoint);
    delay(5000);
//Turn LEDs off 5 seconds
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(outputPin, LOW);
    Serial.println("G'night zzzzz");
    delay(5000);
}