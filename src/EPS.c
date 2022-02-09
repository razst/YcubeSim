#include <stdio.h>
#include "EPS.h"
#include "errors.h"
#include <wiringPiI2C.h>
//#include "../HW/ina219.h"

#define DEVICE_ID 0x40
#define SIGNATURE 8242
#define REG_DATA_ch1  0x01 //ch 1 shunt




ISIS_EPS_t _isis_eps;

