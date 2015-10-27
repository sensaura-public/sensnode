/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - UUID Utilities
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Implements some platform independent UUID utility functions.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gruf.h>

/** Parse a UUID from a string representation
 *
 * This function converts an ASCII string representation of a UUID (in the
 * form 1b4e28ba-2fa1-11d2-883f-b9a761bde3fb) to a 16 byte array.
 *
 * @param uuid pointer to the buffer to contain the parsed UUID. This buffer
 *             must be at least 16 bytes in length.
 * @param cszUUID pointer to a string representation of the UUID.
 *
 * @return true if the UUID was parsed correctly, false if not. If parsing
 *              failed the buffer may still have been modified.
 */
bool uuidParse(uint8_t *uuid, const char *cszUUID) {
  return false;
  }

/** Convert the UUID into a printable format.
 *
 * This function uses an internal static buffer to hold the generated UUID
 * string. It must be used or copied prior to future calls to the method to
 * avoid being overwritten.
 *
 * @param uuid pointer to the buffer containing the UUID. This buffer must be
 *             at least 16 bytes in length.
 *
 * @return a pointer to a NUL terminated string containing a printable version
 *         of the UUID. Will return NULL on error.
 */
const char *uuidPrint(uint8_t *uuid) {
  return NULL;
  }


