/*
 * testIna219.c
 *
 *  Created on: 2 בפבר׳ 2022
 *      Author: User
 */
// libs needed
#include <unistd.h>
#include <stdio.h>
#include <wiringPiI2C.h>
// device constants
// exo decimali number for checking adrees port ina3221
#define DEVICE_ID 0x40
#define SIGNATURE 8242
#define REG_RESET  0x00
#define REG_DATA_ch1  0x01 //ch 1 shunt
#define REG_DATA_ch2  0x03 //ch 2 shunt
#define REG_DATA_ch3  0x05 //ch 3 shunt
// I plan to use it as lowside so voltage values are not o iterest yet.

unsigned int change_endian(unsigned int x)
{
    unsigned char *ptr = (unsigned char *)&x;
    return ( (ptr[0] << 8) | ptr[1]);
}

float shunt_to_Amp(int amp)
{
// sign change for negative value (bit 13 is sign)

        if (amp > 4096){
        amp=-(8192-amp);
        }
// shunt raw value to mv (163.8mV LSB (SD0):40μV) datasheet
        float amp1mv=(163.8/4096)*amp;
// for my shunt the producer does not recomend to go above 80A, IC is able to measure up to 108 A :)
// I have a 50A/75mv shunt so A on channel is:
        float Amp=amp1mv*50/75;
// if you do not plan to use external shunt you are limited to 1.6 A / channel
// default A without external shunt R on device is 0.1 ohm comment line above and uncomment next line:
//      float Amp=amp1mv*10
return Amp;
}

int main (int argc, char **argv)
{
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        printf ("Failed to init I2C communication.\n");
        return -1;
    }
        int check_vendor_id = wiringPiI2CReadReg16(fd,0xFF);
        if (check_vendor_id == SIGNATURE ){
         printf ("I2C communication successfully setup with INA3221 device at addess 0x%x.\n",DEVICE_ID);
        } else {
         printf ("Device at address 0x%x is not an INA3221 device; exiting\n",DEVICE_ID);
        return -1;
        }

    // Switch device to measurement mode (reset when connect,continous mode, max average) to modify this in next version
    wiringPiI2CWriteReg16(fd, REG_RESET, 0b1111111111111111);
    while (1) {

        int shunt1 = wiringPiI2CReadReg16(fd, REG_DATA_ch1);
        //change endian, strip last 3 bits provide raw value
        shunt1 = change_endian(shunt1)/8;
        float shunt1Amp=shunt_to_Amp(shunt1);
        int shunt2 = wiringPiI2CReadReg16(fd, REG_DATA_ch2);
        shunt2 = change_endian(shunt2)/8;
        float shunt2Amp=shunt_to_Amp(shunt2);
        int shunt3 = wiringPiI2CReadReg16(fd, REG_DATA_ch3);
        shunt3 = change_endian(shunt3)/8;
        float shunt3Amp=shunt_to_Amp(shunt3);
               printf ( "ch1 raw:%d ,ch1 A:%f , ch2 raw:%d, ch2 A:%f     ch3 raw:%d , ch3 A:%f \n", shunt1 , shunt1Amp , shunt2 ,shunt2Amp, shunt3, shunt3Amp);
        sleep(1);

    }
    return 0;
}



/*
 * INA219_standalone.c
 *
 *  Created on: 24 בנוב׳ 2021
 *      Author: User



#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>


int main(void) {
	int fd;
	int result;
	//unsigned char buffer[100];

	printf ("Starting ...\n");
	blink();

	fd = wiringPiI2CSetup(0x40);

	result = wiringPiI2CReadReg16(fd, 0x00);//0x02);
	printf("before configure - %d\n", result);
	configure(fd);
	result = wiringPiI2CReadReg16(fd, 0x00);//0x02);
	printf("after configure - %d\n", result);
	calibrate(fd, 0.1 , 0.2 , 32, 2);




	while(1){
		//result = wiringPiI2CReadReg16(fd, 0x04);//0x02);
		result = wiringPiI2CReadReg16(fd, 0x00);//0x02);



			if(result == -1)
				printf( "I2C read failed: %s\n", strerror( errno ) );
			else
				printf("value: %d \n", result);//*current_lsb<<endl;


	}

	return 0;
}
*/



