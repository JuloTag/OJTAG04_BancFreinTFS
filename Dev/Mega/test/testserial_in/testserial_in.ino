int ledrouge = 7;  
int ledvert = 8; 
String message = "";

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() {
  Serial.begin(9600);
    inputString.reserve(200);
  pinMode(ledrouge, OUTPUT);
  pinMode(ledvert, OUTPUT);
  Serial.println("init");
}

void loop() {
  // put your main code here, to run repeatedly:


  if (stringComplete) {
    Serial.println(inputString);
    message=inputString;
    if (message== "1")
    {
      digitalWrite(ledrouge, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(2000);                       // wait for a second
      digitalWrite(ledrouge, LOW);
    }
    else if (message == "2"){
      digitalWrite(ledvert, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(2000);                       // wait for a second
      digitalWrite(ledvert, LOW);
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

}



void serialEvent() {
  Serial.println("serialevent");
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
