#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>

int localPort(8000);
int distPort(9000);

const char* ipW ="192.168.4.2";
WiFiUDP Udp;

const char* UdpIP = "192.168.4.1";

int pinBouton1(15);
int pinBouton2(13);

String MPD = "mogetator";
String ID =  "Panneau2018";

void setup() {
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ID.c_str(),MPD.c_str());
  
  Udp.begin(localPort);

  
   pinMode(pinBouton1, INPUT);
   pinMode(pinBouton2, INPUT);

}

void loop() {
  int etatBouton1 = digitalRead(pinBouton1);
  int etatBouton2 = digitalRead(pinBouton2);

  if(etatBouton1 == HIGH){
    Udp.beginPacket(UdpIP, localPort);
    Udp.println("+5");
    Udp.endPacket();
    delay(200);
  }
  if(etatBouton2 == HIGH){
    Udp.beginPacket(UdpIP, localPort);
    Udp.println("-5");
    Udp.endPacket();
    delay(200);
  }
}
