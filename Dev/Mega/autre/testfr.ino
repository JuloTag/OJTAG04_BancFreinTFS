

#include <MCP3428.h>
#include <Wire.h>

MCP3428 MCP(0); // Declaration of MCP3428: A2, A1, A0 bits (000, 0x68)





const int pwmPin =  12;


const int PulseIN = 7;      // pulse counter pin
float ONCycle;              //oncycle variable 
float OFFCycle;             // offcycle variable got microsecond
float T;                    // tota l time to one cycle ONCycle + OFFcycle
int F;                      // Frequency = 1/T
float DutyCycle;            // D = (TON/(TON+TOFF))*100 %



void setup() {

  Serial.begin(9600);  // init. serial
  pinMode(pwmPin, OUTPUT);
  pinMode(PulseIN, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    //// Variable analogique
  int consignefrein  = analogRead(A0); // valeur sur 1024
  int val_capcharge1 = analogRead(A1);
  int val_capcharge2 = analogRead(A2);
  int alim_captcharge = analogRead(A3);
  int alim_SV = analogRead(A4);
  int courant_SV = analogRead(A5);
  int alim_PGO = analogRead(A6);
  int courant_PGO = analogRead(A7);
  int phase_moteur = analogRead(A8);
  int courant_moteur = analogRead(A9);
  int alim_PC = analogRead(A10);
  int courant_PC = analogRead(A11);

  int alim_tiroir = analogRead(A12);
  int alim_captPos = analogRead(A13);
  int demod = analogRead(A14);
  int courant_EC4 = analogRead(A15); 
// mesure frequence 
// mesure rapport cyclique


    //// Variable numerique
  int Capt_niveau = digitalRead(pin);
  int Capt_temp = digitalRead(pin);
  int Def_frein = digitalRead(pin);
  int frein1_serre
  int frein2_serre
  int frein1_desserre
  int frein2_desserre



  analogWrite(pwmPin, consignefrein/4); // valeur max du pwm de 255
  float voltage = consignefrein * (5.0 / 1023.0);
  Serial.println(consignefrein);
  Serial.println(voltage);
  delay(100);
}
 void DutyCycle_transmissionCharge()
{
  ONCycle = pulseIn(PulseIN, HIGH);
  OFFCycle = pulseIn(PulseIN, LOW);
  T = ONCycle + OFFCycle;
  DutyCycle = (ONCycle / T) * 100;
  F = 1000000 / T;                    // 1000000= microsecond 10^-6 goes to upper
  Serial.print("Frequency = ");
  Serial.print(F);
  Serial.print(" Hz");
  Serial.print("\n");
  Serial.print("DutyCycle = ");
  Serial.print(DutyCycle, 2);
  Serial.print(" %");
  Serial.print("\n");



}



void MCP3428_ADC ()
{
    long Raw_ADC[4];
    float voltage[4];
    for(int i=1;i<=4;i++)
    {
        // MCP3428 is configured to channel i with 12 bits resolution, continuous mode and gain defined to 1
        MCP.SetConfiguration(i,12,1,1);
        Raw_ADC[i-1] = MCP.readADC();
        float voltage[i-1] = Raw_ADC[i-1] * (2.048 / 2047.0);
        // print results
        Serial.print("DigitVal of Channel ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(Raw_ADC[i-1]);
        Serial.print("Tension = ");
        Serial.println(voltage[i-1]);        
        delay(100);
    }
    delay(100);
}




