#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6IS_ezTjJ"
#define BLYNK_TEMPLATE_NAME "piranti"
#define BLYNK_AUTH_TOKEN "7KesF3vQ5jCbIwgEaICPHIPxpMRAXRVd"
#define LED 5
#define DHTPIN 21         // Mention the digital pin where you connected 
#define DHTTYPE DHT11     // DHT 11  
#include <DHT.h>


BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);
bool isOn = false;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "INDIJETIS";
char pass[] = "kosatas123";

String lampu1 = "Lampu Dinyalakan";
String lampu2 = "Lampu Dimatikan";

void send_data() {
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  Serial.println("Suhu : ");
  Serial.print(t);
  Serial.print("|| Kelembapan : ");
  Serial.println(h);

  if (t < 27) {
    digitalWrite(LED, HIGH);
    Serial.print("Lampu           : ");
    Serial.print(lampu1);
    Blynk.virtualWrite(V2, lampu1);
  } else {
    digitalWrite(LED, LOW);
    Serial.println("Lampu           : ");
    Serial.print(lampu2);
    Blynk.virtualWrite(V2, lampu2);
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  dht.begin();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000, send_data);
}

void loop() {
  Blynk.run();
  timer.run();
}