// traffic light uno
int t1B = 6;
int t1R = 7;
int t1Y = 8;
int t1G = 9; 

// traffic light dos
int t2B = 10;
int t2R = 11;
int t2Y = 12;
int t2G = 13;

int trigPin = 5;
int echoPin = 4;

int threshold;

long duration, cm, inches;

bool personDetected = false;
int gBluePin = 0;

void setup()
{
  Serial.begin(9600);

  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(t1B, OUTPUT);
  pinMode(t1R, OUTPUT);
  pinMode(t1Y, OUTPUT);
  pinMode(t1G, OUTPUT);

  pinMode(t2B, OUTPUT);
  pinMode(t2R, OUTPUT);
  pinMode(t2Y, OUTPUT);
  pinMode(t2G, OUTPUT);

  // initial setup
  // reset lights
  // t1 red
  digitalWrite(t1B, LOW);
  digitalWrite(t1R, HIGH);
  digitalWrite(t1Y, LOW);
  digitalWrite(t1G, LOW);

  // t2 green
  digitalWrite(t2B, LOW);
  digitalWrite(t2R, LOW);
  digitalWrite(t2Y, LOW);
  digitalWrite(t2G, HIGH);
}

void loop()
{
  int counter = 0;
  int lightDelay = 0;
  
  // t1 red
  digitalWrite(t1R, HIGH);
  digitalWrite(t1Y, LOW);
  digitalWrite(t1G, LOW);

  counter = 0;
  while (detectPerson() == true) {
    delay(100);
    counter += 100;
  }

  digitalWrite(gBluePin, LOW);

  lightDelay = 0;
  if (counter < 1000) {
    lightDelay = 1000 - counter;
  }

  lightsDelay(lightDelay, t1B);

  // t2 green
  digitalWrite(t2R, LOW);
  digitalWrite(t2Y, LOW);
  digitalWrite(t2G, HIGH);

  counter = 0;
  while (detectPerson() == true) {
    delay(100);
    counter += 100;
  }

  digitalWrite(gBluePin, LOW);

  lightDelay = 0;
  if (counter < 5000) {
    lightDelay = 5000 - counter;
  }

  lightsDelay(lightDelay, t1B);

  // t2 yellow
  digitalWrite(t2R, LOW);
  digitalWrite(t2Y, HIGH);
  digitalWrite(t2G, LOW);

  lightsDelay(1000, t1B);

  // t2 red
  digitalWrite(t2R, HIGH);
  digitalWrite(t2Y, LOW);
  digitalWrite(t2G, LOW);

  counter = 0;
  while (detectPerson() == true) {
    delay(100);
    counter += 100;
  }

  digitalWrite(gBluePin, LOW);

  lightDelay = 0;
  if (counter < 1000) {
    lightDelay = 1000 - counter;
  }

  lightsDelay(lightDelay, t2B);

  // t1 green
  digitalWrite(t1R, LOW);
  digitalWrite(t1Y, LOW);
  digitalWrite(t1G, HIGH);

  lightsDelay(5000, t2B);

  // t1 yellow
  digitalWrite(t1R, LOW);
  digitalWrite(t1Y, HIGH);
  digitalWrite(t1G, LOW);

  lightsDelay(1000, t2B);
  
}

bool detectPerson() 
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  // inches = (duration/2) / 74; 

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // calibrate if we don't have a threshold
  if(!threshold) {
    threshold = cm * 0.6;
    Serial.print("Threshold Set = ");
    Serial.print(threshold);
    Serial.println();
  }

  if (cm < threshold) {
    return true;
  } else {
    return false;
  }
}

void lightsDelay(int delayTime, int bluePin)
{
  gBluePin = bluePin;
  int interval = 100;
  int counter = 0;
  
  while (counter <= delayTime) {
    delay(interval);

    if (detectPerson() == true) {
      digitalWrite(bluePin, HIGH);
    } else {
      digitalWrite(bluePin, LOW);
    }

    counter += interval;
  }
}

