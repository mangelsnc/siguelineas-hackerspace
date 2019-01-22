/**
 * Miguel Ángel Sánchez Chordi <mangel.snc@gmail.com>
 * Francisco Díaz Gomez <diazgomezfrancisco@gmail.com>
 * Vicente Jose Moreno <navarretvj@gmail.com>
 * David Hernandez <davidhernandezruiz@gmail.com>
 * 
 */

const int SENSOR_INPUT = 0;
const int INLINE_THRESHOLD = 900;
const int OUTLINE_THRESHOLD = 100;

const int ENB = 9;
const int IN3 = 11;
const int IN4 = 10;

const int MIN_SPEED = 60;
const int MID_SPEED = 120;
const int MAX_SPEED = 255;

void setup() {
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);  
  pinMode(ENB, OUTPUT);
  pinMode(SENSOR_INPUT, INPUT);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 0);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(SENSOR_INPUT);
  
  if (sensorValue < OUTLINE_THRESHOLD) {
    startEngine(MIN_SPEED);
    Serial.println("Sensor: " + String(sensorValue) + ". Speed => " + String(MIN_SPEED));
  } else if (sensorValue > INLINE_THRESHOLD) {
    startEngine(MAX_SPEED);
    Serial.println("Sensor: " + String(sensorValue) + ". Speed => " + String(MAX_SPEED));
  } else { // if(sensorValue > OUTLINE_THRESHOLD && sensorValue < INLINE_THRESHOLD) {
    startEngine(MID_SPEED);
    Serial.println("Sensor: " + String(sensorValue) + ". Speed => " + String(MID_SPEED));
  }
  
  delay(100);
}

void startEngine(int speed) {
  analogWrite(ENB, speed);
}

void stopEngine() {
  analogWrite(ENB, 0);
}
