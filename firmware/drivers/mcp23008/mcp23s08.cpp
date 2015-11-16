/*--------------------------------------------------------------------------*
* MCP23S08 Driver Interface
*---------------------------------------------------------------------------*
* 08-Sep-2015 ShaneG
*
* Provides a Digital interface using the 8 bit Microchip IO expanders.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <drivers/MCP23S08.h>

/** Constructor
 *
 * The constructor specifies the communication devices to use to talk to
 * the target chip. No significant initialisation is done.
 *
 * @param select the pin to use to select the SPI device
 */
MCP23S08::MCP23S08(PIN select) {
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

/** Configure a GPIO pin
 *
 * @param pin the pin to configure
 * @param mode the requested mode for the pin
 * @param flags optional flags for the pin.
 *
 * @return true if the pin was configured as requested.
 */
bool MCP23S08::pinConfig(uint8_t pin, PIN_MODE mode, uint8_t flags) {
  // TODO: Implement this
  return false;
  }

/** Read the value of a digital pin.
 *
 * To use this function the pin must be configured as DIGITAL_INPUT. If the pin
 * was configured for a different mode the result will always be false.
 *
 * @param pin the pin to read
 *
 * @return the current state of the pin.
 */
bool MCP23S08::pinRead(uint8_t pin) {
  // TODO: Implement this
  return false
  }

/** Change the state of a digital pin.
 *
 * To use this function the pin must be configured as DIGITAL_OUTPUT. If the
 * pin was configured for a different mode the function will have no effect.
 *
 * @param pin the pin to change the state of
 * @param value the value to set the pin to (true = high, false = low)
 */
void MCP23S08::pinWrite(uint8_t pin, bool value) {
  // TODO: Implement this
  }

