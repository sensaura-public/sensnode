/*---------------------------------------------------------------------------*
* LPC1114 implementation of PWM
*----------------------------------------------------------------------------*
* 04-Sep-2015 ShaneG
*
* The prototype board does not have the PWM output configured. Code is here
* simply to allow linking.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

/** Initialise the PWM pin
 *
 * @param freq the frequency to run the PWM output at
 *
 * @return true if PWM is available, false if not.
 */
bool pwmInit(FREQUENCY freq) {
  return false;
  }

/** Set the PWM duty cycle
 *
 * @param duty the duty cycle from 0 (always low) to 0xff (always on).
 */
void pwmDuty(uint8_t cycle) {
  // NOTE: PWM not available on LPC1114 prototype
  }

