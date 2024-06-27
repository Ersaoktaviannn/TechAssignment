#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4     // Pin data DHT11 terhubung ke GPIO 4
#define DHTTYPE DHT11   // Tipe sensor DHT 11

const char* ssid = "arek kost";
const char* password = "warung24";
const char* serverName = "http://192.168.100.27:139/sensor"; // Ganti dengan IP dan port server lokal Anda

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    
    float temperature = dht.readTemperature();
    
    String jsonPayload = "{\"temperature\":" + String(temperature) + "}";
    
    int httpResponseCode = http.POST(jsonPayload);
    
    if(httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
  
  delay(10000); // Kirim data setiap 10 detik
}
