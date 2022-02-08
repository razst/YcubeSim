/*
 * testEPS.c
 *
 *  Created on: 2 áôáø× 2021
 *      Author: User
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "../EPS.h"
#include "../EPS.c"
#include "../HW/ina219.h"
#include "testBasic.h"
#include "../errors.h"

void testISIS_EPS_Init(){
	ISIS_EPS_t i;
	i.i2cAddr = "t";
	uint8_t isis_epsCount = "t";
	int err = ISIS_EPS_Init(&i, isis_epsCount);
	ASSERT_INT(err,E_NO_SS_ERR);

	err = ISIS_EPS_Init(&i, isis_epsCount);
	ASSERT_INT(err,E_IS_INITIALIZED);

}
void testIsisSolarPanelv2_initialize(){
	int err = IsisSolarPanelv2_initialize(8);
	ASSERT_INT(err,E_INDEX_ERROR);

	err = IsisSolarPanelv2_initialize(0);
	ASSERT_INT(err,ISIS_SOLAR_PANEL_STATE_SLEEP);

	err = IsisSolarPanelv2_initialize(0);
	ASSERT_INT(err,E_IS_INITIALIZED);

}
void testIsisSolarPanelv2_getState(){
	IsisSolarPanelv2_Dinitialize();
	int err = IsisSolarPanelv2_getState();
	ASSERT_INT (err,ISIS_SOLAR_PANEL_STATE_NOINIT);

	IsisSolarPanelv2_initialize(0);
	err = IsisSolarPanelv2_getState();
	ASSERT_INT (err, ISIS_SOLAR_PANEL_STATE_SLEEP);

}
void testIsisSolarPanelv2_Dinitialize(){
	int err = IsisSolarPanelv2_Dinitialize();
	ASSERT_INT(err,E_NO_SS_ERR);
}

void testGet_eps_temp (){
	int err = get_eps_temp ();
	for (int i = 0; i<100000000; i++);

	int err2 = get_eps_temp ();
	ASSERT_TRUE(err2>err);
	printf ("The temperature is %d C,temerture 2 is %d C.\n", err,err2);

}

// TODO: just a sample code - change to real test !!
void testINA219(){
	printf("Start 1\n");

	float SHUNT_OHMS = 0.1;
	float MAX_EXPECTED_AMPS = 3.2;

	INA219_Init(SHUNT_OHMS, MAX_EXPECTED_AMPS, 0x41); // defualt INA219 I2C address is 0x40
	INA219_configure(RANGE_16V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT);

	printf("time_s,bus_voltage_V,supply_voltage_V,shunt_voltage_mV,current_mA,power_mW\n");

	int c = 0;
	while(c < 5)
	{
		printf( "%d,%f,%f,%f,%f,%f\n", c, INA219_voltage(),INA219_supply_voltage(),INA219_shunt_voltage(),INA219_current(),INA219_power());
		c++;
		usleep(1000000); // 1s
	}
}
get_amp (DEVICE_ID);

