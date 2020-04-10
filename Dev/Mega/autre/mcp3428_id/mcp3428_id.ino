int I2Cmeasure(byte p, byte mode, int measure_output)
{
  Wire.beginTransmission(p);
  Wire.write(mode);
  Wire.endTransmission();
  Wire.requestFrom(p, 2);
  int temp = Wire.read();
  measure_output = temp << 8;
  measure_output |= Wire.read();
  temp = Wire.read();                 //TODO:check if this line is required
  return measure_output;
}




measureArray[0] = I2Cmeasure(0x68, 0x98, measureArray[0]);  //first channel of the first ADC
  measureArray[1] = I2Cmeasure(0x6D, 0x98, measureArray[1]);  ´//first channel of the second ADC
  measureArray[2] = I2Cmeasure(0x69, 0x98, measureArray[2]);   
  measureArray[3] = I2Cmeasure(0x6C, 0x98, measureArray[3]);
  measureArray[4] = I2Cmeasure(0x6A, 0x98, measureArray[4]);   //all channels are 16 bits, 1x gain and continous mode
  measureArray[5] = I2Cmeasure(0x6F, 0x98, measureArray[5]);
  measureArray[6] = I2Cmeasure(0x68, 0xB8, measureArray[6]);   //second channel of the first ADC
  measureArray[7] = I2Cmeasure(0x6D, 0xB8, measureArray[7]);   //second channel of the second ADC
  measureArray[8] = I2Cmeasure(0x69, 0xB8, measureArray[8]);
  measureArray[9] = I2Cmeasure(0x6C, 0xB8, measureArray[9]);
  measureArray[10] = I2Cmeasure(0x6A, 0xB8, measureArray[10]);
  measureArray[11] = I2Cmeasure(0x6F, 0xB8, measureArray[11]);
  measureArray[12] = I2Cmeasure(0x68, 0xD8, measureArray[12]);   //third channel of the first ADC
  measureArray[13] = I2Cmeasure(0x6D, 0xD8, measureArray[13]);   //thrid channel of the second ADC
  measureArray[14] = I2Cmeasure(0x69, 0xD8, measureArray[14]);
  measureArray[15] = I2Cmeasure(0x6C, 0xD8, measureArray[15]);
  measureArray[16] = I2Cmeasure(0x6A, 0xD8, measureArray[16]);
  measureArray[17] = I2Cmeasure(0x6F, 0xD8, measureArray[17]);


