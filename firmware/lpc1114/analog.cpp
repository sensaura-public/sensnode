/*---------------------------------------------------------------------------*
* LPC1114 implementation of analog IO
*----------------------------------------------------------------------------*
* 02-Sep-2015 ShaneG
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>
#include "common.h"

/** Assign ports and pin numbers to all defined pins
 */
static const PINDEF g_pins[] = {
  { m_port: 1, m_pin: 3,  m_func: 0x02, m_iocon: 0x90 }, // PIN_A0
  { m_port: 1, m_pin: 4,  m_func: 0x01, m_iocon: 0x94 }, // PIN_A1
  { m_port: 0, m_pin: 11, m_func: 0x02, m_iocon: 0x74 }, // PIN_VBAT
  };

/** Determine if a pin is valid
 */
static bool isValidPin(int pin) {
  if((pin<PIN_A0)||(pin>PIN_VBAT))
    return false;
  return g_pins[pin].m_pin != 15;
  }

class LPC_Analog : public Analog {
  public:
    /** Default constructor
     */
    LPC_Analog() {
      // Nothing to do
      }

    /** Initialise the analog interface
     *
     * This method should be called first to do any initialisation required for
     * the interface. Note that the primary analog interface is initialised at
     * startup, the application does not need to initialise it directly.
     *
     * @return true if the initialisation was successful.
     */
    virtual bool init() {
      return true;
      }

    /** Return the number of pins available on the interface.
     *
     * Pins are numbered from 0 upwards. The primary interface defines 3 analog
     * inputs - two for general purpose use and the third for monitoring the
     * battery level.
     *
     * @return the number of pins available.
     */
    virtual int pins() {
      return PIN_VBAT + 1;
      }

    /** Initialise an analog pin
     *
     * This method configures an analog pin.
     *
     * @param pin the pin to configure
     *
     * @return true if the pin was configured as requested, false on error or
     *              invalid pin number.
     */
    virtual bool init(int pin) {
      if(!isValidPin(pin))
        return false;
      // Determine the registers to use
      volatile unsigned int *ddir = (g_pins[pin].m_port==0)?&GPIO0DIR:&GPIO1DIR;
      volatile unsigned int *iocon = &REGISTER_32(IOCONFIG_BASE + (uint32_t)g_pins[pin].m_iocon);
      // Set as input with analog function
      (*ddir) &= ~((uint32_t)1 << g_pins[pin].m_pin);
      (*iocon) = (uint32_t)g_pins[pin].m_func;
      return true;
      }

    /** Read an analog value
     *
     * Reads a 16 bit value from the specified analog pin. If the physical ADC is
     * not capable of 16 bit resolution the results will be shifted so the
     * resolution available is represented in the most significant bits.
     *
     * @param pin the pin to read
     *
     * @return the resulting value scaled to a 16 bit resolution. If an error
     *         occurs or the pin has not been configured or is not available the
     *         value of 0 will be returned.
     */
    virtual uint16_t read(int pin) {
      // TODO: Implement this
      return 0;
      }

  };

// Set up the reference
static LPC_Analog lpcAnalog = LPC_Analog();
Analog *analog = &lpcAnalog;

