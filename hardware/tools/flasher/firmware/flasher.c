/*---------------------------------------------------------------------------*
* Flasher firmware
*----------------------------------------------------------------------------*
* 08-Sep-2015 ShaneG
*
* This firmware runs on an ATtiny85 on the flasher tool to control the RESET,
* PROG and VCC lines of the debug port.
*---------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

//--- Pin definitions
#define PIN_IN_SWITCH  0 // Prog/Run input switch
#define PIN_OUT_RESET  1 // RESET output line
#define PIN_OUT_PROG   2 // PROG output line
#define PIN_OUT_VCC    3 // VCC control line
#define PIN_IN_DTR     4 // DTR input line

/** Helper to set pin state
 */
void setPin(int pin, bool state) {
  if(state)
    PORTB |= (uint8_t)(1 << pin);
  else
    PORTB &= (uint8_t)~(1 << pin);
  }

/** Helepr to read pin state
 */
bool getPin(int pin) {
  return (pin & (uint8_t)(1 << pin)) != 0;
  }

/** Initialise the pins
 */
void initPins() {
  // Set states first before enabling output
  setPin(PIN_OUT_RESET, false);
  setPin(PIN_OUT_PROG, false);
  setPin(PIN_OUT_VCC, false);
  // Enable the outputs
  DDRB =
    (1 << PIN_OUT_RESET) |
    (1 << PIN_OUT_PROG) |
    (1 << PIN_OUT_VCC);
  }

/** Enter programming mode
 */
void setProgMode() {
  setPin(PIN_OUT_RESET, true);
  setPin(PIN_OUT_PROG, true);
  setPin(PIN_OUT_VCC, true);
  }

/** Enter running mode
 */
void setRunMode() {
  setPin(PIN_OUT_PROG, false);
  setPin(PIN_OUT_VCC, false);
  setPin(PIN_OUT_RESET, false);
  }

/** Perform a reset cycle
 */
void triggerReset() {
  setPin(PIN_OUT_RESET, true);
  setPin(PIN_OUT_RESET, false);
  }

/** Main program
 *
 * Set the initial state and enter the main loop
 */
int main() {
  // Initialise hardware
  initPins();
  // Are we in programming mode already ?
  bool progMode = false;
  if(getPin(PIN_IN_SWITCH)) {
    setProgMode();
    progMode = true;
    }
  bool thisDTR, lastDTR = getPin(PIN_IN_DTR);
  bool dtrPrimed = false;
  // Main loop
  while(true) {
    // In prog mode you can use a DTR high -> low -> high to toggle RESET
    if(progMode) {
      thisDTR = getPin(PIN_IN_DTR);
      if(thisDTR!=lastDTR) {
        if(!thisDTR) // High to Low, prime the pin
          dtrPrimed = false;
        else { // Low to High - trigger reset if primed
          if(dtrPrimed)
            triggerReset();
          dtrPrimed = false;
          }
        lastDTR = thisDTR;
        }
      }
    // Look for mode change
    if(getPin(PIN_IN_SWITCH)!=progMode) {
      // Possible state change, do debounce first
      _delay_ms(5);
      if(getPin(PIN_IN_SWITCH)==progMode)
        continue; // False alarm
      // Switch mode
      if(progMode)
        setRunMode();
      else
        setProgMode();
      triggerReset();
      dtrPrimed = false;
      progMode = !progMode;
      }
    }
  // Never get here
  return 0;
  }

