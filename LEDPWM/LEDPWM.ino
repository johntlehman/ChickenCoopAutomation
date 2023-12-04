void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin (115200);
    pinMode(11, OUTPUT);
}

void loop()
{
    //Just run the LED
    //digitalWrite(LED_BUILTIN,HIGH);
    //digitalWrite(11, HIGH);
    //Serial.println("Wakey wakey eggs and bacie");    
    //delay(500);

    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(11, LOW);
    Serial.println("G'night zzzzz");
    delay(1500);

    digitalWrite(LED_BUILTIN,HIGH);
    analogWrite(11, 75); //Approx 25% duty cycle PWM
    Serial.println("25% Brightness");
    delay(3000);
    analogWrite(11, 125); //Approx 50% duty cycle PWM
    Serial.println("50% Brightness");
    delay(3000);
    analogWrite(11, 175); //Approx 75% duty cycle PWM
    Serial.println("75% Brightness");
    delay(3000);
    analogWrite(11, 255); //100% duty cycle PWM
    Serial.println("100% Brightness");
    delay(3000);

}

//{
//  digitalWrite(11, HIGH);
//  delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
//  digitalWrite(11, LOW);
//  delayMicroseconds(1000 - 100);
//}