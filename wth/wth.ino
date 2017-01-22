#include <dht.h>
#include "SoftwareSerial.h"

// config file defining SSID, PASSWORD, SERVER infos
#include "config.h"

String WIFI_SSID     = SSID;
String WIFI_PASSWORD = PASSWORD;
String HOST_NAME     = SERVER_IP;
int    HOST_PORT     = SERVER_PORT;

#define DHT11_PIN 5
#define ESP_RXPIN 10
#define ESP_TXPIN 11

#define LEDY_PIN 9
#define LEDG_PIN 8
#define LEDB_PIN 7

#define BAUD_RATE 115200

#define SENDING_INTERVAL 21600000 // send humidity and temperature every 6 hours (6*60*60*1000 = 21,600,000)

#define DEBUG

SoftwareSerial espSerial(ESP_RXPIN, ESP_TXPIN); // RX, TX - reversed on ESP8266

dht DHT;

struct ht_struct {
    double temperature;
    double humidity;
};


ht_struct ht;

/**
 * Read humidity and temperature from DHT library
 * @param ht ht_struct to fill in temperature and humidity
 */
void readHT(ht_struct& ht) {
  DHT.read11(DHT11_PIN);
  ht.temperature = DHT.temperature;
  ht.humidity = DHT.humidity;

#ifdef DEBUG
  Serial.print("Temperature = ");
  Serial.println(ht.temperature);
  Serial.print("Humidity = ");
  Serial.println(ht.humidity);
#endif
}


void emptyESP8266() {
  while (espSerial.available()) {
#ifdef DEBUG
    Serial.write(espSerial.read());
#else
    espSerial.read();
#endif
  }

#ifdef DEBUG
  Serial.println("");
#endif
}

/**
 * Connect the ESP8266 to wifi
 */
void connectWifi() {
#ifdef DEBUG
  // send AT command to check ESP8266 is active and respond
  espSerial.println("AT");
  delay(2000);
  emptyESP8266();
#endif
  // Set ESP8266 in station mode (connect to an existing network)
  espSerial.println("AT+CWMODE=1");
  delay(2000);
  emptyESP8266();
  // Connect to network
  espSerial.println("AT+CWJAP=\""+WIFI_SSID+"\",\""+WIFI_PASSWORD+"\"");
  delay(3000);
  emptyESP8266();
#ifdef DEBUG
  // Get IP Address
  espSerial.println("AT+CIFSR");
  delay(2000);
  emptyESP8266();
#endif
}

/**
 * POST humidity and temperature to server
 * @param ht ht_struct containing humidity and temperature
 */
void httpPOSTHT(ht_struct& ht) {
#ifdef DEBUG
  Serial.println("HTTP POST");
#endif
  // Create TCP Connection
  espSerial.println("AT+CIPSTART=\"TCP\",\""+HOST_NAME+"\","+HOST_PORT);
  delay(1000);
  emptyESP8266();
  // Create request HTTP command
  String request = "POST /wth/measures/?location=rangement&temperature="+String(ht.temperature)+"&humidity="+String(ht.humidity)+" HTTP/1.1\r\n";
  request       += "Host:"+HOST_NAME+":"+HOST_PORT+"\r\n\r\n";
  // Set request size to ESP8266
  espSerial.println("AT+CIPSEND="+String(request.length()));
  delay(1000);
  emptyESP8266();
  // Send request
#ifdef DEBUG
  Serial.println("Send request");
  Serial.println(request);
#endif
  espSerial.print(request);
#ifdef DEBUG
  Serial.println("SENT");
#endif
  delay(5000);
  emptyESP8266();
  // Close connection if needed
  espSerial.println("AT+CIPCLOSE");
  delay(1000);
  emptyESP8266();
}


/**
 * setup WTH module
 * - Set pin mode for LEDs
 * - Connect to wifi
 */
void setup() {
  pinMode(LEDY_PIN, OUTPUT);
  pinMode(LEDG_PIN, OUTPUT);
  pinMode(LEDB_PIN, OUTPUT);
  delay(500);
  // Open yellow LED when connecting
  digitalWrite(LEDY_PIN, HIGH);
  digitalWrite(LEDG_PIN, LOW);
  digitalWrite(LEDB_PIN, LOW);
#ifdef DEBUG
  Serial.begin(BAUD_RATE);
  Serial.println("Initializing...");
  delay(1000);
#endif
  // Init ESP8266 communication
  espSerial.begin(BAUD_RATE);
  delay(4000);
#ifdef DEBUG
  Serial.println("Connecting to wifi...");
#endif
  // Connect to wifi
  connectWifi();
  // Do a 1st read of the DHT for initialization
  readHT(ht);
  delay(2000);
  // shut down yellow LED, open green LED
  digitalWrite(LEDY_PIN, LOW);
  digitalWrite(LEDG_PIN, HIGH);
  digitalWrite(LEDB_PIN, LOW);
#ifdef DEBUG
  Serial.println("Starting main loop");
#endif
}

/**
 * main loop
 */
void loop() {
  // Open blue LED when active
  digitalWrite(LEDB_PIN, HIGH);
  // read humidity and temperature
  readHT(ht);
  // send humidity and temperature
  httpPOSTHT(ht);
  // Shut down blue LED before next activation
  digitalWrite(LEDB_PIN, LOW);
  // wait until next interval...
  delay(SENDING_INTERVAL);
}
