/*---------------------------------------------------------------------------*
* SensNode - Sleep mode implementation for XMC1100
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Handles the sleep mode for the XMC1100. In this mode IO pins need to
* maintain their state but the processor core can be shutdown (or idled).
* The processor can be woken by the RTC or by activity on an input pin.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

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
WAKE_REASON sleep(uint32_t duration, TIMEUNIT units) {
  // TODO: Implement this
  return WAKE_UNKNOWN;
  }

