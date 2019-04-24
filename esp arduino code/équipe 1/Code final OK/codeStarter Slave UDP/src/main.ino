#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

String chaine = "";

char key;

int localPort(8000);
int distPort(9000);

int softStart = 0;

const char* MonIP ="192.168.4.2";
const char* EcranIP = "192.168.4.255";
const char* RobotIP = "192.168.4.255";
WiFiUDP Udp;

const char* password = "mogetator";
const char* ssid =  "Panneau2018";

void setup() {
  Serial.begin(9600);
  wifiBegin();

  Udp.begin(localPort);

  pinMode(12, INPUT);

}

void loop() {
  int starte = digitalRead(12);
  if (softStart == 0 && starte == LOW) {
    softStart = 1;
    senderRobot();
  }
}


void senderRobot() {
  Udp.beginPacket(RobotIP, localPort);
  Udp.println("Start");
  Udp.endPacket();
  delay(200);
}


void wifiBegin() {
  WiFi.mode(WIFI_OFF);
  delay(200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.print(" connected : ");
  Serial.println(WiFi.localIP().toString().c_str());
}
