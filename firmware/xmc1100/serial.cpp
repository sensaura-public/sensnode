/*---------------------------------------------------------------------------*
* SensNode - Serial port implementation for XMC1100
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Provides the serial port interface functions for the XMC1100 based board.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

/** Initialise the serial port
 *
 * The serial port is always operated in 8 bit mode with a single stop bit
 * (8N1). The core initialisation will set the initial baudrate to 57600 but
 * user code may reconfigure the port to a different baud rate if required.
 *
 * @param rate the requested baud rate
 */
void serialInit(BAUDRATE rate) {
  // TODO: Implement this
  }

/** Write a single character to the serial port
 *
 * @param ch the character to write
 */
void serialWrite(uint8_t ch) {
  // TODO: Implement this
  }

/** Determines if data is available to be read
 *
 * @return the number of bytes available to read immediately.
 */
bool serialAvailable() {
  // TODO: Implement this
  return false;
  }

/** Read a single byte from the serial port
 *
 * If no data is available this function will block until the next character
 * is received. Use 'serialAvailable()' to determine if data can be read
 * without blocking.
 *
 * @return the value of the byte read
 */
int serialRead() {
  return -1;
  }

