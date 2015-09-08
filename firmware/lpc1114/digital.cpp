/*---------------------------------------------------------------------------*
* LPC1114 implementation of digital IO
*----------------------------------------------------------------------------*
* 02-Sep-2015 ShaneG
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>
#include "common.h"

// Number of core pins
#define PIN_COUNT 12

/** Assign ports and pin numbers to all defined pins
 */
static const PINDEF g_pins[] = {
  { m_port: 1, m_pin: 9,  m_func: 0x00, m_iocon: 0x38 }, // PIN_D0
  { m_port: 1, m_pin: 8,  m_func: 0x00, m_iocon: 0x14 }, // PIN_D1
  { m_port: 1, m_pin: 0,  m_func: 0x01, m_iocon: 0x78 }, // PIN_D2
  { m_port: 0, m_pin: 7,  m_func: 0x00, m_iocon: 0x50 }, // PIN_D3
  { m_port: 0, m_pin: 2,  m_func: 0x00, m_iocon: 0x1C }, // PIN_D4
  { m_port: 0, m_pin: 3,  m_func: 0x00, m_iocon: 0x2C }, // PIN_D5
  { m_port: 0, m_pin: 4,  m_func: 0x00, m_iocon: 0x30 }, // PIN_D6
  { m_port: 0, m_pin: 5,  m_func: 0x00, m_iocon: 0x34 }, // PIN_D7
  { m_port: 0, m_pin: 8,  m_func: 0x00, m_iocon: 0x60 }, // PIN_INDICATOR
  { m_port: 0, m_pin: 9,  m_func: 0x00, m_iocon: 0x64 }, // PIN_ACTIVITY
  { m_port: 0, m_pin: 6,  m_func: 0x00, m_iocon: 0x4C }, // PIN_LATCH
  { m_port: 0, m_pin: 10, m_func: 0x01, m_iocon: 0x04 }, // PIN_POWER
  };

/** Determine if a pin is valid
 */
static bool isValidPin(int pin) {
  if((pin<0)||(pin>=PIN_COUNT))
    return false;
  return g_pins[pin].m_pin != 15;
  }

/** Class to access LPC1114 digital pins
 */
class LPC_Digital : public Digital {
  private:
    int m_base;  // Base offset for pin
    int m_count; // Number of pins for this instance

  public:
    /** Constructor
     *
     * The constructor is provided with a base offset into the pin table and
     * a pin count.
     *
     * @param base the base offset into the pin table
     * @param count the number of pins this instance provides.
     */
    LPC_Digital(int base, int count) {
      m_base = base;
      m_count = count;
      }

    /** Initialise the digital pin interface
     *
     * Configure the interface prior to use. Note that the core implementations
     * are initialised at start up and do not require explicit initialisation by
     * the application.
     *
     * @return true if the initialise succeeded.
     */
    virtual bool init() {
      return true;
      }

    /** Determine the number of pins available
     *
     * @return the number of pins supported by the interface.
     */
    virtual int pins() {
      return m_count;
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
    virtual bool init(int pin, IODIR dir, bool pullup) {
      if((pin<0)||(pin>=m_count))
        return false;
      // Get the real pin index
      pin = m_base + pin;
      if(!isValidPin(pin))
        return false;
      // Determine the registers to use
      volatile unsigned int *ddir = (g_pins[pin].m_port==0)?&GPIO0DIR:&GPIO1DIR;
      volatile unsigned int *iocon = &REGISTER_32(IOCONFIG_BASE + (uint32_t)g_pins[pin].m_iocon);
      // Set direction
      if(dir==INPUT) {
        (*ddir) &= ~((uint32_t)1 << g_pins[pin].m_pin);
        (*iocon) = (uint32_t)g_pins[pin].m_func | (pullup?BIT4:0);
        }
      else {
        (*ddir) |= (uint32_t)1 << g_pins[pin].m_pin;
        (*iocon) = (uint32_t)g_pins[pin].m_func;
        }
      return true;
      }

    /** Read the current value of the digital pin
     *
     * @param pin the digital pin to read
     *
     * @return true if the pin is currently 'high', false if 'low'
     */
    virtual bool read(int pin) {
      if((pin<0)||(pin>=m_count))
        return false;
      // Get the real pin index
      pin = m_base + pin;
      if(!isValidPin(pin))
        return false;
      // Determine the registers to use
      volatile unsigned int *data = (g_pins[pin].m_port==0)?&GPIO0DATA:&GPIO1DATA;
      return ((*data) & ((uint32_t)1 << g_pins[pin].m_pin)) != 0;
      }

    /** Write a value to the digital pin
     *
     * @param pin the digital pin to write
     * @param value the new value of the pin - true for 'high', false for 'low'
     */
    virtual void write(int pin, bool value) {
      if((pin<0)||(pin>=m_count))
        return;
      // Get the real pin index
      pin = m_base + pin;
      if(!isValidPin(pin))
        return;
      // Determine the registers to use
      volatile unsigned int *data = (g_pins[pin].m_port==0)?&GPIO0DATA:&GPIO1DATA;
      if(value)
        (*data) |= ((uint32_t)1 << g_pins[pin].m_pin);
      else
        (*data) &= ~((uint32_t)1 << g_pins[pin].m_pin);
      }
  };

// The core interfaces
static LPC_Digital lpcDigital = LPC_Digital(0, 8);
Digital *digital = &lpcDigital;
static LPC_Digital lpcPower = LPC_Digital(8, 4);
Digital *power = &lpcPower;

