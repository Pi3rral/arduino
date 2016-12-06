#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTPIN 5
#define DHTTYPE           DHT11     // DHT 11 

#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASS"
#define SERVER_NAME "YOUR_BACKEND"
#define SERVER_PORT 80
#define SERVER_URL "/measures/"
#define LOCATION "YOUR_LOCATION"

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int loop_nb = 0;
HTTPClient http;

void sendTH(int temperature, int humidity) {
  Serial.println("Sending temperature and humidity");
  http.begin(SERVER_NAME, SERVER_PORT, SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  auto httpCode = http.POST(
    "{\"temperature\": "+ String(temperature)
    + ", \"humidity:\"" + String(humidity)
    + ", \"location\": \"" + LOCATION 
    + "\"}"
  );
  Serial.println(httpCode);
  http.end();
}

int readTemp() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  return event.temperature;
}

int readHum() {
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }
  return event.relative_humidity;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
  }
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = readTemp();
  
  if (!isnan(temp)) {
    Serial.print("Temperature: ");
    Serial.println(temp);    
  }
  
  int hum = readHum();
  if (!isnan(hum)) {
    Serial.print("Humidity: ");
    Serial.println(hum);
  }

  if (!isnan(temp) && !isnan(hum)) {
    sendTH(temp, hum);
  }
  
  delay(1000);
}
