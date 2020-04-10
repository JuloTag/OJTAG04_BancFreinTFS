// Gregg Messenger      December 18, 2014
// This Sketch is for the DUE board and utilizes the "Extended SPI Library" available for the DUE.
// The purpose of this sketch is to read 12 bit data from an MCP3201 12 bit ADC chip and to send it to the serial monitor.
// Note: The DUE is a 32 bit system that uses 3.3v logic.  Don't apply 5 volts to any of the pins on this board!

// Wiring Map
// MCP3201            DUE
// Pin 1 Vref  -->  3.3v (DUE)
// Pin 2 IN+   -->  Center pin of 5k potentiometer
// Pin 3 IN-   -->  GND (DUE)
// Pin 4 Vss   -->  GND (DUE)
// Pin 5 CS    -->  Pin 10 (DUE)
// Pin 6 Dout  -->  MIMO Pin 1 on SPI Header (DUE)
// Pin 7 CLK   -->  SCK Pin 3 on SPI Header (DUE)
// Pin 8 Vdd   -->  3.3v (DUE)

// Left pin on potentiometer goes to Pin 1 (Vref) on MCP3201
// Right pin on potentiometer goes to GND
// Install a decoupling capacitor (.1uF ceramic disc) across pins 2 & 3 on the MCP3201 to eliminate noise on the input.

#include <SPI.h>

unsigned int result = 0;       //Initialize the 32 bit variable used to store the 12 bit value from the MCP3201
byte byteOne = 0;              //Initialize an 8 bit variable to read the first byte from the MCP3201
byte byteTwo = 0;              //Initialize another 8 bit variable to read the second byte
float percent = 0;             //Initialize a float variable to display percentage with capability of decimal places

void setup() {

  Serial.begin(9600);                //Open the serial port at 9600 baud
  SPI.begin(10);                     //Initialize the bus for a device on pin 10
  SPI.setDataMode(10,1);             //Set SPI data mode to 1
  SPI.setBitOrder(10, MSBFIRST);     //Expect the most significant bit first, apply rule only to pin 10
  SPI.setClockDivider(10, 42);       //Set clock divider on pin 10 to 42 (84 MHz / 42 = 2 MHz SPI bus speed)
 
}

void loop() {
 
  byteOne = SPI.transfer(10, 0x00, SPI_CONTINUE);     //Read the first byte from the MCP3201, keep CS active LOW for the next byte to transfer
  byteTwo = SPI.transfer(10, 0x00, SPI_LAST);         //Read the second byte, take CS pin 10 HIGH to disable the MCP3201
  
  result = byteOne;                                           //Store the first byte into the result variable
  result = result << 8;                                       //Shift the first byte left 8 bits.
  result = result | byteTwo;                                  //Combine the two bytes into a 16 bit word (stored in a 32 bit variable) using OR function
  result = result >> 1;                                       //Shift the bits in the word to the right 1 places.  Bit 0 from MCP3201 is blank data.                                                      
  result = result & 0b00000000000000000000111111111111;       //Bit mask the first 20 bits using the AND function.  We only want to look at the last 12 bits
  percent = ((float) result/4096*100);                        //Cast the result integer into a float variable, calculate percentage.
  
  Serial.println(percent,1);                           //Display the final result using the serial monitor.  1 decimal place.

}
