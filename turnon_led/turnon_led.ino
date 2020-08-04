#include <ESP8266HTTPClient.h>

#include <DHT11.h>
#include <ESP8266WiFi.h>
int pin = 14;
DHT11 dht11(pin);

const char* ssid = "ARRIS-D752";
const char* password = "3A73C60C3B1E2AAD";
 
void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT); 

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");
  Serial.println("IP :");
  Serial.print(WiFi.localIP());

   

}

void loop() {

  float temp, hum; 
  float data = dht11.read(hum, temp);
  Serial.println("Temperatura: ");
  Serial.println(temp);
  delay(500);
  Serial.println("Humedad: ");
  Serial.println(hum);
  delay(500);
  digitalWrite(D0, HIGH);
  delay(200);
  digitalWrite(D0, LOW);
  delay(200);

  if(WiFi.status() == WL_CONNECTED){
     HTTPClient http;

     http.begin("http://192.168.0.11:3000/temperatura/");
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
     String temperatura = String(temp);
     String humedad = String(hum);
     
     String postData = temperatura + "&" + humedad;
     Serial.println(postData);
     int codigo = http.POST("100&100");
     Serial.println("Respuesta: ");
     Serial.println(codigo);
     delay(2000);
  }
  
  

}
