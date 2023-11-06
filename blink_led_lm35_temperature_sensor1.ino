#include <TimerOne.h> // Include the Timer1 library

#define LED_pin 13 // Onboard LED pin
#define TEMPERATURE_threshold 30 // Temperature threshold in degrees Celsius

int sensorPin = A0; // LM35 temperature sensor pin
int interval = 250; // Initial interval for blinking
bool ledState = false;

void setup() {
  pinMode(LED_pin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Initialize serial communication

  Timer1.initialize(interval * 1000); // Initialize Timer1 with interval in microseconds
  Timer1.attachInterrupt(blinkLED); // Attach the blinkLED function to the timer interrupt
}

void loop() {
  int temp = getTemperature(); // Read temperature from the sensor
  Serial.print("Temperature: ");
  Serial.println(temp);

  if (temp < TEMPERATURE_threshold) {
    interval = 250; // Blink LED every 250 milliseconds
  } else {
    interval = 500; // Blink LED every 500 milliseconds
  }
}

int getTemperature() {
  int sensorValue = analogRead(sensorPin); // Read analog value from LM35 sensor
  
  // Convert analog value to temperature in degrees Celsius
  float voltage = (sensorValue / 1023.0) * 5.0;
  int temp = (voltage - 0.5) * 100;
  
  return temp;
}

void blinkLED() {
  ledState = !ledState;
  digitalWrite(LED_pin, ledState);
}
