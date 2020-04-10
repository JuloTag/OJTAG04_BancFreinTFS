// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP3428
// This code is designed to work with the MCP3428_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=MCP3428_I2CADC#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class MCP3428_4Channel
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
		byte[] data1 = new byte[2];
		device.read(0x00, data1, 0, 2);

		// Convert the data to 12-bits
		int raw_adc1 = (((data1[0] & 0x0F) * 256) + (data1[1] & 0xFF));
		if(raw_adc1 > 2047)
		{
			raw_adc1 -= 4095;
		}

		// Output data to screen
		System.out.printf("Digital value of Analog Input on Channel-1: %d %n", raw_adc1);

		// Select configuration register
		// Continuous conversion mode, Channel-2, 12-bit resolution
		device.write((byte)0x30);

		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data2 = new byte[2];
		device.read(0x00, data2, 0, 2);

		// Convert the data to 12-bits
		int raw_adc2 = (((data2[0] & 0x0F) * 256) + (data2[1] & 0xFF));
		if(raw_adc2 > 2047)
		{
			raw_adc2 -= 4095;
		}

		// Output data to screen
		System.out.printf("Digital value of Analog Input on Channel-2: %d %n", raw_adc2);

		// Select configuration register
		// Continuous conversion mode, Channel-3, 12-bit resolution
		device.write((byte)0x50);

		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data3 = new byte[2];
		device.read(0x00, data3, 0, 2);

		// Convert the data to 12-bits
		int raw_adc3 = (((data3[0] & 0x0F) * 256) + (data3[1] & 0xFF));
		if(raw_adc3 > 2047)
		{
			raw_adc3 -= 4095;
		}

		// Output data to screen
		System.out.printf("Digital value of Analog Input on Channel-3: %d %n", raw_adc3);

		// Select configuration register
		// Continuous conversion mode, Channel-4, 12-bit resolution
		device.write((byte)0x70);

		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data4 = new byte[2];
		device.read(0x00, data4, 0, 2);

		// Convert the data to 12-bits
		int raw_adc4 = (((data4[0] & 0x0F) * 256) + (data4[1] & 0xFF));
		if(raw_adc4 > 2047)
		{
			raw_adc4 -= 4095;
		}

		// Output data to screen
		System.out.printf("Digital value of Analog Input on Channel-4: %d %n", raw_adc4);
	}
}