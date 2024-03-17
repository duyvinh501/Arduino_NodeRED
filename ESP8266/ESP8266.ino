#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); //RX, TX
String s = "";
unsigned long t1 = 0;
int e1 = 0, e2 = 0, e3 = 0;
String kc1, kc2, kc3;
String a, b, c;

const char *ssid = "dhtdt_l0714";
const char *password = "nn7c1d08"; 
const char *mqtt_server = "10.41.7.224"; // dia chi IP
const int mqtt_port = 1883; 
const char *mqtt_id = "esp8266";

WiFiClient client;
PubSubClient mqtt_client(client);


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Recived data from: ");
  Serial.println(topic);
  Serial.print("Message: ");
    if(!strcmp(topic,"to-esp8266"))
   {
    
    for (int i = 0; i < length; i++) 
   {  
      Serial.print((char)payload[i]);
      if(millis() - t1 > 500)
      {
        mySerial.println((char)payload[i]);
        delay(100);
        t1 = millis();
      }
   } 
   Serial.println();     
  }
}

void connectmqtt()
{
  Serial.print("Connecting to Wifi... ");
  //Serial.print(ssid);
  //Serial.println();
  WiFi.begin(ssid, password);
  //WiFi.reconnect();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to Wifi ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  delay(1000);

  mqtt_client.setServer(mqtt_server, mqtt_port);
  mqtt_client.setCallback(callback);

  Serial.println("Connecting to mqtt... ");
  while (!mqtt_client.connect(mqtt_id))
  {
    delay(500);
  }
  Serial.println("Connected to mqtt ");
  //mqtt_client.subscribe("abc");
  mqtt_client.subscribe("to-esp8266");
  
}
void UART_MEGA()
{
  if(mySerial.available()>0)
  {
    char c = mySerial.read();
    s += c;
    if ( c == '\n')
    {
      //Serial.println(s);
      
      int TimeA, TimeB, TimeC, TimeD = -1;
      TimeA = s.indexOf("A");
      TimeB = s.indexOf("B");
      TimeC = s.indexOf("C");
      TimeD = s.indexOf("D");
    
      if(TimeA >= 0 && TimeB >= 0)
      {
        kc1 = s.substring(TimeA + 1, TimeB);
        //Serial.println(kc1);
        mqtt_client.publish("from-esp8266-trai", kc1.c_str()  );
      }
      if(TimeB >= 0 && TimeC >= 0)
      {
        kc2 = s.substring(TimeB + 1, TimeC);
        //Serial.println(kc2);
        mqtt_client.publish("from-esp8266-truoc", kc2.c_str()  );
      }
      if(TimeC >= 0 && TimeD >= 0)
      {
        kc3 = s.substring(TimeC + 1, TimeD);
        //Serial.println(kc3);
        mqtt_client.publish("from-esp8266-phai", kc3.c_str()  );
      }
       s = "";
    }
  }
}
void setup() 
{
  Serial.begin(115200);
  mySerial.begin(9600);
  connectmqtt();
}
void loop() 
{ 
  mqtt_client.loop();
  UART_MEGA();
}
