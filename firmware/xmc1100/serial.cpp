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

/** Get the number of bytes available in the input buffer.
 *
 * This function determines how much data is available to read from the serial
 * port.
 *
 * @return the number of bytes available to read immediately.
 */
int serialAvailable() {
  // TODO: Implement this
  return 0;
  }

/** Read a single byte from the serial port
 *
 * This function is non-blocking, if no data is available to read the function
 * will return a value < 0.
 *
 * @return the value of the byte read or a value < 0 if no data is available.
 */
int serialRead() {
  // TODO: Implement this
  return -1;
  }

