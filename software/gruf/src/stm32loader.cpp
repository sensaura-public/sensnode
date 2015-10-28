/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - STM32 Bootloader
*----------------------------------------------------------------------------*
* 28-Oct-2015 ShaneG
*
* Implements the STM32 bootloader protocol.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <gruf.h>
#include "bootloader.h"

class BootloaderSTM32 : public AbstractBootloader {
  public:
    /** Constructor
     */
    BootloaderSTM32(const char *cszName, uint32_t id1, uint32_t id2) : AbstractBootloader(cszName, id1, id2) {
      // Nothing to do
      }

    /** Validate the firmware data
     *
     * This method ensures the firmware is suitable for the target device. It
     * checks the memory areas used and the total size.
     *
     * @return true if the firmware can be flashed, false if not.
     */
    virtual bool validate(Firmware *pFirmware) {
      ELog("Operation not yet implemented.");
      return false;
      }

    /** Program the device with the given firmware data
     *
     * This method programs the target flash memory with the data represented
     * by the firmware instance. The bootloader must be attached to a flasher
     * for this to work.
     *
     * @return true if the firmware was written, false on failure.
     */
    virtual bool program(Firmware *pFirmware) {
      ELog("Operation not yet implemented.");
      return false;
      }

    /** Verify the contents of the target flash memory
     *
     * This method compares the current contents of the targets flash memory
     * with the data contained in the Firmware instance. The bootloader must
     * be attached to a Flasher for this to work.
     *
     * @return true if the target flash contents match the firmware, false on
     *              error.
     */
    virtual bool verify(Firmware *pFirmware) {
      ELog("Operation not yet implemented.");
      return false;
      }

    /** Erase the contents of the target flash memory
     *
     * This method clears the entire flash memory on the target device. This
     * generally results in the memory being filled with 0xFF bytes.
     *
     * The bootloader must be attached to a Flasher for this to work.
     *
     * @return true on success, false if an error occurred.
     */
    virtual bool erase() {
      ELog("Operation not yet implemented.");
      return false;
      }
  };

/** Factory function to create the loader
 *
 * @param cszDevice the name of the target device
 * @param id1 the first part of the expected device ID
 * @param id2 the second part of the expected device ID
 *
 * @return a Bootloader instance or NULL on error.
 */
Bootloader *BootloaderSTM32Factory(const char *cszDevice, uint32_t id1, uint32_t id2) {
  return new BootloaderSTM32(cszDevice, id1, id2);
  }
