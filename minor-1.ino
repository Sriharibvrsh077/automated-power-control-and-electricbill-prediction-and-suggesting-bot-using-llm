#include <Arduino.h>
#include <Servo.h>  // Include Servo library

// Pin connections for Arduino Mega
const int trigPin = 5;  // Trigger for Ultrasonic Sensor 1 on Pin 5
const int echoPin = 4;  // Echo for Ultrasonic Sensor 1 on Pin 4
const int trigPin2 = 7; // Trigger for Ultrasonic Sensor 2 on Pin 7
const int echoPin2 = 6; // Echo for Ultrasonic Sensor 2 on Pin 6
const int servoPin = 8; // Pin for servo motor

// Other pins used for shift register and 7-segment display
const int dataPin = 50;  // Pin for 74HC595 on Pin 50
const int latchPin = 48; // Pin for 74HC595 on Pin 48
const int clockPin = 46; // Pin for 74HC595 on Pin 46

int i = 0; // Visitor count
int currentState = 0;
int previousState = 0;
int currentState2 = 0;
int previousState2 = 0;

Servo myServo;  // Create a Servo object

// Function to map numbers to 7-segment display bits
byte myfnNumToBits(int someNumber) {
  switch (someNumber) {
    case 0:
      return B11111100;
    case 1:
      return B01100000;
    case 2:
      return B11011010;
    case 3:
      return B11110010;
    case 4:
      return B01100110;
    case 5:
      return B10110110;
    case 6:
      return B10111110;
    case 7:
      return B11100000;
    case 8:
      return B11111110;
    case 9:
      return B11110110;
    default:
      return B10010010; // Error condition, displays three vertical bars
  }
}

// Function to update the 7-segment display
void myfnUpdateDisplay(byte eightBits) {
  digitalWrite(latchPin, LOW); // prepare shift register for data
  shiftOut(dataPin, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}

// Function to update the servo position based on visitor count
void myfnUpdateServo(int visitorCount) {
  if (visitorCount == 0) {
    myServo.write(90);  // Move servo to 90 degrees (upwards)
  } else if (visitorCount == 1) {
    myServo.write(0);   // Move servo to 0 degrees (downwards)
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);  // Trigger for Sensor 1
  pinMode(echoPin, INPUT);   // Echo for Sensor 1
  pinMode(trigPin2, OUTPUT); // Trigger for Sensor 2
  pinMode(echoPin2, INPUT);  // Echo for Sensor 2

  pinMode(dataPin, OUTPUT);  // Data pin for shift register
  pinMode(latchPin, OUTPUT); // Latch pin for shift register
  pinMode(clockPin, OUTPUT); // Clock pin for shift register

  myServo.attach(servoPin);  // Attach servo to pin 8
  myServo.write(90);         // Set initial position to 90 degrees (upwards)

  Serial.begin(9600); // Start the serial monitor
}

void loop() {
  long duration, distance, duration2, distance2;

  // Read distance from first ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // Read distance from second ultrasonic sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;

  // Object entering the system
  if (distance <= 10) {
    currentState = 1;
  } else {
    currentState = 0;
  }

  if (currentState != previousState) {
    while (currentState == 1) {
      // Check second sensor
      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
      distance2 = (duration2 / 2) / 29.1;

      if (distance2 <= 10) {
        currentState2 = 1;
      } else {
        currentState2 = 0;
      }

      if (currentState2 != previousState2) {
        if (currentState2 == 1) {
          i = i + 1; // Increment count
          byte bits = myfnNumToBits(i);
          myfnUpdateDisplay(bits); // Update the display
          myfnUpdateServo(i);      // Update the servo motor position
          Serial.print("Visitor Entered, Total Visitors: ");
          Serial.println(i);  // Print the visitor count to Serial Monitor
          delay(1000); // Pause for 1 second
        }
        return;
      }
    }
  }

  // Object exiting the system
  if (distance2 <= 10) {
    currentState2 = 1;
  } else {
    currentState2 = 0;
  }

  if (currentState2 != previousState2) {
    while (currentState2 == 1) {
      // Check first sensor again
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;

      if (distance <= 10) {
        currentState = 1;
      } else {
        currentState = 0;
      }

      if (currentState != previousState) {
        if (currentState == 1) {
          i = i - 1; // Decrement count

          // Check if the visitor count is negative
          if (i < 0) {
            Serial.println("Unaurthorize person");  // Send a BEEP signal when count is negative
          }

          byte bits = myfnNumToBits(i);
          myfnUpdateDisplay(bits); // Update the display
          myfnUpdateServo(i);      // Update the servo motor position
          Serial.print("Visitor Exited, Total Visitors: ");
          Serial.println(i);  // Print the visitor count to Serial Monitor
          delay(1000); // Pause for 1 second
        }
        return;
      }
    }
  }

  // Save the previous states
  previousState = currentState;
  previousState2 = currentState2;
}
