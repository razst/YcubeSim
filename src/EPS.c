#include <stdio.h>
#include "EPS.h"
#include "errors.h"
#include <wiringPiI2C.h>
//#include "../HW/ina219.h"
#define DEVICE_ID 0x40
#define SIGNATURE 8242
#define REG_DATA_ch1  0x01 //ch 1 shunt




ISIS_EPS_t _isis_eps;

/*
int communication (int argc, char **argv)
{
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        printf ("Failed to init I2C communication.\n");
        return -1;
    }
        int check_vendor_id = wiringPiI2CReadReg16(fd,0xFF);
        if (check_vendor_id == SIGNATURE ){
         printf ("I2C communication successfully setup with INA3221 device at address 0x%x.\n",DEVICE_ID);
 		wiringPiI2CWriteReg16(fd, REG_RESET, 0b1111111111111111);
 		int shunt1 = wiringPiI2CReadReg16(fd, REG_DATA_ch1);
 		//change endian, strip last 3 bits provide raw value
 		shunt1 = change_endian(shunt1)/8;

        } else {
         printf ("Device at address 0x%x is not an INA3221 device; exiting\n",DEVICE_ID);
        return -1;
        }
}

float shunt_to_Amp(int amp){
	// sign change for negative value (bit 13 is sign)
	if (amp > 4096){
	amp=-(8192-amp);
}
	}

int get_amp (DEVICE_ID){
communication (int argc, char **argv){
	if (check_vendor_id == SIGNATURE ){
	 		wiringPiI2CWriteReg16(fd, REG_RESET, 0b1111111111111111);
	 		int shunt1 = wiringPiI2CReadReg16(fd, REG_DATA_ch1);
	 		//change endian, strip last 3 bits provide raw value
	 		shunt1 = change_endian(shunt1)/8;
}
float shunt1Amp=shunt_to_Amp(shunt1)
printf ( "ch1 raw:%d ,ch1 A:%f , ch2 raw:%d, ch2 A:%f     ch3 raw:%d , ch3 A:%f \n", shunt1 , shunt1Amp , shunt2 ,shunt2Amp, shunt3, shunt3Amp);
      sleep(1);
}

*/
