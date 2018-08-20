#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Tenda";
const char* password =  "asdf1234";
const char* mqttServer = "m11.cloudmqtt.com";
const int mqttPort = 17735;
const char* mqttUser = "hitcmgji";
const char* mqttPassword = "QtOnRR0io93j";
const char* topics[2] = {"esp/relay1","esp/relay2"};
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  for(int i=0;i<sizeof(topics);i++){
    client.subscribe(topics[i]);
    client.publish(topics[i], "Hello from ESP8266");
  }
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
