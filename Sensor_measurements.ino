#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "g2PsGb--dTroWiq10zsjPeAtlQlUFswc";
char ssid[] = "Legion";
char pass[] = "tasm7034";

#define DHTPIN 2
#define DHTTYPE DHT11  // DHT11 SENSOR CONNECT D2 PIN
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V1, h); // V5 is for Humidity
  Blynk.virtualWrite(V0, t); // V6 is for Temperature
}

int soilMoisturePin = A0;

void sendSoilMoisture()
{
  int soilMoisture = analogRead(soilMoisturePin);
  Blynk.virtualWrite(V2, soilMoisture); // V1 is for Soil Moisture
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop()
{
  Blynk.run();
  sendSensor();
  sendSoilMoisture();
}
