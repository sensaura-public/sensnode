/*---------------------------------------------------------------------------*
* SensNode - GPIO implementation for XMC1100
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Provides the GPIO interface functions for the XMC1100 based board.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

/** Pin capability flags
 */
typedef enum {
  CAN_INPUT    = 0x01, //!< Pin can be a digital input
  CAN_OUTPUT   = 0x02, //!< Pin can be a digital output
  CAN_ANALOG   = 0x04, //!< Pin can be an analog input
  CAN_WAKEUP   = 0x08, //!< Pin can trigger a wakeup
  CAN_PULLUP   = 0x10, //!< Pin can use an internal pull up
  CAN_PULLDOWN = 0x20, //!< Pin can use an internal pull down
  CAN_INTERNAL = 0x40, //!< Pin has an internal function (eg: I2C)
  } PINCAP_FLAG;

/** Information about each configurable pin
 */
typedef struct _PININFO {
  uint8_t m_capabilities : 8;  //!< What the pin is capable of
  uint8_t m_current      : 8;  //!< What the pin is configured for
  uint8_t m_port         : 4;  //!< Which port is it attached to
  uint8_t m_pin          : 4;  //!< Which pin on that port is it
  } PININFO;

/** Pin definition table
 *
 * This table maps pin IO ports and capabilities to it's current state. There
 * is one entry per pin (the pins defined in the PIN enum).
 */
static PININFO g_pininfo[] = {
  { CAN_INPUT|CAN_OUTPUT|CAN_INTERNAL, 0, 0, 7 }, // PIN0 (SDA)
  { CAN_INPUT|CAN_OUTPUT|CAN_INTERNAL, 0, 0, 8 }, // PIN1 (SCL)
  { CAN_INPUT|CAN_OUTPUT|CAN_ANALOG,   0, 0, 0 }, // PIN2
  { CAN_INPUT|CAN_OUTPUT|CAN_ANALOG,   0, 0, 0 }, // PIN3
  { CAN_INPUT|CAN_OUTPUT|CAN_ANALOG,   0, 0, 0 }, // PIN4
  //-- Pins used internally
  { CAN_INPUT,                         0, 0, 0 }, // PIN_ACTION
  { CAN_OUTPUT,                        0, 0, 0 }, // PIN_LATCH
  { CAN_OUTPUT,                        0, 0, 0 }, // PIN_INDICATOR
  { CAN_ANALOG,                        0, 0, 0 }, // PIN_BATTERY
  { CAN_OUTPUT,                        0, 0, 0 }, // PIN_CE
  { CAN_OUTPUT,                        0, 0, 0 }, // PIN_CSN
  { CAN_OUTPUT,                        0, 0, 0 }, // PIN_SCK
  { CAN_INPUT,                         0, 0, 0 }, // PIN_MISO
  { CAN_OUTPUT,                        0, 0, 0 }, // PIN_MOSI
  };

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
/* TODO: Revisit this
  if(pin>=PINMAX)
    return false;
  // Configure the pin
  uint8_t config = 0;
  switch(mode) {
    case ANALOG:
      if(!(g_pininfo[pin].m_capabilities&CAN_ANALOG))
        return false;
      if(flags!=0) // No flags allowed for analog pins
        return false;
      config = CAN_ANALOG;
      break;
    case DIGITAL_INPUT:
      if(!(g_pininfo[pin].m_capabilities&CAN_INPUT))
        return false;
      config = CAN_INPUT;
      break;
    case DIGITAL_OUTPUT:
      if(!(g_pininfo[pin].m_capabilities&CAN_OUTPUT))
        return false;
      break;
    case SPECIAL_FUNCTION:
      if(!(g_pininfo[pin].m_capabilities&CAN_INTERNAL))
        return false;
      break;
    default:
      return false;
    }
*/
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

