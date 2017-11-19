// DHT sensor library - Version: Latest
#include <DHT.h>

// Uncomment to display debug info to Serial Monitor
// #define DEBUG

#define DHT11_PIN 10

#define LEDB_PIN 5
#define LEDY_PIN 7
#define LEDR_PIN 9

#define YELLOW_THRESHOLD 19.0
#define RED_THRESHOLD 21.0

#define BAUD_RATE 9600


DHT dht11(DHT11_PIN, DHT11);

float temperature;
float humidity;

/**
 * setup Weather Station module
 * - Set pin mode for LEDs
 */
void setup() {
    pinMode(LEDB_PIN, OUTPUT);
    pinMode(LEDY_PIN, OUTPUT);
    pinMode(LEDR_PIN, OUTPUT);
    delay(500);
    digitalWrite(LEDB_PIN, HIGH);
    digitalWrite(LEDY_PIN, LOW);
    digitalWrite(LEDR_PIN, LOW);
#ifdef DEBUG
    Serial.begin(BAUD_RATE);
    Serial.println("Initializing...");
#endif
    dht11.begin();
    delay(5000);
#ifdef DEBUG
    Serial.println("Starting main loop");
#endif
}

/**
 * main loop
 */
void loop() {
      // switch off all LEDs
    digitalWrite(LEDB_PIN, LOW);
    digitalWrite(LEDY_PIN, LOW);
    digitalWrite(LEDR_PIN, LOW);
    delay(500);

    // animate LEDs
    digitalWrite(LEDB_PIN, HIGH);
    delay(150);
    digitalWrite(LEDY_PIN, HIGH);
    delay(150);
    digitalWrite(LEDR_PIN, HIGH);
    delay(150);
    digitalWrite(LEDB_PIN, LOW);
    digitalWrite(LEDY_PIN, LOW);
    digitalWrite(LEDR_PIN, LOW);
    delay(100);

    // read humidity and temperature
    temperature = dht11.readTemperature(false, true);
    humidity = dht11.readHumidity();

#ifdef DEBUG
    Serial.print("Temperature = ");
    Serial.println(temperature);
    Serial.print("Humidity = ");
    Serial.println(humidity);
#endif

    // switch on LED according to temp thresholds
    if (temperature >= RED_THRESHOLD) {
        digitalWrite(LEDR_PIN, HIGH);
    } else if (temperature >= YELLOW_THRESHOLD) {
        digitalWrite(LEDY_PIN, HIGH);
    } else {
        digitalWrite(LEDB_PIN, HIGH);
    }

    // wait 10 seconds...
    delay(10000);
}
