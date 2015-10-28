/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - UUID Generation for Windows
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Implements the Windows version of the UUID generation utility.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gruf.h>

/** Create a new UUID
 *
 * This is a generic wrapper to create a new UUID using the underlying operating
 * system implementation.
 *
 * @param uuid pointer to the buffer to contain the generated UUID. This buffer
 *             must be at least 16 bytes in length.
 *
 * @return true if the UUID was created, false if not.
 */
bool uuidCreate(uint8_t *uuid) {
  // TODO: Pretend we did
  return true;
  }

