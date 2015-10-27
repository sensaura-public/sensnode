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

//--- TODO: Bootloader implementation functions

// Maximum length of a device name
#define MAX_DEVICE_NAME 64

/** Map device name to device information
 */
struct DeviceInfoDetail {
  const char *m_cszName; //! Name of the device
  DeviceInfo  m_info;    //! Information about the device
  };

/** The master device table
 */
static DeviceInfoDetail g_devices[] = {
  { NULL, { NULL, 0, 0, 0, 0 } },
  };

/** Get the device information structure for the named device
 *
 * Populates a DeviceInfo structure with details about the named device. The
 * device name is specified on the command line and is matched to device
 * identification information and a bootloader protocol implementation.
 *
 * @param cszDevice the name of the device to get info about
 * @param pDeviceInfo pointer to a DeviceInfo structure to fill
 *
 * @return true if the device is known and the information provided, false if
 *              the device is not supported.
 */
bool getDeviceInfo(const char *cszDevice, DeviceInfo *pDeviceInfo) {
  // Check parameters
  if((cszDevice==NULL)||(pDeviceInfo==NULL))
    return false;
  // Find the device
  for(int i=0; g_devices[i].m_cszName!=NULL; i++) {
    if(strnicmp(cszDevice, g_devices[i].m_cszName, MAX_DEVICE_NAME)==0) {
      memcpy(pDeviceInfo, &g_devices[i].m_info, sizeof(DeviceInfo));
      return true;
      }
    }
  // No such device
  return false;
  }

