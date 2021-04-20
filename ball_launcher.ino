#include <ESP32Servo.h>

#define trigPin 13 // define TrigPin
#define echoPin 14 // define EchoPin.
#define MAX_DISTANCE 700 // Maximum sensor distance is rated at 400-500cm.

Servo myservo1;  // create servo object to control a servo
Servo myservo2;

int posVal = 0;    // variable to store the servo position
int newVal = 0;
int servoPin1 = 4; // Servo motor pin
int servoPin2 = 5;

float timeOut = MAX_DISTANCE * 60; 
int soundVelocity = 340; // define sound speed=340m/s

float distance;

void setup() {
  myservo1.setPeriodHertz(50);           // standard 50 hz servo
  myservo2.setPeriodHertz(50);
  myservo1.attach(servoPin1, 500, 2500);  // attaches the servo on servoPin1 to the servo object
  myservo2.attach(servoPin2, 500, 2500);
  pinMode(trigPin,OUTPUT);// set trigPin to output mode
  pinMode(echoPin,INPUT); // set echoPin to input mode
  Serial.begin(115200);   // Open serial monitor at 115200 baud to see ping results.
  myservo1.write(70);
  myservo2.write(0);
}

void loop() {
  for (posVal = 70; posVal <= 110; posVal += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(posVal);// tell servo to go to position in variable 'pos'
    myservo2.write(0);
    //myservo2.write(posVal);
    if (posVal % 10 == 0) {
      distance = getSonar();
      Serial.printf("Distance: ");
      Serial.print(distance); // Send ping, get distance in cm and print result 
      Serial.println("cm");
      if (distance < 46 && distance > 45) {
        delay(5000);
        myservo2.write(110);
        delay(1000);
        myservo2.write(0);
        delay(5000);
      }
    }
    delay(50);                   // waits 15ms for the servo to reach the position
  }
  for (posVal = 110; posVal >= 70; posVal -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(posVal);       // tell servo to go to position in variable 'pos'
    myservo2.write(0);
    if (posVal % 10 == 0) {
      distance = getSonar();
      Serial.printf("Distance: ");
      Serial.print(distance); // Send ping, get distance in cm and print result 
      Serial.println("cm");
      if (distance < 46 && distance > 45) {
        delay(5000);
        myservo2.write(110);
        delay(1000);
        myservo2.write(0);
        delay(5000);
      }
    }
    delay(50);                   // waits 15ms for the servo to reach the position
  }
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  // make trigPin output high level lasting for 10Î¼s to triger HC_SR04
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Wait HC-SR04 returning to the high level and measure out this waitting time
  pingTime = pulseIn(echoPin, HIGH, timeOut); 
  // calculate the distance according to the time
  distance = (float)pingTime * soundVelocity / 2 / 10000; 
  return distance; // return the distance value
}
