#include "utils.h"
#include <stdio.h>
#include "EPS.h"
#include "errors.h"
#include <wiringPiI2C.h>
#include "HW/ina219.h"

#define DEVICE_ID 0x40
#define SIGNATURE 8242
#define REG_RESET  0x00
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

IsisSolarPanelv2_State_t IsisSolarPanelv2_getState(){
	if (_flagSolarPanelInit == FALSE){
		return ISIS_SOLAR_PANEL_STATE_NOINIT;
	}
	return ISIS_SOLAR_PANEL_STATE_SLEEP;
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

int isis_eps__gethousekeepingengincdb__tm( uint8_t index, isis_eps__gethousekeepingengincdb__from_t *response ){
	response->fields.temp= (short) get_eps_temp();
	response->fields.temp = get_eps_temp();
	printf ("%d",response->fields.temp);
	//need to return something
	return 0;
}

double get_eps_temp (){
	FILE *temperatureFile;
	double T;
	temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
	if (temperatureFile == NULL){
		return E_INPUT_POINTER_NULL;
	}
	fscanf (temperatureFile, "%lf", &T);
	T /= 1000;
	printf ("The temperature is %6.3f C.\n", T);
	fclose (temperatureFile);
	return T;
}
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
         printf ("I2C communication successfully setup with INA3221 device at addess 0x%x.\n",DEVICE_ID);
        } else {
         printf ("Device at address 0x%x is not an INA3221 device; exiting\n",DEVICE_ID);
        return -1;
        }
        return 0;
        //to change
}

float shunt_to_Amp(int amp)
{
        if (amp > 4096){
        amp=-(8192-amp);
        }
        return 0;
        // to change, lines in function less
}

int getamp(){
	float shunt_to_Amp(int amp);
	int amp1 = 0;
return amp1;
}














