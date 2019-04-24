

int pinStop = 15;
int pinStart = 13;
int etatStart = 1;
int etatStop = 0;
int stopM = 1;
int Thaut = 0;
int Tbas = 0;
bool etatled=0;
int cycle=10000;
int demicycle=5000;
int vitmoteur=1000;
#define MOTEUR 2  //On board LED
 
//=======================================================================
void ICACHE_RAM_ATTR onTimerISR(){
   // digitalWrite(LED,!(digitalRead(LED)));  //Toggle LED Pin
   if (etatled==0) {digitalWrite(MOTEUR,HIGH);etatled=1;} else {digitalWrite(MOTEUR,LOW);etatled=0;}
   if (etatled==1) {demicycle=vitmoteur*5;}
   if (etatled==0) {demicycle=10000-(vitmoteur*5);}
    timer1_write(demicycle);//12us
}
//=======================================================================
//                               Setup
//=======================================================================


void setup() {
  

      pinMode(MOTEUR,OUTPUT);
 
    //Initialize Ticker every 0.5s
    timer1_attachInterrupt(onTimerISR);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
    timer1_write(5000); //120000 us

  digitalWrite(2,LOW);
  Serial.begin(9600);
  pinMode(pinStop, INPUT);
  pinMode(pinStart, INPUT);
  
  while(etatStart == HIGH){
    Serial.println("wait");
    vitmoteur=1000;
    etatStart = digitalRead(pinStart);
    delay(30);
  }
  Serial.println("GO !");
}

void loop() {
  etatStop = digitalRead(pinStop);
  
  if (etatStop == HIGH){
    Serial.println("stop");
    vitmoteur=1000;
    stopM = 0;
  }
  if(stopM == 1){
    vitmoteur=1195;

  }
}
