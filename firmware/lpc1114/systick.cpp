/*--------------------------------------------------------------------------*
* System tick access
*---------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*
* Provides access to the system tick timer
*--------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

/** Get the current system tick count
 *
 * Each processor board maintains a count of system ticks since power up, this
 * function returns the current value of that count. The duration of a single
 * tick is processor independent - use the 'timeExpired()' function to determine
 * if a time period has been exceeded or 'timeElapsed()' to determine the
 * amount of time between two tick counts.
 *
 * @return the current system tick count.
 */
uint32_t getTicks() {
  return SYST_CVR;
  }

