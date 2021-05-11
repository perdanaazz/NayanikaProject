//header
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht.h>

//setup connection
char ssid[] = "Pepe WiFi";
char pass[] = "perdana2020";
WiFiClient client;

//setup Blynk
char auth[] = "OB1eCNUYXoLjz1KvAakoEBCZ_GKhomAM";

//setup pin untuk sensor flame
int flamePin = D6;
int buzzerPin = D2;

//setup pin untuk sensor pir
int pirPin = D7;

//setup pin dht11
int dhtPin = D5;
dht DHT;

//setup pin mq2
int mqPin = A0;

void setup(){
  Serial.begin(9600);
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(dhtPin, OUTPUT);
  pinMode(mqPin, INPUT);

  //wifi connect
  Serial.print("Menghubungkan ke : ");
  Serial.print(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");
  Serial.print("IP Address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("Terhubung dengan : ");
  Serial.print(ssid);

  //blynk connect
  Blynk.begin(auth, ssid, pass);
}

void loop(){
  Blynk.run();
  flame();
  pir();
  dht11();
  mq();
}

void flame(){
  int state = digitalRead(flamePin);
  if (state == LOW){
    Serial.println("Api terdeteksi");
    digitalWrite(buzzerPin, HIGH);
  }else{
    Serial.println("Tidak ada api");
    digitalWrite(buzzerPin, LOW);
  }
  delay(1000);
}

void pir(){
  int state2 = digitalRead(pirPin);
  Serial.print(state2);
  if (state2 == HIGH){
    Serial.println("Ada gerakan");
    digitalWrite(buzzerPin, HIGH);
  }else{
    Serial.println("Tidak ada gerakan");
    digitalWrite(buzzerPin, LOW);
  }
  delay(1000);
}

void dht11(){
  int readData = DHT.read11(dhtPin);
  Blynk.virtualWrite(V5, DHT.temperature);
  Blynk.virtualWrite(V6, DHT.humidity);
}

void mq(){
  int valueMQ = analogRead(mqPin);
  if (valueMQ > 500){
    Serial.println("Asap terdeteksi");
  }else{
    Serial.println("Asap tidak terdeteksi");
  }
  delay(1000);
}
