#define LED_pin 13 // Onboard Led pin
#define TEMPERATURE_threshold 30 // Temperature threshold in degrees Celsius

int sensorPin = A0; // LM35 temperature sensor pin

void setup() {
  pinMode(LED_pin, OUTPUT); // set led pin as output
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  int temp = getTemperature(); // Read temperature from the sensor
  Serial.print("Temperature: ");
  Serial.println(temp);
  
  if (temp < TEMPERATURE_threshold) {
    blinkLED(250); // Blink LED every 250 milliseconds
  } else {
    blinkLED(500); // Blink LED every 500 milliseconds
  }
}

int getTemperature() {
  int sensorValue = analogRead(sensorPin); // Read analog value from LM35 sensor
  
  // Convert analog value to temperature in degrees Celsius
  float voltage = (sensorValue / 1023.0) * 5.0;
  int temp = (voltage - 0.5) * 100;
  
  return temp;
}

void blinkLED(int interval) {
  static unsigned long previousMillis = 0;
  static bool ledState = false;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    
    digitalWrite(LED_pin, ledState);
    delay(interval); 
  }
}

