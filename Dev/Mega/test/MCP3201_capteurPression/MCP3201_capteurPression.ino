//////////////////////////////////////////////////////////
//  TEST mesure de courant avec le module current click //
// basé sur un MCP3201 et utilisant une resistance de   //
// 0,2Ohm 1% 3W.                                        //
//////////////////////////////////////////////////////////
// Brochage MEGA  --> CurrentClick          //
//  3.3V      -->    3.3V             //
//  GND           -->    GND              //
//  MISO(53)      -->    SDA              //
//  SCK(52)       -->    SCK              //
//  SS(53)        -->    CS  A CHANGER           //
//////////////////////////////////////////////////////////  
#include <SPI.h>

#define ADCpression_CS 53
 
void setup() {

  pinMode (ADCpression_CS, OUTPUT);
  digitalWrite(ADCpression_CS, 0);
  delay(100);
  digitalWrite(ADCpression_CS, 1);

  // initialize serial
  Serial.begin(9600);
  // initialize SPI
  SPI.begin();
}
 
void loop() {

  unsigned int Raw_Value = read_raw();
  unsigned int Mesured_Current = Raw_Value/8;
  Serial.print("Measured current: ");
  Serial.print(Mesured_Current);
  Serial.println(" mA");

  unsigned float Pression = (Mesured_Current-7.356)*12.42;   // selon calcul de la pente du capteur de forme ax+b //utiliser un float????
  Serial.print("Pression: ");
  Serial.print(Pression);
  Serial.println(" Bars");
  
  // volts = read_volts(ADC_offset);
  // Serial.print("Measured voltage: ");
  // Serial.println(volts);
  delay(1000);
}
 
 
unsigned int read_raw(void){
/*
DAC works on SPI
We receive 16 bits
Of which we extract only 12 bits
MCP3201 has a strange way of formatting data
with 5 bits in the first byte and
the rest of 7 bits in the second byte
*/
  unsigned int result;
  unsigned int first_byte;
  unsigned int second_byte;
  unsigned int ADC_avrg = 0;
  // Average of four readings
  for (int i=0; i<4; i++){
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
    digitalWrite(ADCpression_CS, 0);
    first_byte = SPI.transfer(0);
    second_byte = SPI.transfer(0);
    digitalWrite(ADCpression_CS, 1);
    SPI.endTransaction();
   
    /* After the second eight clocks have been
    sent to the device, the MCU receive register
    will contain the lowest order seven bits and
    the B1 bit repeated as the A/D Converter has begun
    to shift out LSB first data with the extra clock.
    Typical procedure would then call for the lower order
    byte of data to be shifted right by one bit
    to remove the extra B1 bit.
    See MCP3201 datasheet, page 15
    */
    result = ((first_byte & 0x1F) << 8) | second_byte;
    result = result >> 1;
    ADC_avrg = ADC_avrg + result;
    // wait 10 ms between readings
    delay(10);
  }
  ADC_avrg = ADC_avrg / 4;
  //Serial.print("MCP_RAW: ");
  //Serial.println(ADC_avrg);  
  return ADC_avrg;
}
ADCpression_CS
