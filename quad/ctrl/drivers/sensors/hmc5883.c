/*
  June 2012

  BaseFlightPlus Rev -

  An Open Source STM32 Based Multicopter

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick

  Designed to run on Naze32 Flight Control Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "hmc5883.h"
#include "bsp.h"

///////////////////////////////////////////////////////////////////////////////

#define HMC5883_ADDRESS 0x1E

#define HMC5883_CONFIG_REG_A    0x00
#define HMC5883_CONFIG_REG_B    0x01
#define HMC5883_MODE_REG        0x02
#define HMC5883_DATA_X_MSB_REG  0x03
#define HMC5883_STATUS_REG      0x09

///////////////////////////////////////////////////////////////////////////////

//#define SENSOR_CONFIG 0x18  // 1 Sample average, 75 Hz
//#define SENSOR_CONFIG 0x38  // 2 Sample average, 75 Hz
//#define SENSOR_CONFIG 0x58  // 4 Sample average, 75 Hz
#define SENSOR_CONFIG 0x78      // 8 Sample average, 75 Hz

#define NORMAL_MEASUREMENT_CONFIGURATION 0x00
#define POSITIVE_BIAS_CONFIGURATION      0x01

///////////////////////////////////////////////////////////////////////////////

//#define SENSOR_GAIN 0x00  // +/- 0.88 Ga
#define SENSOR_GAIN 0x20        // +/- 1.3  Ga (default)
//#define SENSOR_GAIN 0x40  // +/- 1.9  Ga
//#define SENSOR_GAIN 0x60  // +/- 2.5  Ga
//#define SENSOR_GAIN 0x80  // +/- 4.0  Ga
//#define SENSOR_GAIN 0xA0  // +/- 4.7  Ga
//#define SENSOR_GAIN 0xC0  // +/- 5.6  Ga
//#define SENSOR_GAIN 0xE0  // +/- 8.1  Ga

///////////////////////////////////////////////////////////////////////////////

#define OP_MODE_CONTINUOUS 0x00 // Continuous conversion
#define OP_MODE_SINGLE     0x01 // Single converison

#define STATUS_RDY         0x01 // Data Ready

///////////////////////////////////////////////////////////////////////////////
#define swap_(x,y)  do{uint8_t t =x; x = y; y = t;}while(0)

///////////////////////////////////////////////////////////////////////////////
// Read Magnetometer
///////////////////////////////////////////////////////////////////////////////

void HMC5883_mag_read(int16_t* data)
{
    uint8_t* buf = (uint8_t*) data;
    HMC5883_Read_Buffer(HMC5883_ADDRESS, HMC5883_DATA_X_MSB_REG, buf, 6);
    // setting is MSB, need to swap bytes order
    swap_(buf[0],buf[1]);
    swap_(buf[2],buf[3]);
    swap_(buf[4],buf[5]);
}

///////////////////////////////////////////////////////////////////////////////
// Initialize Magnetometer
///////////////////////////////////////////////////////////////////////////////

void HMC5883_mag_init(void)
{
    ///*
       uint8_t I2C2_Buffer_Rx[4] = { 0 };
       int16_t mag[3];
       HMC5883_INIT();

       HMC5883_Write_Byte( HMC5883_ADDRESS, HMC5883_CONFIG_REG_B, SENSOR_GAIN );
       delay_ms(20);

       HMC5883_Write_Byte( HMC5883_ADDRESS, HMC5883_CONFIG_REG_A, SENSOR_CONFIG | POSITIVE_BIAS_CONFIGURATION );
       delay_ms(20);

       HMC5883_Write_Byte( HMC5883_ADDRESS, HMC5883_MODE_REG, OP_MODE_SINGLE );

       //while ( (I2C2_Buffer_Rx[0] & STATUS_RDY) == 0x00 )
       //i2cRead ( HMC5883_ADDRESS, HMC5883_STATUS_REG, 1, I2C2_Buffer_Rx );

       HMC5883_mag_read(mag);
     //*/
    //magScaleFactor[XAXIS] = 1.0f;       // (1.16F * 1090.0F) / (float)rawMag[XAXIS].value;
    //magScaleFactor[YAXIS] = 1.0f;       // (1.16F * 1090.0F) / (float)rawMag[YAXIS].value;
    //magScaleFactor[ZAXIS] = 1.0f;       // (1.08F * 1090.0F) / (float)rawMag[ZAXIS].value;

    delay_ms(20);
    HMC5883_Read_Buffer ( HMC5883_ADDRESS, HMC5883_CONFIG_REG_B, I2C2_Buffer_Rx, 1);
    delay_ms(20);
    HMC5883_Write_Byte( HMC5883_ADDRESS, HMC5883_CONFIG_REG_B, 0xe0 );
    delay_ms(20);
    HMC5883_Read_Buffer ( HMC5883_ADDRESS, HMC5883_CONFIG_REG_B, I2C2_Buffer_Rx, 1);
    delay_ms(20);
    HMC5883_Write_Byte( HMC5883_ADDRESS, HMC5883_CONFIG_REG_B, SENSOR_GAIN );
    delay_ms(20);
    HMC5883_Read_Buffer ( HMC5883_ADDRESS, HMC5883_CONFIG_REG_B, I2C2_Buffer_Rx, 1);
    delay_ms(20);
    HMC5883_Read_Buffer ( HMC5883_ADDRESS, 10, I2C2_Buffer_Rx, 3);

    HMC5883_Write_Byte(HMC5883_ADDRESS, HMC5883_CONFIG_REG_A, SENSOR_CONFIG | NORMAL_MEASUREMENT_CONFIGURATION);
    delay_ms(20);

    HMC5883_Write_Byte(HMC5883_ADDRESS, HMC5883_MODE_REG, OP_MODE_CONTINUOUS);
    delay_ms(20);

    HMC5883_mag_read(mag);

    delay_ms(20);
}

///////////////////////////////////////////////////////////////////////////////
