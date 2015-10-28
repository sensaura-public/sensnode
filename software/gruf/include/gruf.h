/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Common Definitions
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Provides common functions and structures used by the GRUF utility.
*---------------------------------------------------------------------------*/
#ifndef __GRUF_H
#define __GRUF_H

// Required definitions
#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
// Logging and error reporting
//---------------------------------------------------------------------------

/** The different verbosity levels for the application
 */
enum VERBOSITY {
  QUIET = 0,
  NORMAL,
  VERBOSE
  };

/** Set the application verbosity
 *
 * The verbosity level starts as NORMAL but can be changed by the command line
 * options.
 *
 * @param verbosity the required verbosity level
 */
void setVerbosity(VERBOSITY verbosity);

/** Emit a debugging message
 *
 * Debug messages are only displayed in verbose mode.
 *
 * @param cszFormat format string (as per 'printf()')
 */
void DLog(const char *cszFormat, ...);

/** Emit a informational message
 *
 * Informational messages are not displayed in quiet mode.
 *
 * @param cszFormat format string (as per 'printf()')
 */
void ILog(const char *cszFormat, ...);

/** Emit an error message
 *
 * Error messages are always displayed.
 *
 * @param cszFormat format string (as per 'printf()')
 */
void ELog(const char *cszFormat, ...);

//---------------------------------------------------------------------------
// UUID Manipulation
//---------------------------------------------------------------------------

// Length of a UUID in bytes
#define UUID_LENGTH 16

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
bool uuidParse(uint8_t *uuid, const char *cszUUID);

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
bool uuidCreate(uint8_t *uuid);

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
const char *uuidPrint(uint8_t *uuid);

//---------------------------------------------------------------------------
// The generic flasher interface
//---------------------------------------------------------------------------

/** Supported baudrates for the flasher interface
 */
typedef enum {
  B9600 = 0,
  B19200,
  B38400,
  B57600,
  B115200,
  } BAUDRATE;

/** Interface for the flasher tool
 *
 * This pure virtual class allows interaction with the flasher tool which
 * allows for a serial communications channel to the target device as well as
 * being able to remotely reset and enter programming mode.
 */
class Flasher {
  public:
    /** Open the flasher with the specified baud rate.
     *
     * When a Flasher instance is first created it is simply attached to a
     * local communications channel but not yet open. This method must be
     * called to open the connection and set the communications speed.
     *
     * @param baud the requested baud rate.
     *
     * @return true if the device was opened, false if an error occured.
     */
    virtual bool open(BAUDRATE baud) = 0;

    /** Close the device
     *
     * Close the connection. The device may be reopened with a different
     * baud rate if needed.
     */
    virtual void close() = 0;

    /** Trigger a processor reset
     *
     * This method forces a reset of the target processor.
     */
    virtual void reset() = 0;

    /** Enter programming mode
     *
     * Forces the target processor into programming mode. It will remain in
     * this state until the 'reset()' method is called to restore it to a
     * 'normal' state.
     */
    virtual void program() = 0;

    /** Write a sequence of bytes to the target processor.
     *
     * @param pData pointer to a buffer containing the data to be sent.
     * @param length the number of bytes to send
     *
     * @return the number of bytes sent or -1 if an error occured.
     */
    virtual int write(const uint8_t *pData, int length) = 0;

    /** Read a sequence of bytes from the target processor.
     *
     * @param pData pointer to a buffer to contain the data read.
     * @param length the number of bytes to read.
     *
     * @return the number of bytes read or -1 if an error occured. This may be
     *         less than the number of bytes requested.
     */
    virtual int read(uint8_t *pData, int length) = 0;
  };

/** Attach to a flasher on the specified port.
 *
 * This function is used to create a flasher instance attached to the named
 * port. The port name is platform independent.
 *
 * @param cszPort name of the port to attach to.
 *
 * @return a Flasher instance or NULL if an error occured.
 */
Flasher *attachFlasher(const char *cszPort);

//---------------------------------------------------------------------------
// Firmware image management
//---------------------------------------------------------------------------

//! Constant used for invalid address indications.
const uint32_t INVALID_ADDRESS = (uint32_t)-1L;

/** Represents a single firmware blob
 *
 * This class provides access to a raw firmware blob to be written to the
 * target device flash.
 */
class Firmware {
  public:
    /** The ID types that can be patched
     */
    enum ID {
      TYPEID,
      NODEID
      };

    /** Represents a single block of flash data
     *
     * Each instance of this structure represents a contiguous block of data
     * that needs to be written to the target flash. The blocks are maintained
     * in a list in ascending order of address.
     */
    struct Block {
      uint32_t  m_base; //!< Base address of this block
      uint32_t  m_size; //!< Size of the block (in bytes)
      uint8_t  *m_data; //!< Data for the block
      Block    *m_next; //!< Next block or NULL if end of firmware
      };

    /** Get the first block in the firmware
     *
     * The Firmware structure maintains a list of blocks that need to be
     * written to the target systems flash memory. The list is held in ascending
     * order of address.
     *
     * @return a pointer to the first block of memory to be written or NULL if
     *         there is no data.
     */
    virtual Block *first() = 0;

    /** Get the start address of the flash data to be written
     *
     * This is the equivalent of first()->m_base.
     *
     * @return the start address of the firmware data or INVALID_ADDRESS if no
     *         data is available.
     */
    virtual uint32_t baseAddress() = 0;

    /** Get the last address referenced in the firmware
     *
     * @return the highest address containing data to be written or INVALID_ADDRESS
     *         if no data is available.
     */
    virtual uint32_t lastAddress() = 0;

    /** Get the total size of the firmware
     *
     * This returns the total number of bytes in address space covered by the
     * firmware. This does not necessarily match the number of bytes that needs
     * to be written to the target.
     *
     * @return the total number of bytes covered by the firmware.
     */
    virtual uint32_t totalSize() = 0;

    /** Get the number of bytes that need to be written to the target flash.
     *
     * This method provides the total number of bytes that need to be written
     * which excludes any memory areas that have no data specified.
     *
     * @return the number of bytes to write to the target.
     */
    virtual uint32_t flashSize() = 0;

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
    virtual uint32_t patchID(ID id, const uint8_t *uuid);
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
Firmware *loadFirmware(const char *cszFilename);

//---------------------------------------------------------------------------
// Bootloader interface
//---------------------------------------------------------------------------

/** Provides access to a bootloader protocol
 */
class Bootloader {
  public:
    /** Attach the bootloader to the given flasher connection
     *
     * @param pFlasher the flasher to attach to.
     */
    virtual bool attach(Flasher *pFlasher) = 0;

    /** Detach the bootloader from a flasher.
     *
     */
    virtual void detach() = 0;

    /** Validate the firmware data
     *
     * This method ensures the firmware is suitable for the target device. It
     * checks the memory areas used and the total size.
     *
     * @return true if the firmware can be flashed, false if not.
     */
    virtual bool validate(Firmware *pFirmware) = 0;

    /** Program the device with the given firmware data
     *
     * This method programs the target flash memory with the data represented
     * by the firmware instance. The bootloader must be attached to a flasher
     * for this to work.
     *
     * @return true if the firmware was written, false on failure.
     */
    virtual bool program(Firmware *pFirmware) = 0;

    /** Verify the contents of the target flash memory
     *
     * This method compares the current contents of the targets flash memory
     * with the data contained in the Firmware instance. The bootloader must
     * be attached to a Flasher for this to work.
     *
     * @return true if the target flash contents match the firmware, false on
     *              error.
     */
    virtual bool verify(Firmware *pFirmware) = 0;

    /** Erase the contents of the target flash memory
     *
     * This method clears the entire flash memory on the target device. This
     * generally results in the memory being filled with 0xFF bytes.
     *
     * The bootloader must be attached to a Flasher for this to work.
     *
     * @return true on success, false if an error occurred.
     */
    virtual bool erase() = 0;

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
Bootloader *getBootloader(const char *cszDevice);

#endif

