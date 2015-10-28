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
#include "bootloader.h"

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

//--- Bootloader implementation functions
extern Bootloader *BootloaderSTM32Factory(const char *cszDevice, uint32_t id1, uint32_t id2);

/** The master device table
 */
static DeviceInfo g_devices[] = {
  // Name         FactoryFN               ID1         ID2
  { "stm32f030",  BootloaderSTM32Factory, 0x00000000, 0x00000000 },
  { "stm32f070",  BootloaderSTM32Factory, 0x00000000, 0x00000000 },
  // End of records
  { NULL,         NULL,                    0,          0          },
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

/** Display a list of all supported devices
 */
void listDevices() {
  ILog("Supported devices:");
  for(int i=0; g_devices[i].m_cszName!=NULL; i++)
    ILog("\t%s", g_devices[i].m_cszName);
  }

/** Constructor
 *
 * Stashes away the device specific information.
 */
AbstractBootloader::AbstractBootloader(const char *cszName, uint32_t id1, uint32_t id2) {
  m_cszName = cszName;
  m_id1 = id1;
  m_id2 = id2;
  }

/** Attach the bootloader to the given flasher connection
 *
 * @param pFlasher the flasher to attach to.
 */
bool AbstractBootloader::attach(Flasher *pFlasher) {
  // Detach any existing flasher
  detach();
  // Check parameters
  if(pFlasher==NULL)
    return false;
  // Store a reference to the flasher and enter programming mode
  m_flasher = pFlasher;
  m_flasher->program();
  // All done
  return true;
  }

/** Detach the bootloader from a flasher.
 */
void AbstractBootloader::detach() {
  if(m_flasher==NULL)
    return; // Nothing to do
  // Reset the device on disconnect
  m_flasher->reset();
  m_flasher = NULL;
  }

/** Default destructor
 */
AbstractBootloader::~AbstractBootloader() {
  detach();
  }

