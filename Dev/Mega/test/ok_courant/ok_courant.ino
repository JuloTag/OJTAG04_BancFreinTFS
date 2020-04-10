//include <LiquidCrystal.h>
// mesure courant arduino mega avec current click
#include <SPI.h>

const int chipSelectPinADC = 53; //Using pin 9, but pin 10 would also be fine
unsigned int raw_result = 0;       //Use 16-bits to store the 12-bit result
unsigned int result = 0;
byte inByte = 0; 
int z =0;
unsigned long y = 0;
unsigned int result2 = 0;               
//LiquidCrystal lcd(3, 4, 2, 5, 6, 7);
void setup() {
//  lcd.begin(16, 2);
Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);           //How to read in SPI data, most significant bit first   
  pinMode(chipSelectPinADC, OUTPUT);      //select the pin to control the MCP3201
  digitalWrite(chipSelectPinADC, HIGH);   //set the pin high at initialize
}

void loop() {
//lcd.clear();
raw_result = 0;  
digitalWrite(chipSelectPinADC, LOW);  //Tell the MCP3201 to start sending data
raw_result = SPI.transfer(0x00);          //Read in the first 8 bits of data
raw_result = result << 8;                 //Shift the data left so there is room for the next 8 bits
inByte = SPI.transfer(0x00);          //Read in the last 8 data bits from the MCP3201
raw_result = raw_result | inByte;             //Combine all the data into one value
digitalWrite(chipSelectPinADC, HIGH); //Tell the MCP3201 to wait for your next data request
raw_result = raw_result >> 1 ;                //Shift the result right 1 bit since bit 0 is blank data
Serial.println(raw_result);
raw_result = raw_result & 0b0000111111111111; //Only look at the right 12 bits of the data for a value
//lcd.setCursor(0, 1);
//lcd.print(result);
Serial.print("raw result: ");
Serial.println(raw_result);

//result=raw_result/40;
result=raw_result/8;
Serial.println(result);
delay(500);
}
