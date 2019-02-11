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
  initializeEngine();
  initializeSensor();
  Serial.begin(9600);
}

void initializeEngine() {
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);  
  pinMode(ENB, OUTPUT);
  
  setForwardDirection();
  stopEngine();
}

void initializeSensor() {
  pinMode(SENSOR_INPUT, INPUT);
}

void setForwardDirection() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
}

void setEngineSpeed(int speed) {
  analogWrite(ENB, speed);
}

void stopEngine() {
  analogWrite(ENB, 0);
}

void loop() {
  int sensorValue = analogRead(SENSOR_INPUT);
  
  if (isOutOfLine(sensorValue)) {
    setEngineSpeed(MIN_SPEED);
    printEngineStatusMessage(sensorValue, MIN_SPEED);
  } else if (isInsideLine(sensorValue)) {
    setEngineSpeed(MAX_SPEED);
    printEngineStatusMessage(sensorValue, MAX_SPEED);
  } else {
    setEngineSpeed(MID_SPEED);
    printEngineStatusMessage(sensorValue, MID_SPEED);
  }
  
  delay(100);
}

bool isOutOfLine(int sensorValue) {
  return sensorValue < OUTLINE_THRESHOLD;
}

bool isInsideLine(int sensorValue) {
  return sensorValue > INLINE_THRESHOLD;
}

void printEngineStatusMessage(int sensorValue, int speed) {
  String sensorMessage = "Sensor => ";
  sensorMessage = sensorMessage + sensorValue;

  String speedMessage = "Speed => ";
  speedMessage = speedMessage + speed;

  String message = sensorMessage + " | " + speedMessage;
  Serial.println(message);
}
