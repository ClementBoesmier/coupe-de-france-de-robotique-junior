void pad() {
  chaine = String(chaine + key);
  Serial.print("mem : ");
  Serial.println(chaine);
}

void reset(){
  chaine = "";
  Serial.println("reset");
}

void senderScore() {
  Udp.beginPacket(EcranIP, localPort);
  Udp.println(chaine);
  Udp.endPacket();
  delay(200);
}

void senderRobot() {
  Udp.beginPacket(RobotIP, localPort);
  Udp.println("Start");
  Udp.endPacket();
  delay(200);
  Serial.println("Send Start OK");
}
