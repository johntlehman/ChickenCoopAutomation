//Output voltage at pin A0

int analogPin = A0; // Solar panel voltage 
int sensorValue = 0; // variable to store the value read
float voltage;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);           //  setup serial
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(analogPin);  // read the input pin
  voltage = (sensorValue * 5.0 / 1023.0);
  Serial.println(voltage);          // debug value
  delay(1000);
}
