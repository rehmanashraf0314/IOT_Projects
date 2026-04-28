#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// === GPS Pin Configuration ===
static const int RXPin = 15;  // GPS TX to ESP8266 D6 (GPIO12)
static const int TXPin = 13;  // Not used, but required for SoftwareSerial
static const uint32_t GPSBaud = 9600;

// === Initialize GPS and Serial ===
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin); // RX, TX

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("🔄 Starting GPS Module..."));

  gpsSerial.begin(GPSBaud);
  Serial.println(F("✅ GPS Serial initialized."));
}

void loop() {
  // Read from GPS and feed to GPS parser
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    gps.encode(c);
  }

  // If a valid location was found
  if (gps.location.isUpdated()) {
    Serial.println(F("✅ GPS Fix Acquired:"));
    Serial.print(F("📍 Latitude: "));   Serial.println(gps.location.lat(), 6);
    Serial.print(F("📍 Longitude: "));  Serial.println(gps.location.lng(), 6);
    Serial.print(F("📡 Satellites: ")); Serial.println(gps.satellites.value());
    Serial.print(F("⛰️ Altitude: "));    Serial.print(gps.altitude.meters()); Serial.println(F(" m"));
    Serial.println(F("----------------------------"));
  } else {
    Serial.println(F("⚠️  Waiting for GPS fix..."));
  }

  delay(1000); // Delay to avoid flooding
}
