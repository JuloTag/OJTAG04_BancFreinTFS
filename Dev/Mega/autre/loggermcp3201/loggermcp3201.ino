/*

Jesse Campbell
2014-11-28
SD card datalogger + MCP3201 analog-to-digital converter 

RFDuino SPI Pins are:

MOSI -> GPIO5
MISO -> GPIO3
SCK -> GPIO4

Chip/Signal Select Pins are: 

CS SD Card -> GPIO6
CS MCP3201 -> GPIO2

SD card should be formated in FAT16

Based on: 

http://www.speedlimit88.com/arduino/spi_adc/
Arduino > Examples > SD Library

Parts used: 

http://www.ebay.com/itm/Read-And-Write-For-Arduino-ARM-MCU-1pcs-SD-Card-Module-Slot-Socket-Reader-New-BQ-/251472408054?pt=LH_DefaultDomain_2&hash=item3a8cec6df6
http://www.karlssonrobotics.com/cart/RFduino-Dev-Kit/?gclid=CjwKEAiA1-CjBRDOhIr_-vPDvQYSJAB48SmECXsxGBuSnWfWvQkqP76xsVxAQA4vpjyfeCayd8YwIBoCOCfw_wcB
http://www.ebay.com/itm/141457779249
http://www.ebay.com/itm/151381040568

Screenshot: http://imgur.com/1YuePlw
Circuit: http://i.imgur.com/mIcv01N.jpg
*/

#include <SPI.h>
#include <SD.h>

const uint8_t chipSelectMCP3201 = 2; //GPIO2
const uint8_t chipSelectSDCard = 6; //GPIO6
File dataFile;

unsigned int bytesWritten = 0;
unsigned long startTime = 0;

const unsigned int bufferSize = 512;
uint8_t bufferArray[bufferSize];

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(1000000); //1 Mbps
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelectSDCard, OUTPUT);

  // see if the card is present and can be initialized:
  while (!SD.begin(chipSelectSDCard)) {
    Serial.println("Card failed, or not present");
    //try plugging SD card in
    delay(1000);
  }
  Serial.println("card initialized.");
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  SPI.setBitOrder(MSBFIRST);
  pinMode(chipSelectSDCard, OUTPUT);
}

void loop()
{
  if (startTime == 0)
    startTime = millis();
 
    for (unsigned int bufferPosition = 0; bufferPosition < bufferSize; bufferPosition++){
      digitalWrite(chipSelectMCP3201, LOW);
      bufferArray[bufferPosition] = SPI.transfer(0x00);
      digitalWrite(chipSelectMCP3201, HIGH);
    }

  bytesWritten += dataFile.write(bufferArray,bufferSize);
  
  if (millis()-startTime > 1000){
  	dataFile.flush();
    dataFile.close();
    Serial.println("finished");
    Serial.print("bytes written: ");    
    Serial.println(bytesWritten);
    while(true);
  }
}

