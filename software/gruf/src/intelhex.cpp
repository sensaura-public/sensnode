/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Intel Hex File Loader
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Implementation of the Firmware interface for Intel Hex files.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gruf.h>

/** Load firmware from a Intel Hex file.
 *
 * This function creates a new Firmware instance and populates it from the
 * named file. The file is expected to be in Intel Hex format.
 *
 * @param cszFilename the name of the hex file containing the firmware data.
 *
 * @return a pointer to a Firmware instance containing the data or NULL if an
 *         error occurs.
 */
Firmware *loadFirmware(const char *cszFilename) {
  return NULL;
  }

