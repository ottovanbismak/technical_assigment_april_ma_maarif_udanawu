#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 5
DHT dht(DHTPIN, DHTTYPE);

// Replace with your network credentials
const char* ssid = "rusak";
const char* password = "nggakenek";

// Server endpoint
const char* serverName = "http://192.168.43.210:5000/"; // Replace with your Flask server IP and port

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println("Connected to the WiFi network");
  dht.begin();

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    Serial.println(h);
    Serial.println(t);
    // Specify content-type header
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Create JSON object
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["suhu"] = h;
    jsonDoc["kelembapan"] = t;
    jsonDoc["nama"] = "yanti";


    // Serialize JSON object to string
    String requestBody;
    serializeJson(jsonDoc, requestBody);

    // Send POST request
    int httpResponseCode = http.POST(requestBody);

    // Check the response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Send a request every 10 seconds
  delay(1000);
} 