



// envoi une PWM de frequence 500hz en 3Vcc.

#define Freq_PWN 500    //frequence de la PWN à 500Hz
#define pin_Cons_Frein 2
#define pin_pot_cons A0
 int val = 0;


void setup() {
  pinMode(pin_Cons_Frein, OUTPUT);   // sets the pin as output
  Serial.begin(9600);
  Serial.println("test pwm");
  
}

void loop() {

  val = analogRead(pin_pot_cons);   // lecture ana de 0 a 1023    (50% à 515)
  Serial.print("valpot: ");
  Serial.println(val);
  Serial.print("val_pwm: ");
  Serial.println(val/4);
  analogWrite(pin_Cons_Frein, val / 4);  //Pwm varian entre 0 et 255
  delay(100);
}
