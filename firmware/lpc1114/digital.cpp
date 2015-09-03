/*---------------------------------------------------------------------------*
* LPC1114 implementation of digital IO
*----------------------------------------------------------------------------*
* 02-Sep-2015 ShaneG
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

/** Initialise a pin for digital input or output
 *
 * @param pin the digital pin to configure
 * @param dir the direction of the pin (input or output)
 * @param pullup enable or disable the pull up resistor on the pin
 *
 * @return true if the pin was configured as requested, false if the pin is
 *         not available or could not be configured.
 */
bool digitalInit(DIGITAL_PIN pin, IODIR dir, bool pullup) {
  return false;
  }

/** Read the current value of the digital pin
 *
 * @param pin the digital pin to read
 *
 * @return true if the pin is currently 'high', false if 'low'
 */
bool digitalRead(DIGITAL_PIN pin) {
  return false;
  }

/** Write a value to the digital pin
 *
 * @param pin the digital pin to write
 * @param value the new value of the pin - true for 'high', false for 'low'
 */
void digitalWrite(DIGITAL_PIN pin, bool value) {
  }

