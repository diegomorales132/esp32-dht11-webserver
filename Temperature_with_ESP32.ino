#include <WiFi.h>
#include "DHT.h"


const char* ssid     = "(Your SSID)"; 
const char* password = "(Your Password)";

#define DHTPIN 27     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.print("Go to this IP on your browser: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Request.");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            
           
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            
            float h = dht.readHumidity();
            float t = dht.readTemperature();

           
            client.print("<h1>My Room Monitor</h1>");
            
            if (isnan(h) || isnan(t)) {
              client.print("<p>Sensor Error! Check wires.</p>");
            } else {
              client.print("<p>The Temperature is: ");
              client.print(t);
              client.print(" C</p>");
              
              client.print("<p>The Humidity is: ");
              client.print(h);
              client.print(" %</p>");
            }
            
            
            client.print("<br><a href=\"/\">Click to Refresh</a>");
            
            break; 
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected.");
  }
}
