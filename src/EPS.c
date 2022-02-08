/*
 * EPS.c
 *
 *  Created on: Nov 22, 2020
 *      Author: pc
 */
#include "utils.h"
#include <stdio.h>
#include "EPS.h"
#include "errors.h"
#include <wiringPiI2C.h>
//#include "../HW/ina219.h"
#define DEVICE_ID 0x40
#define SIGNATURE 8242
#define REG_DATA_ch1  0x01 //ch 1 shunt




ISIS_EPS_t _isis_eps;
Boolean _flagEpsInit = FALSE;
Boolean _flagSolarPanelInit = FALSE;



int ISIS_EPS_Init( ISIS_EPS_t* isis_eps, uint8_t isis_epsCount ){
if (_flagEpsInit == TRUE){
	return E_IS_INITIALIZED;
}
	_flagEpsInit = TRUE;
	_isis_eps.i2cAddr = isis_eps->i2cAddr;
	return E_NO_SS_ERR;
}


int IsisSolarPanelv2_initialize( SPIslave slave ){
	if (_flagSolarPanelInit == TRUE){
		return E_IS_INITIALIZED;
	}

	if (slave != slave0_spi){
		return E_INDEX_ERROR;
	}

	 _flagSolarPanelInit = TRUE;

	 return IsisSolarPanelv2_getState();
}
int IsisSolarPanelv2_Dinitialize(){
	 _flagSolarPanelInit = FALSE;
	 return E_NO_SS_ERR;

}

/* TODO: need to complete the function| AWAKE/SLEEP
 *
 */
IsisSolarPanelv2_State_t IsisSolarPanelv2_getState(){
	if (_flagSolarPanelInit == FALSE){
		return ISIS_SOLAR_PANEL_STATE_NOINIT;
	}
	return ISIS_SOLAR_PANEL_STATE_SLEEP;
}

int isis_eps__gethousekeepingengincdb__tm( uint8_t index, isis_eps__gethousekeepingengincdb__from_t *response ){
<<<<<<< Updated upstream
//	response->fields.temp = get_eps_temp();
//	printf ("%d",response->fields.temp);
//	get_VIP(response->fields.)
=======
	response->fields.temp = get_eps_temp();
	printf ("%d",response->fields.temp);
	get_VIP(response->fields.dist_input,0x40);
	get_VIP(response->fields.batt_input, 0x40);
>>>>>>> Stashed changes
}

int get_eps_temp (){
//	FILE *temperatureFile;
//	int T;
//	temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
//	if (temperatureFile == NULL)
//		return E_INPUT_POINTER_NULL;
//	fscanf (temperatureFile, "%d", &T);
//	fclose (temperatureFile);
//	return T;
}

void get_VIP(isis_eps__vipdeng_t temp,int address){

//	float SHUNT_OHMS = 0.1;
//	float MAX_EXPECTED_AMPS = 3.2;
//
//	INA219_Init(SHUNT_OHMS, MAX_EXPECTED_AMPS, address); // defualt INA219 I2C address is 0x40
//	INA219_configure(RANGE_16V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT);
//	temp->fields.current=INA219_current();
//	temp->fields.power=INA219_power();
//	temp->fields.volt=INA219_voltage();


}
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
