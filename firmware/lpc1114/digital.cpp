/*---------------------------------------------------------------------------*
* LPC1114 implementation of digital IO
*----------------------------------------------------------------------------*
* 02-Sep-2015 ShaneG
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

typedef struct {
  uint8_t m_port  : 1;
  uint8_t m_pin   : 4;
  uint8_t m_func  : 2;
  uint8_t m_iocon : 8;
  } PINDEF;

/** Assign ports and pin numbers to all defined pins
 */
static const PINDEF g_pins[] = {
  { m_port: 1, m_pin: 9, m_func: 0x00, m_iocon: 0x38 }, // PIN_D0
  { m_port: 1, m_pin: 8, m_func: 0x00, m_iocon: 0x14 }, // PIN_D1
  { m_port: 1, m_pin: 0, m_func: 0x01, m_iocon: 0x78 }, // PIN_D2
  { m_port: 0, m_pin: 7, m_func: 0x00, m_iocon: 0x50 }, // PIN_D3
  { m_port: 0, m_pin: 2, m_func: 0x00, m_iocon: 0x1C }, // PIN_D4
  { m_port: 0, m_pin: 3, m_func: 0x00, m_iocon: 0x2C }, // PIN_D5
  { m_port: 0, m_pin: 4, m_func: 0x00, m_iocon: 0x30 }, // PIN_D6
  { m_port: 0, m_pin: 5, m_func: 0x00, m_iocon: 0x34 }, // PIN_D7
  { m_port: 0, m_pin: 8, m_func: 0x00, m_iocon: 0x60 }, // PIN_INDICATOR
  { m_port: 0, m_pin: 9, m_func: 0x00, m_iocon: 0x64 }, // PIN_ACTIVITY
  { m_port: 0, m_pin: 6, m_func: 0x00, m_iocon: 0x4C }, // PIN_LATCH
  { m_port: 1, m_pin: 15, m_func: 0x00, m_iocon: 0x00 }, // PIN_POWER
  };

/** Determine if a pin is valid
 */
static bool isValidPin(int pin) {
  if((pin<0)||(pin>PIN_POWER))
    return false;
  return g_pins[pin].m_pin != 15;
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
bool digitalInit(int pin, IODIR dir, bool pullup) {
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
bool digitalRead(int pin) {
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
void digitalWrite(int pin, bool value) {
  if(!isValidPin(pin))
    return;
  // Determine the registers to use
  volatile unsigned int *data = (g_pins[pin].m_port==0)?&GPIO0DATA:&GPIO1DATA;
  if(value)
    (*data) |= ((uint32_t)1 << g_pins[pin].m_pin);
  else
    (*data) &= ~((uint32_t)1 << g_pins[pin].m_pin);
  }

