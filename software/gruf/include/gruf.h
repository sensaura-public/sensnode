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

#endif

