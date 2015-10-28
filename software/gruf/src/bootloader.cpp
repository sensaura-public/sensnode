/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Device Information Data
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Maintains the table of known devices and their associated information.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <gruf.h>

// Maximum length of a device name
#define MAX_DEVICE_NAME 64

/** Bootloader factory function signature
 *
 * Bootloader implementations must provide functions that match this signature
 * to create instances of the Bootloader interface.
 *
 * @param cszDevice the name of the target device
 * @param id1 the first part of the expected device ID
 * @param id2 the second part of the expected device ID
 *
 * @return a Bootloader instance or NULL on error.
 */
typedef Bootloader *(*PFN_BOOTLOADER_FACTORY)(const char *cszDevice, uint32_t id1, uint32_t id2);

/** Information required to flash a device
 */
struct DeviceInfo {
  const char            *m_cszName;    //! Name of the device
  PFN_BOOTLOADER_FACTORY m_pfnFactory; //!< The bootloader function to call
  uint32_t               m_id1;        //!< First part of device ID code
  uint32_t               m_id2;        //!< Second part of device ID code
  };

//--- TODO: Bootloader implementation functions

/** The master device table
 */
static DeviceInfo g_devices[] = {
  // Name  FactoryFN  ID1 ID2
  { NULL,  NULL,      0,  0    },
  };

/** Get the bootloader implementation for the named device
 *
 * This function creates an returns an appropriate Bootloader implementation
 * for the named device.
 *
 * @param cszDevice the device name.
 *
 * @return a bootloader instance that can be used to program device or NULL
 *         if the device is not recognised.
 */
Bootloader *getBootloader(const char *cszDevice) {
  // Check parameters
  if(cszDevice==NULL)
    return false;
  // Find the device
  for(int i=0; g_devices[i].m_cszName!=NULL; i++) {
    if(strnicmp(cszDevice, g_devices[i].m_cszName, MAX_DEVICE_NAME)==0)
      return (g_devices[i].m_pfnFactory)(g_devices[i].m_cszName, g_devices[i].m_id1, g_devices[i].m_id2);
    }
  // No such device
  return NULL;
  }

