/*
 * Telemetry.h
 *
 *  Created on: 6 áãöî× 2020
 *      Author: Alihai
 */


#ifndef TELEMETRY_H_
#define TELEMETRY_H_
/* Driver definitions */
#include <stdio.h>

typedef int F_DRIVERINIT;
typedef FILE F_FILE;



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
  * Desc: Use this function to release the file system from the calling task.
  * in:
  * return: None
  */
 void f_releaseFS ();

 /*
  * Desc: Use this function to initialize a volume. Call it with a pointer to the driver function that must be called to
	retrieve drive configuration information from the relevant driver.
  * in:  int drvnumber, F_DRIVERINIT driver_init, unsigned long driver_param
  * return: error code, see mkdir, chdir error codes
  */

int f_initvolume (int drvnumber, F_DRIVERINIT driver_init,  unsigned long driver_param );


 /*
  * Desc: Use this function to open a file.
  * in:const char * filename,const char * mode
  * return: F_FILE * Pointer to the associated opened file handle, or zero if it could not be opened
  */

 F_FILE * f_open (const char * filename,const char * mode );

 /*
   * Desc: Use this function to write data into a file at the current position
   * in:buf: Pointer to data to be written.
		size: Size of items to be written.
        size_st: Number of items to be written.
        filehandle: Handle of target file.
   *
   * return: number: Number of items written.
			 Else: See Error Codes.
   */
 long f_write ( const void * buf, long size,long size_st, F_FILE * filehandle );


 /*
   * Desc: Use this function to close a previously opened file.
   * in: filehandle: Handle of target file
   * return: Error Code.
   */


 int f_close ( F_FILE * filehandle );


 /*
    * Desc: Use this function to flush an opened file to a storage medium.
    * in: filehandle: Handle of target file.
    * return: Error Code.
    *
    */

 int f_flush ( F_FILE * filehandle );

 /*
     * Desc:Use this function to read bytes from the current position in the target file. The file must be opened with “r”, "r+", "w+" or "a+".
     * in:buf Buffer to store data in.
		size: Size of items to be read.
		size_st: Number of items to be read.
		filehandle: Handle of target file.
     * return:number Number of items read. Else See Error Codes.
     */

 long f_read ( void * buf, long size, long size_st, F_FILE * filehandle );


 /*
      * Desc:
      * in:
      * return:
      */



 #endif /* TELEMETRY_H_ */

