
#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#define LED_PIN 2 // Change 
const char* ssid = "Note 7"; 
const char* password = "12345671011";  
const char* mqtt_server = "broker.hivemq.com";  
const int mqtt_port = 1883; 
WiFiClient espClient; 
PubSubClient client(espClient); 
const char* topic = "pieas/esp8266/led";
void setup() { 
Serial.begin(115200); 
pinMode(LED_PIN, OUTPUT); 
digitalWrite(LED_PIN, LOW); // LED OFF initially 
// Connect to WiFi 
WiFi.begin(ssid, password); 
while (WiFi.status() != WL_CONNECTED) { 
delay(1000); 
Serial.println("Connecting to WiFi..."); 
} 
Serial.println("Connected to WiFi"); 
// Connect to MQTT Broker 
client.setServer(mqtt_server, 1883); 
while (!client.connected()) { 
Serial.println("Connecting to MQTT..."); 
if (client.connect("ESP8266Client")) { 
Serial.println("Connected to MQTT Broker"); 
} else { 
Serial.print("Failed, rc="); 
Serial.print(client.state()); 
Serial.println(" Retrying..."); 
delay(2000); 
} 
} 
} 
void loop() { 
if (Serial.available()) { 
char key = Serial.read(); // Read input from Serial Monitor 
if (key == 'p') { // Press 'p' to toggle LED 
digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED 
// Publish LED state 
if (digitalRead(LED_PIN) == HIGH) { 
client.publish(topic, "ON"); 
Serial.println("LED is ON"); 
} else { 
client.publish(topic, "OFF"); 
Serial.println("LED is OFF"); 
} 
} 
} 
client.loop();  
}