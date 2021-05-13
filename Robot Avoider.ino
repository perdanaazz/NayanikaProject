const int motor1 = 7;
const int motor2 = 6;
const int motor3 = 5;
const int motor4 = 4;
const int pinT = 3;
const int pinE = 2; 
const int pinSpeed = 10;
int Speed, durasi, jarak;

void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(pinT, OUTPUT);
  pinMode(pinE, INPUT);
  pinMode(pinSpeed, OUTPUT);
}

void loop() {
  //Motor DC
  Speed = constrain(Speed, 0, 255);
  Speed = 255;
  analogWrite(pinSpeed, Speed);
  
  //Sensor Ultrasonik (inisiasi)
  digitalWrite(pinT, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinT, LOW);
  
  //Data pantulan gelombang
  durasi = pulseIn(pinE, HIGH);
  jarak = ((durasi * 0.034) / 2);
  
  //Setting up gerakan
  if (jarak >= 20){
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    digitalWrite(motor3, HIGH);
    digitalWrite(motor4, LOW);
  }
  else if (jarak < 20){
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
    digitalWrite(motor3, LOW);
    digitalWrite(motor4, HIGH);
    delay(300);
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    digitalWrite(motor3, LOW);
    digitalWrite(motor4, HIGH);
    delay(300);
  }
}
