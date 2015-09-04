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

// Static initialisers (constructors, etc)
extern "C" void (**__init_array_start)();
extern "C" void (**__init_array_end)();

//---------------------------------------------------------------------------
// Internal implementation
//---------------------------------------------------------------------------

#define BATTERY_CHECK 60
#define BATTERY_RETRY 3

/** Battery monitoring
 *
 * This task checks the battery level periodically and, if it falls below a
 * user specified level, shuts down the sensor. There is a level of hysterisis
 * involved - the battery must remain below the shutdown level for a number
 * of samples before the shutdown is triggered. This protects against shutting
 * down during high load periods.
 */
static void taskBattery() {
  static uint32_t timer = 0;
  static int count = 0;
  // Do we have a limit ?
  if(g_battery==0)
    return; // No limit
  // Is it time to check the battery ?
  if(!timeExpired(timer, BATTERY_CHECK, SECOND))
    return;
  timer = getTicks();
  // Check the battery level
  if(analogRead(PIN_VBAT)>=g_battery) {
    count = 0;
    return;
    }
  // Increment the count
  count++;
  if(count>=BATTERY_RETRY) {
    // TODO: Show indication of low battery
    shutdown();
    }
  }

/** Implements the main loop
 *
 * This processes the network, battery monitoring and application loop. It is
 * invoked by the main program and by the delay() function.
 *
 * @param userTask if true, run the user application loop as well.
 */
static void mainLoop(bool userTask) {
  // Power management checking
  taskBattery();
  // TODO: Network processing
  // Application loop
  if(userTask)
    loop();
  }

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
  analogInit(PIN_VBAT);
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

/** Set the battery shutdown limit
 *
 * Set the ADC reading at which the battery level will trigger a shutdown. The
 * value at power up is 0 (which means never). The actual value will depend on
 * the power source connected and the type of battery. This is intended to
 * protect against draining LiION batteries to too low a level or to shutdown
 * if an unreliable power supply will impact sensor readings.
 *
 * @param level the ADC reading to shutdown at.
 */
void setBatteryLimit(uint16_t level) {
  g_battery = level;
  }

/** Power down the device
 *
 * This function will completely power down the device. It is usually only
 * called in situations where continuing to operate would be dangerous or
 * possibly damage the sensor.
 */
void shutdown() {
  digitalWrite(PIN_LATCH, false);
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

/** Put the processor into sleep mode
 *
 * This function puts the CPU into sleep mode for the specified period of
 * time to conserve power. While the processor is sleeping other background
 * tasks (network operations, battery monitoring, etc) will also be paused.
 *
 * If the processor does not support sleep mode (or doesn't have an RTC to
 * trigger waking) this function will behave like the 'delay()' function.
 *
 * @param duration the amount of time to delay for
 * @param units the units the duration is specified in
 */
void sleep(uint32_t duration, TIMEUNIT units) {
  delay(duration, units);
  }

