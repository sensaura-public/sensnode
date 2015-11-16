/*---------------------------------------------------------------------------*
* SensNode - Datetime hardware functions for the XMC1100
*----------------------------------------------------------------------------*
* 30-Oct-2015 ShaneG
*
* Provides the hardware specific functions for the RTC module on the XMC1100.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

/** Get the current date and time according to the RTC
 *
 * @param pDateTime pointer to a structure to receive the date and time data.
 *
 * @return true on success, false on failure.
 */
bool getDateTime(DATETIME *pDateTime) {
  // TODO: Implement this
  return false;
  }

/** Set the current date and time in the RTC
 *
 * @param pDateTime pointer to a structure containing the new date and time.
 *
 * @return true on success, false on failure.
 */
bool setDateTime(DATETIME *pDateTime) {
  // TODO: Implement this
  return false;
  }

/** Set an alarm
 *
 * This function is used internally by the 'sleep()' function to set a wake
 * up event for the processor. Calling it from application code will have
 * no effect (the interrupt is essentially ignored).
 *
 * @param pDateTime pointer to a structure containing date and time for the alarm.
 *
 * @return true on success, false on failure.
 */
bool setAlarm(DATETIME *pDateTime) {
  // TODO: Implement this
  return false;
  }

