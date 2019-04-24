#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Keypad.h>



const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {2, 0, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15, 13, 12}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String chaine = "";

char key;

int localPort(8000);
int distPort(9000);

const char* MonIP ="192.168.4.2";
const char* EcranIP = "192.168.4.1";
const char* RobotIP = "192.168.4.3";
WiFiUDP Udp;


String MPD = "mogetator";
String ID =  "Panneau2018";

void setup(){
  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ID.c_str(),MPD.c_str());

  Udp.begin(localPort);

}

void loop(){
  key = keypad.getKey();

  if (key){
    if (String(key) == "#"){
      senderScore();
      reset();
    }else if (String(key) == "*") {
      Serial.println("* OK !");
      senderRobot();
    }else{
      Serial.println(key);
      pad();
    }
  }
}
