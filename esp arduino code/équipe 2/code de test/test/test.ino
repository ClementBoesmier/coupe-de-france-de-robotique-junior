
/*----------------------------Documentation--------------------------*/

/*WIFIAP*/
// https://techtutorialsx.com/2017/07/26/esp32-arduino-setting-a-soft-ap/
// https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst#softap

/*UDP*/
// https://www.arduino.cc/en/Reference/EthernetUDPParsePacket
// https://www.arduino.cc/en/Reference/EthernetUDPRead

/*----------------------------Code----------------------------*/

#include <ESP8266WiFi.h>
const char *ssid = "MyESP"; // choose a wifi name (ssid)
const char *password = "1234567890"; // choose a wifi password (nothing = no password)

#include <WiFiUDP.h>
WiFiUDP Udp;
unsigned int localUdpPort = 8000; // choose the udp port
byte PacketBuffer[3024]; // choose the size (in bits) of the packet buffer
String request = ""; // my object for the storage of the received packages
int led(2); // indicator led pin
int myDelay(10);

void setup() {
        WiFi.mode(WIFI_OFF); // turn off the wifi
        delay(200); // wait 0.2 seconde
        WiFi.mode(WIFI_AP); // turn on the wifi access point mode
        WiFi.softAP(ssid, password); // lunch the access point

        Serial.begin(9600); // start a serial connection
        Serial.println(); // make an enter
        Serial.print(WiFi.softAPIP()); // and print the ip adresse of the esp

        Udp.begin(localUdpPort); // lunch the udp server
        pinMode(led, OUTPUT); // initialize the led indicator

}

void loop() {
        int packetSize = Udp.parsePacket(); // parcePacket affect the size (in bit) of the receive packet to the variable called "packSize"
        if (!packetSize) { // if packSize is not equal to parsePacket, this make a thing like "while" fonction
                return;
        }
        Udp.read(PacketBuffer, packetSize);
        for (int i = 1; i <= packetSize; i++) { // If the variable called "i" (set to one by default) is inferior or equal to the packSize, add 1. Store all of the caractere of the packetbuffer in a string object
                request = request + char(PacketBuffer[i - 1]); // -1 to the variable "i" to make a loop if nothing is received ?
        }
        Serial.print(request); // print the message receive by udp (wifi)
        request = ""; // erease the message for the next package
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.print("OK");
        Udp.endPacket();
        for (int i = 0; i <= packetSize; i++) {         // do the following code the same number of times as the size the udp packet (in bits)
                digitalWrite(led,HIGH);         // turn on the led
                delay(myDelay);         // wait
                digitalWrite(led,LOW);         // turn off the led
                delay(myDelay+10);         // the LOW(off) time is much higher than the HIGH(on) for optimizing readability
        }
}
