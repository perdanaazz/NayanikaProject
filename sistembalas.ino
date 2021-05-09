//import library
#include <LiquidCrystal_I2C.h>

//setup LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//deklarasi pin
#define echoPin 3
#define trigPin 2
#define relayPin 13

//global variabel
int maxRange = 200;
int minRange = 0;
long duration, distance;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop(){
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(relayPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2; //algoritma hitung jarak sensor ultrasonik
  
  if(distance <= 30){
    Serial.print("Jarak air = "); Serial.print(distance);
    Serial.print(" Pompa OFF\n");
    lcd.setCursor(0,0);
    lcd.print("Jarak air = ");
    lcd.setCursor(12,0);
    lcd.print(distance);
    lcd.setCursor(0,1);
    lcd.print("Pompa OFF");
    digitalWrite(relayPin, HIGH);
  }else{
    Serial.print("Jarak air = "); Serial.print(distance);
    Serial.print(" Pompa ON\n");
    lcd.setCursor(0,0);
    lcd.print("Jarak air = ");
    lcd.setCursor(12,0);
    lcd.print(distance);
    lcd.setCursor(0,1);
    lcd.print("Pompa ON");
    digitalWrite(relayPin, LOW);
  }
  delay(1000);
  lcd.clear();
}
