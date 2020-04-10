// produit une PWM variant en raport cyclique avec des temps de pause(environ 30sec) et des temps de montées/descentes (10sec)

#define Freq_PWN 500    //frequence de la PWN à 500Hz (non utilisé)
#define pin_Cons_Frein 2    //utilise la broche 2 de l'arduino pour la generation de la pwm
//#define pin_pot_cons A0
int message = 0;
int val = 0;
bool etatcycle = false;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 100;
//////////////////////////////////////////////////////////////
void setup() {
  pinMode(pin_Cons_Frein, OUTPUT);                        // sets the pin as output
  Serial.begin(9600);                                     // pour test
  Serial.println("test cycle");                           // pour test
}
//////////////////////////////////////////////////////////////
void loop() {
  if (Serial.available())  {
    message = Serial.read();
    if (message == 22){
      etatcycle = true;
      Serial.println("CycleAuto ON");
    }
    else {
      etatcycle = false;
      Serial.println("CycleAuto OFF");
    }
  }
  if (etatcycle == true)  {
    cyclemonte2();
    cycledescente();
  }
}
//////////////////////////////////////////////////////////////
void cyclemonte2(){
  currentMillis = 0;
  Serial.println("montee");                               // pour test
//  Serial.println(val);
  //val=800;
  while(val<=1023){
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      val=val+10;
      int val2= val/4;
      if(val2>=255){
        val2=255;
      }
      Serial.println(val);                  // pour test
      analogWrite(pin_Cons_Frein, val2);    //Pwm varian entre 0 et 255
    }
  }
}
//////////////////////////////////////////////////////////////
void cycledescente(){
  currentMillis = 0;
  Serial.println("descente");               // pour test
//  Serial.println(val);
  //val=800;
  while(val>=0){
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      val=val-10;
      int val2= val/4;
      if(val2<=0){
        val2=0;
      }
      Serial.println(val);                  // pour test
      analogWrite(pin_Cons_Frein, val2);    //Pwm varian entre 255 et 0
    }
  }
}
