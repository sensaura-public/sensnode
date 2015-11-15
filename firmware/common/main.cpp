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

// Battery level cutoff
static uint16_t g_battery = 0;

// Indicator pattern
static uint16_t g_pattern = 0;
static uint8_t  g_patternIdx = 0;
static bool     g_patternRepeat = false;
static uint32_t g_patternTimer = 0;

// Static initialisers (constructors, etc)
extern "C" void (**__init_array_start)();
extern "C" void (**__init_array_end)();

//---------------------------------------------------------------------------
// Internal implementation
//---------------------------------------------------------------------------

/** Implements the main loop
 *
 * This processes the network, battery monitoring and application loop. It is
 * invoked by the main program and by the delay() function.
 *
 * @param userTask if true, run the user application loop as well.
 */
static void mainLoop(bool userTask) {
  // Power management checking
//  taskBattery();
  // Indicator display
//  taskIndicator();
  // TODO: Network processing
  // Application loop
  if(userTask)
    loop();
  }

/** Program entry point
 */
int main() {
  // First configure and latch our power pin.
  pinConfig(PIN_LATCH, DIGITAL_OUTPUT, 1);
  pinWrite(PIN_LATCH, true);
  // Call all the constructors
  for(void (**p)() = __init_array_start; p < __init_array_end; ++p)
    (*p)();
  // Set up the rest of the power head pins
  pinConfig(PIN_INDICATOR, DIGITAL_OUTPUT, 0);
  pinWrite(PIN_INDICATOR, false);
  pinConfig(PIN_ACTION, DIGITAL_INPUT, WAKEUP);
  pinConfig(PIN_BATTERY, ANALOG);
  // Show we are on (2s indicator LED)
//  indicate(PATTERN_FULL, false);
  // TODO: Internal setup
  // Application setup
  setup();
  // Main loop
  while(true)
    mainLoop(true);
  return 0;
  }

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------

/** Set the output indication sequence
 *
 * Every power adapter has an indication LED which is used to provide visual
 * feedback. This function sets an indication pattern to run on the LED. A
 * pattern consists of a sequence of 16 LED states (1 = on, 0 = off) which
 * are stepped through every 125ms giving a total of 2s for each pattern.
 *
 * If a pattern is already running it will be terminated at the current step
 * and the new pattern started instead.
 *
 * @param pattern the 16 bit pattern to start.
 * @param repeat if true the pattern will be repeated until a new pattern is
 *               set.
 */
void indicate(uint16_t pattern, bool repeat) {
//  resetIndicator();
  g_pattern = pattern;
  g_patternRepeat = repeat;
  }

/** Power down the device
 *
 * This function will completely power down the device. It is usually only
 * called in situations where continuing to operate would be dangerous or
 * possibly damage the sensor.
 */
void shutdown() {
  pinWrite(PIN_LATCH, false);
  // Enter endless loop
  while(true);
  }

/** Delay the invocation of the application loop for a specified duration
 *
 * This function will block until the specified time period has elapsed but
 * background tasks (network operations, battery monitoring, etc) will continue.
 *
 * @param duration the amount of time to delay for
 * @param units the units the duration is specified in
 */
void delay(uint32_t duration, TIMEUNIT units) {
  static bool inDelay = false;
  if(inDelay)
    return; // Avoid recursive calls
  inDelay = true;
  // Run the main loop without the user application for a while
  uint32_t timer = getTicks();
  while(!timeExpired(timer, duration, units))
    mainLoop(false);
  inDelay = false;
  }

