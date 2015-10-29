/*---------------------------------------------------------------------------*
* SensNode - GPIO implementation for XMC1100
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Provides the GPIO interface functions for the XMC1100 based board.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

//----------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------

/** Configure a GPIO pin
 *
 * @param pin the pin to configure
 * @param mode the requested mode for the pin
 * @param flags optional flags for the pin.
 *
 * @return true if the pin was configured as requested.
 */
bool pinConfig(PIN pin, PIN_MODE mode, uint8_t flags) {
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
bool pinRead(PIN pin) {
  // TODO: Implement this
  return false;
  }

/** Change the state of a digital pin.
 *
 * To use this function the pin must be configured as DIGITAL_OUTPUT. If the
 * pin was configured for a different mode the function will have no effect.
 *
 * @param pin the pin to change the state of
 * @param value the value to set the pin to (true = high, false = low)
 */
void pinWrite(PIN pin, bool value) {
  // TODO: Implement this
  }

/** Sample the value of a analog input
 *
 * To use this function the pin must be configured as ANALOG. If the pin was
 * configured for a different mode the function will always return 0.
 *
 * The value returned by this function is always scaled to a full 16 bit value
 * regardless of the resolution of the underlying ADC.
 *
 * The function allows the caller to sample and discard a number of samples
 * before reading and to take a group of samples and return the average. This
 * can improve the accuracy of the final result.
 *
 * @param pin the pin to sample the input from.
 * @param average the number of samples to average to get the final result.
 * @param skip the number of samples to skip before averaging.
 *
 * @return the sample read from the pin. This will be shifted left if needed
 *         to fully occupy a 16 bit value.
 */
uint16_t pinSample(PIN pin, int average, int skip) {
  // TODO: Implement this
  return 0;
  }

