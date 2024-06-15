#include <Servo.h>

const int soilMoisturePin = A0;
const int potentiometerPin = A1;
const int pumpPin = 9;
const int buzzerPin = 7;
const int ledPin = 6;
const int buttonPin = 2;

Servo servoMotor;
int threshold = 300; // Default threshold for soil moisture

void setup() {
  pinMode(soilMoisturePin, INPUT);
  pinMode(potentiometerPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Button pin with internal pull-up resistor
  servoMotor.attach(10);
  
  // Initialize the system
  digitalWrite(pumpPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);
  int potValue = analogRead(potentiometerPin);
  
  // Adjust threshold based on potentiometer value (0-1023)
  threshold = map(potValue, 0, 1023, 200, 800); // Map potentiometer range to desired threshold range
  
  if (soilMoisture < threshold) {
    digitalWrite(pumpPin, HIGH);
    servoMotor.write(90);
    feedback(true); // Provide feedback that watering starts
    delay(5000);    // Watering duration
    digitalWrite(pumpPin, LOW);
    servoMotor.write(0);
    feedback(false); // Provide feedback that watering stops
  }
  
  // Check for manual activation via button (sleep mode toggle)
  if (digitalRead(buttonPin) == LOW) {
    while (digitalRead(buttonPin) == LOW) {
      // Wait for button release
      delay(50);
    }
    delay(500); // Debounce delay
    sleepMode(false); // Exit sleep mode
  }
  
  // Enter sleep mode to conserve power
  sleepMode(true);
}

void feedback(bool start) {
  if (start) {
    // Watering starts feedback
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(200); // Feedback duration
  } else {
    // Watering stops feedback
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(200); // Feedback duration
  }
}

void sleepMode(bool enable) {
  if (enable) {
    // Entering sleep mode
    digitalWrite(pumpPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    servoMotor.detach(); // Detach servo to save power
    Serial.println("System in sleep mode...");
    // Sleep until button press wakes up
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    // Upon wakeup, reinitialize necessary components
    servoMotor.attach(10); // Reattach servo
    Serial.println("System wakes up from sleep.");
  }
}
