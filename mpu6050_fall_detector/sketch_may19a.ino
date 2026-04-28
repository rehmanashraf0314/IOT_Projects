#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h> //i2c 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Note7";
const char* password = "12345671011";

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected!");

  // Initialize I2C for ESP8266
  Wire.begin(4, 5);  // SDA=GPIO4, SCL=GPIO5

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("❌ ERROR: Failed to find MPU6050 chip.");
    while (1) delay(1000);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("✅ MPU6050 initialized.\n");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.println("📈 Sensor Readings:");
  Serial.printf("  Accel Z: %.2f m/s²\n", a.acceleration.z);

  // Check if Z acceleration is negative
  if (a.acceleration.z < 0) {
    Serial.println("⚠ Negative Z acceleration detected. Sending HTTP POST...");

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, "http://192.168.43.167:8000/send_location/");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String lat = "31.5204";  // Hardcoded latitude 
      String lon = "74.3587";  // Hardcoded longitude
      String postData = "lat=" + lat + "&lon=" + lon;

      int httpCode = http.POST(postData);

      if (httpCode > 0) {
        Serial.printf("HTTP POST sent. Status code: %d\n", httpCode);
        String response = http.getString();
        Serial.println("Response: " + response);
      } else {
        Serial.printf(" HTTP POST failed. Error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
      
    } else {
      Serial.println(" WiFi not connected.");
    }
  }

  Serial.println("----------------------------------");
  delay(1000); // Delay between readings
}
