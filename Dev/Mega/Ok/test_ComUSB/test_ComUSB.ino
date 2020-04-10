/******************************************************************************************
 * L'Arduino attend la requête du Rasperry Pi.  Lorsqu'il reçoit cette requête, il envoie en
 * retour le signal mesuré à la pin A0.
 *
 * http://electroniqueamateur.blogspot.com/2014/05/communication-par-usb-entre-raspberry.html
 *
 ******************************************************************************************/
int ledrouge = 7;  
int ledvert = 8; 
int message = 0;


void setup()
{ 
  Serial.begin(9600);
  pinMode(ledrouge, OUTPUT);
  pinMode(ledvert, OUTPUT);
}

void loop()
{
  if (Serial.available())  {
    message = Serial.read()-'0';  // on soustrait le caractère 0, qui vaut 48 en ASCII

    if (message == 5){
      Serial.println(analogRead(A0),DEC);
      digitalWrite(ledrouge, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(2000);                       // wait for a second
      digitalWrite(ledrouge, LOW);
    }
  }
}
