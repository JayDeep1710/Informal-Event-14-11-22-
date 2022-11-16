int trigPin = 6;  // trig pin of HC-SR04
int echoPin = 9;  // Echo pin of HC-SR04
int M1_1 = 5;
int M1_2 = 3;
int M2_1 = 11;
int M2_2 = 10;
long duration, distance;
unsigned long time, timeinit = millis() / 1000;

void setup() {
  delay(random(500, 2000));  // delay for random time
  Serial.begin(9600);

  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);
  pinMode(trigPin, OUTPUT);  // set trig pin as output
  pinMode(echoPin, INPUT);   //set echo pin as input to capture reflected waves
}
void left() {

  analogWrite(M1_1, 130);
  analogWrite(M1_2, 0);
  analogWrite(M2_1, 138);
  analogWrite(M2_2, 0);
  delay(550);
}
void right() {
  analogWrite(M1_1, 0);
  analogWrite(M1_2, 130);
  analogWrite(M2_1, 0);
  analogWrite(M2_2, 138);
  delay(575);
}
void measuredistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // send waves for 10 us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // receive reflected waves
  Serial.print(duration);
  Serial.print(" ");
  distance = duration / 58.2;  // convert to distance (cm)
}
void loop() {
  measuredistance();
  int leftdistance = 0;
  int rightdistance = 0;


  if (distance < 13) {
    stop();
    left();
    stop();
    measuredistance();
    if (distance > 15) {
      leftdistance = 1;
    } else {
      right();
      right();
      stop();
      measuredistance();
      if (distance > 14) {
        rightdistance = 1;
      } else {
        right();
        stop();
      }
    }
  }

  else {
    analogWrite(M1_1, 0);
    analogWrite(M1_2, 130);
    analogWrite(M2_1, 138);
    analogWrite(M2_2, 0);
  }
  delay(400);
}

void stop() {
  digitalWrite(M1_1, LOW);
  digitalWrite(M1_2, LOW);
  digitalWrite(M2_1, LOW);
  digitalWrite(M2_2, LOW);
  delay(500);
}
