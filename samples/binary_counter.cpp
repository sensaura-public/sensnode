/*--------------------------------------------------------------------------*
* Sample SensNode main program
*---------------------------------------------------------------------------*
* 08-Sep-2015 ShaneG
*
* Updated to the new interface model for GPIO pins.
*
* 03-Sep-2015 ShaneG
*
* This sample simply uses the 8 digital output bins as a binary counter
* output incrementing the count every 250 milliseconds.
*--------------------------------------------------------------------------*/
#include <sensnode.h>

// Last activity timestamp
static uint32_t g_timer;

// Current pin state
static uint8_t g_state = 0;

/** User application initialisation
 *
 * The library will call this function once at startup to allow the user
 * application to do any initialisation it needs. At the time this function
 * is called all IO pins will have been set to their default states and the
 * network subsystem initialised (if not yet connected).
 */
void setup() {
  // Set all pins as output
  for(int pin=PIN_D0; pin<=PIN_D7; pin++) {
    digital->init(pin, OUTPUT);
    digital->write(pin, false);
    }
  g_timer = getTicks();
  }

/** User application loop
 *
 * The library repeatedly calls this function in an endless loop. The function
 * will generally be implemented as a state machine and take care to minimise
 * the amount of time spent in the function itself.
 */
void loop() {
  // Update state if needed
  if(timeExpired(g_timer, 250, MILLISECOND)) {
    g_timer = getTicks();
    g_state++;
    // Update pin output
    DBG("Updating pin output");
    for(int pin=PIN_D0; pin<=PIN_D7; pin++)
      digital->write(pin, g_state & (1 << pin));
    }
  }

