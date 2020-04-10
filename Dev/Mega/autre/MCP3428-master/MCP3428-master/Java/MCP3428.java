// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP3428
// This code is designed to work with the MCP3428_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=MCP3428_I2CADC#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class MCP3428
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, MCP3428 I2C address is 0x68(104)
		I2CDevice device = Bus.getDevice(0x68);
		Thread.sleep(300);

		// Select configuration register
		// Continuous conversion mode, Channel-1, 12-bit resolution
		device.write((byte)0x10);

		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data = new byte[2];
		device.read(0x00, data, 0, 2);

		// Convert the data to 12-bits
		int raw_adc = (((data[0] & 0x0F) * 256) + (data[1] & 0xFF));
		if(raw_adc > 2047)
		{
			raw_adc -= 4095;
		}

		// Output data to screen
		System.out.printf("Digital value of Analog Input : %d %n", raw_adc);
	}
}
