/*--------------------------------------------------------------------------*
* Main program loop
*---------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*
* Main program loop. Invokes the application setup and loop functions as
* well as processing power management and network activity.
*--------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

// Static initialisers (constructors, etc)
extern "C" void (**__init_array_start)();
extern "C" void (**__init_array_end)();

/** Program entry point
 */
int main() {
  // First configure and latch our power pin.
  digitalInit(PIN_LATCH, OUTPUT);
  digitalWrite(PIN_LATCH, true);
  // Call all the constructors
  for(void (**p)() = __init_array_start; p < __init_array_end; ++p)
    (*p)();
  // Set up the rest of the power head pins
  digitalInit(PIN_INDICATOR, OUTPUT);
  digitalWrite(PIN_INDICATOR, false);
  digitalInit(PIN_ACTIVITY, INPUT);
  digitalInit(PIN_POWER, INPUT);
  // TODO: Internal setup
  // Application setup
  setup();
  // Main loop
  while(true) {
    // TODO: Power management checking
    // TODO: Network processing
    // Application loop
    loop();
    }
  return 0;
  }

