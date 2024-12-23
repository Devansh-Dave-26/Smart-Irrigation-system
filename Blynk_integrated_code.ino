#define BLYNK_TEMPLATE_ID "TMPL3PyML4pws"
#define BLYNK_TEMPLATE_NAME "smart irrigation"
#define BLYNK_AUTH_TOKEN "g2PsGb--dTroWiq10zsjPeAtlQlUFswc"

#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Network_name";
char pass[] = "password"; 

// Analog pin where the soil moisture sensor is connected
const int soilMoisturePin = A0;

// Digital pin where the motor pump is connected
const int motorPumpPin = D1;

// DHT sensor configuration
#define DHTPIN D2
#define DHTTYPE DHT11  // Changed to DHT11
DHT dht(DHTPIN, DHTTYPE);

// Thresholds for automatic control
const int moistureThreshold = 30; // Adjust as needed
const float temperatureThreshold = 30.0; // Adjust as needed

int moisturePercentage;
float temperature, humidity;

void readSoilMoisture() {
  // Read soil moisture level (0-1023)
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Map the analog value to a percentage (0-100)
  moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  // Print the soil moisture value to the Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Send the soil moisture value to Blynk
  Blynk.virtualWrite(V2, moisturePercentage);
}

void readTemperatureAndHumidity() {
  // Read temperature and humidity from DHT sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Print the temperature and humidity values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Send the temperature and humidity values to Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(motorPumpPin, OUTPUT);
  // timer.setInterval(2000, readState);
  
}

void loop() {
  Blynk.run();

  // Call the functions to read soil moisture and temperature/humidity
  readSoilMoisture();
  readTemperatureAndHumidity();

  // Automatic control based on thresholds
//  if (temperature > temperatureThreshold) 
//{
//      // Turn on the motor pump
//    digitalWrite(motorPumpPin, LOW);
//  } else {
//    // Turn off the motor pump
//    digitalWrite(motorPumpPin, HIGH);
//  }
//    Blynk.setProperty(V4,"Label","Temperature");
  delay(5000);  // Adjust the delay as needed to avoid flooding the Blynk server
}
// Blynk virtual pin handler for the motor pump button
BLYNK_WRITE(V3) {
  int motorPumpStatus = param.asInt();
  
  // If the button is pressed (1), turn on the motor pump
  // If the button is released (0), turn off the motor pump
  digitalWrite(motorPumpPin, !motorPumpStatus);
  
}
