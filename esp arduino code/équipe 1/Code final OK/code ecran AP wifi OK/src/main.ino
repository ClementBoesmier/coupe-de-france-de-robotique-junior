#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#define pin_A 16
#define pin_B 12
#define pin_sclk 0
#define pin_clk 14
#define pin_r 13
#define pin_noe 15

#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1
SPIDMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH, pin_noe, pin_A, pin_B, pin_sclk); // DMD controls the entire display


const char* ssid = "Panneau2018";//id du résau
const char* password = "mogetator";//mdp du résau

String E2Issid = ssid;
String E2Ipassword = password;
const char* ipW ="192.168.4.1";//ip de l'esp

unsigned int localPort = 8000;//port de communication aec l'esp
unsigned int distPort = 9000;
char Ipremote;
byte packetBuffer[3024];

String request = "";
String lastrequest = "";

WiFiUDP Udp;

int conteur(185);

void setup() {
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.reconnect();

  Serial.begin(9600);
  Serial.println("");
  Serial.println("WiFi Connected");

  Udp.begin(localPort);
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.softAPIP());
  Serial.println("/");

  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();

}

void loop() {

//dmd.drawString(0,0,String(conteur));
int noBytes = Udp.parsePacket();
  request = "";
  if (!noBytes) {
   return;
  }

  Ipremote=Udp.remoteIP();
  Udp.read(packetBuffer,noBytes);

  for (int i=1;i<=noBytes;i++)
    {
      request = request + char(packetBuffer[i - 1]);
    }
  Serial.println(request);
  dmd.clearScreen();
  dmd.drawString(0,0,request);
}
