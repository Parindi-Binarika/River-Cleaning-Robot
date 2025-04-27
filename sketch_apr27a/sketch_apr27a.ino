#include <NewPing.h>

// Motor Pins  
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

//  Ultrasonic Sensor Pins 
#define trig_pin A1
#define echo_pin A2
#define maximum_distance 200
NewPing sonar(trig_pin, echo_pin, maximum_distance);

// Buzzer Pin 
#define buzzerPin 3

// Shovel Motor Pins 
#define shovelMotorPin1 11  // IN1 for Shovel Motor
#define shovelMotorPin2 12  // IN2 for Shovel Motor


int distance = 100;

void setup() {
 
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  pinMode(shovelMotorPin1, OUTPUT);
  pinMode(shovelMotorPin2, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  moveForward();
}

void loop() {
  distance = readPing();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= 20) {
    beepBuzzer();       // Alert

    moveForward();
    delay(1500);        // Move forward for 1.5 seconds to reach debris
    moveStop();        

    liftShovel();       
    delay(2000);        
    lowerShovel();     
    delay(2000);        

    moveForward();     
  }
  else {
    moveForward();     
  }

  delay(200); 
}

// shovel scope function
void liftShovel() {
  digitalWrite(shovelMotorPin1, HIGH);
  digitalWrite(shovelMotorPin2, LOW);
  delay(800);
  stopShovel();
}

void lowerShovel() {
  digitalWrite(shovelMotorPin1, LOW);
  digitalWrite(shovelMotorPin2, HIGH);
  delay(800);
  stopShovel();
}

void stopShovel() {
  digitalWrite(shovelMotorPin1, LOW);
  digitalWrite(shovelMotorPin2, LOW);
}
void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
}

void turnLeft() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
}

void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

// buzzer
void beepBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(300);
  digitalWrite(buzzerPin, LOW);
}

// sensor
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  return (cm == 0) ? 250 : cm;
}
