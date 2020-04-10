//////////////////////////////////////////////////////////
//  TEST mesure de courant avec le module current click //
// basé sur un MCP3201 et utilisant une resistance de   //
// 0,2Ohm 1% 3W.                                        //
//////////////////////////////////////////////////////////
// Brochage MEGA	--> CurrentClick					//
//	3.3V			-->    3.3V							//
//	GND        		-->    GND							//
//	MISO(53)   		-->    SDA							//
//	SCK(52)    		-->    SCK							//
//	SS(53)     		-->    CS							//
//////////////////////////////////////////////////////////	
#include <SPI.h>

#define ADC_CS 53
 
int volts;
// this is determined emiprically, putting the input into short and reading the ADC readout
int ADC_offset = 2040;
 
void setup() {
	/* Resetting MCP3201
	* From MCP3201 datasheet: If the device was powered up
	* with the CS pin low, it must be brought high and back low
	* to initiate communication.
	* The device will begin to sample the analog
	* input on the first rising edge after CS goes low. */
	pinMode (ADC_CS, OUTPUT);
	digitalWrite(ADC_CS, 0);
	delay(100);
	digitalWrite(ADC_CS, 1);

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
		digitalWrite(ADC_CS, 0);
		first_byte = SPI.transfer(0);
		second_byte = SPI.transfer(0);
		digitalWrite(ADC_CS, 1);
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
	Serial.print("MCP_RAW: ");
	Serial.println(ADC_avrg);  
	return ADC_avrg;
}
 
int read_volts (int zero_offset){
	int myvolts;
	int ADC_readout = read_raw();
	myvolts = (int)(float(ADC_readout - zero_offset) * 16.6667);
	return myvolts;
}
