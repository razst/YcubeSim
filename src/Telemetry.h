/*
 * Telemetry.h
 *
 *  Created on: 6 ����� 2020
 *      Author: Alihai
 */

#ifndef TELEMETRY_H_
#define TELEMETRY_H_


/*
 * Desc: Use this function to initialize the file system. Call it once at start-up.
 * in:None
 * return: error code
 */
int fs_init();

/*
 * Desc: intitilize the Telemetry
 * in:
 * return: error code
 */
 int hcc_mem_init();

 /*
  * Desc: Use this function to create resources for the calling task in the file system and allocate a current working
	directory for that task.
  * in:
  * return: error code
 */
 int f_enterFS();


 /*
  * Desc: Use this function to initialize a volume. Call it with a pointer to the driver function that must be called to
	retrieve drive configuration information from the relevant driver.
  * in:  int drvnumber, F_DRIVERINIT driver_init, unsigned long driver_param
  * return: error code
  */

 int f_initvolume (int drvnumber, F_DRIVERINIT driver_init,  unsigned long driver_param );



#endif /* TELEMETRY_H_ */

