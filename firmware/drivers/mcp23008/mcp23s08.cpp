/*--------------------------------------------------------------------------*
* MCP23S08 Driver Interface
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
 * @param spi the SPI interface used to communicate with the device
 * @param digital the Digital interface used to control the select pin
 * @param select the pin number to use for device selection
 */
MCP23S08::MCP23S08(SPI *spi, Digital *digital, int select) {
  m_spi = spi;
  m_digital = digital;
  m_select = select;
  }

/** Initialise the digital pin interface
 *
 * Configure the interface prior to use. Note that the core implementations
 * are initialised at start up and do not require explicit initialisation by
 * the application.
 *
 * @return true if the initialise succeeded.
 */
bool MCP23S08::init() {
  // TODO: Implement this
  return false;
  }

/** Determine the number of pins available
 *
 * @return the number of pins supported by the interface.
 */
int MCP23S08::pins() {
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
bool MCP23S08::init(int pin, IODIR dir, bool pullup) {
  // TODO: Implement this
  return false;
  }

/** Read the current value of the digital pin
 *
 * @param pin the digital pin to read
 *
 * @return true if the pin is currently 'high', false if 'low'
 */
bool MCP23S08::read(int pin) {
  // TODO: Implement this
  return false;
  }

/** Write a value to the digital pin
 *
 * @param pin the digital pin to write
 * @param value the new value of the pin - true for 'high', false for 'low'
 */
void MCP23S08::write(int pin, bool value) {
  // TODO: Implement this
  }

