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

class FirmwareImpl : public Firmware {
  public:
    /** Default constructor
     */
    FirmwareImpl() {
      }

    //-----------------------------------------------------------------------
    // Public API
    //-----------------------------------------------------------------------

    /** Get the first block in the firmware
     *
     * The Firmware structure maintains a list of blocks that need to be
     * written to the target systems flash memory. The list is held in ascending
     * order of address.
     *
     * @return a pointer to the first block of memory to be written or NULL if
     *         there is no data.
     */
    virtual Block *first() {
      return NULL;
      }

    /** Get the start address of the flash data to be written
     *
     * This is the equivalent of first()->m_base.
     *
     * @return the start address of the firmware data or INVALID_ADDRESS if no
     *         data is available.
     */
    virtual uint32_t baseAddress() {
      return INVALID_ADDRESS;
      }

    /** Get the last address referenced in the firmware
     *
     * @return the highest address containing data to be written or INVALID_ADDRESS
     *         if no data is available.
     */
    virtual uint32_t lastAddress() {
      return INVALID_ADDRESS;
      }

    /** Get the total size of the firmware
     *
     * This returns the total number of bytes in address space covered by the
     * firmware. This does not necessarily match the number of bytes that needs
     * to be written to the target.
     *
     * @return the total number of bytes covered by the firmware.
     */
    virtual uint32_t totalSize() {
      return 0;
      }

    /** Get the number of bytes that need to be written to the target flash.
     *
     * This method provides the total number of bytes that need to be written
     * which excludes any memory areas that have no data specified.
     *
     * @return the number of bytes to write to the target.
     */
    virtual uint32_t flashSize() {
      return 0;
      }

    /** Patch the firmware with a new ID code
     *
     * SensNode devices have two IDs associated with them - a TYPEID which is
     * used to determine the type of the sensor and may be shared across
     * multiple devices and a NODEID which must be unique for each device.
     * Rather than compile a new firmware image for every node this method
     * allows an embedded ID to be modified in place prior to flashing.
     *
     * @param id the type of ID to change
     * @param uuid the 16 byte UUID value to insert into the code.
     *
     * @return the address at which the ID was found or INVALID_ADDRESS if the
     *         location could not be determined.
     */
    virtual uint32_t patchID(ID id, const uint8_t *uuid) {
      return 0;
      }
  };

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
  // TODO: Make sure the file exists and we can read it
  FirmwareImpl *firmware = new FirmwareImpl();
  // TODO: Load file contents into Firmware instance
  // All done
  return firmware;
  }

