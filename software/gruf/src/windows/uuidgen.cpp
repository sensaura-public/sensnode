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
#include <Winsock2.h>
#include <windows.h>
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
  GUID guid;
  HRESULT result = CoCreateGuid(&guid);
  if(result != S_OK)
    return false;
  // Windows GUID values are stored in native endian format, convert to
  // network byte order first
  guid.Data1 = htonl(guid.Data1);
  guid.Data2 = htons(guid.Data2);
  guid.Data3 = htons(guid.Data3);
  memcpy(uuid, &guid, UUID_LENGTH);
  return true;
  }

