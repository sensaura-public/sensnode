/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Windows API Serial Interface
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Implements the Flasher interface for serial ports on Windows.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gruf.h>

/** Attach to a flasher on the specified port.
 *
 * This function is used to create a flasher instance attached to the named
 * port. The port name is platform independent.
 *
 * @param cszPort name of the port to attach to.
 *
 * @return a Flasher instance or NULL if an error occured.
 */
Flasher *attachFlasher(const char *cszPort) {
  return NULL;
  }

