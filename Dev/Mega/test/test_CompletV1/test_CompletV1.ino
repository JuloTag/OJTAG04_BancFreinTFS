

#define Freq_PWN 500    //frequence de la PWN à 500Hz (non utilisé)
#define pin_Cons_Frein 2    //utilise la broche 2 de l'arduino pour la generation de la pwm

int val = 0;
bool etatcycle = false;
bool etatcarac = false;
int message = 0;
int ledrouge = 7;
int ledverte = 8;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 100;



//////////////////////////////////////////////////////////////
void setup()
{ 
  Serial.begin(9600);
  pinMode(ledrouge, OUTPUT);
  pinMode(ledverte, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);   
}
//////////////////////////////////////////////////////////////
void loop()
{
  if (Serial.available())  {
    message = Serial.read();//-'0';  // on soustrait le caractère 0, qui vaut 48 en ASCII
    if (message == 65){
      
      etatcarac = true;
      etatcycle = false;
      
    }
    else if (message == 97){
      
      etatcycle = true;
      etatcarac = false;
    }
  }
  if (etatcarac == true)
  {
    digitalWrite(ledrouge, HIGH);
    delay(100);
    digitalWrite(ledrouge, LOW);
    Serial.println(message);
    delay(100);
    Serial.println("Carac");  
    CaracAuto();
  } 
  if (etatcycle == true)
  {
    digitalWrite(ledverte, HIGH);
    delay(100);
    digitalWrite(ledverte, LOW);
    Serial.println(message); 
    delay(100);
    Serial.println("cycleAuto"); 
    CycleAuto();
  }

}
//////////////////////////////////////////////////////////////
void CaracAuto(){
  
}
//////////////////////////////////////////////////////////////
void CycleAuto(){
  cyclemonte();
  cycledescente();
}

//////////////////////////////////////////////////////////////
void cyclemonte(){
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
