/*--------------------------------------------------------------------------*
* MCP23008 Driver Interface
*---------------------------------------------------------------------------*
* 08-Sep-2015 ShaneG
*
* Provides a Digital interface using the 8 bit Microchip IO expanders.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <drivers/mcp23008.h>

/** Constructor
 *
 * The constructor specifies the communication devices to use to talk to
 * the target chip. No significant initialisation is done.
 *
 * @param i2c the I2C interface to use to communicate with the chip
 * @param address the address of the target device.
 */
MCP23008::MCP23008(I2C *i2c, uint8_t address) {
  m_i2c = i2c;
  m_address = address;
  }

/** Initialise the digital pin interface
 *
 * Configure the interface prior to use. Note that the core implementations
 * are initialised at start up and do not require explicit initialisation by
 * the application.
 *
 * @return true if the initialise succeeded.
 */
bool MCP23008::init() {
  // TODO: Implement this
  return false;
  }

/** Determine the number of pins available
 *
 * @return the number of pins supported by the interface.
 */
int MCP23008::pins() {
  return 8;
  }

/** Initialise a pin for digital input or output
 *
 * @param pin the digital pin to configure
 * @param dir the direction of the pin (input or output)
 * @param pullup enable or disable the pull up resistor on the pin
 *
 * @return true if the pin was configured as requested, false if the pin is
 *         not available or could not be configured.
 */
bool MCP23008::init(int pin, IODIR dir, bool pullup) {
  // TODO: Implement this
  return false;
  }

/** Read the current value of the digital pin
 *
 * @param pin the digital pin to read
 *
 * @return true if the pin is currently 'high', false if 'low'
 */
bool MCP23008::read(int pin) {
  // TODO: Implement this
  return false;
  }

/** Write a value to the digital pin
 *
 * @param pin the digital pin to write
 * @param value the new value of the pin - true for 'high', false for 'low'
 */
void MCP23008::write(int pin, bool value) {
  // TODO: Implement this
  }

