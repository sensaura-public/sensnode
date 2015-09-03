/*--------------------------------------------------------------------------*
* Timing functions implementation
*---------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*
* Implements the common timing functions.
*--------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

// Make sure TICKS_PER_SECOND is valid
#if TICKS_PER_SECOND < 1000000L
#  error TICKS_PER_SECOND must be >= 1000000
#endif

/** Calculate the time difference between two tick counts.
 *
 * This function will convert the difference between two tick count values into
 * an actualy time period. Tick count wrap around is accounted for. The return
 * value is the number of whole units rounded down.
 *
 * @param start the tick count at the start of the period
 * @param end the tick count at the end of the period
 * @param units the time units to calculate the difference in.
 *
 * @return the amount of elapsed time in whole units.
 */
uint32_t timeElapsed(uint32_t start, uint32_t end, TIMEUNIT units) {
  // Calculate the duration in ticks
  uint32_t ticks;
  if(start<end)
    ticks = end - start;
  else
    ticks = (TICKS_MAX - start) + end;
  // Convert to the appropriate units
  switch(units) {
    case MICROSECOND:
      ticks = ticks / (TICKS_PER_SECOND / 1000000L);
      break;
    case MILLISECOND:
      ticks = ticks / (TICKS_PER_SECOND / 1000);
      break;
    case SECOND:
      ticks = ticks / TICKS_PER_SECOND;
      break;
    }
  return ticks;
  }

/** Determine if the specified amount of time has expired.
 *
 * This function compares the current tick count with a previously stored
 * start point and determines if the requested amount of time has expired
 * yet.
 *
 * @param reference the starting reference
 * @param duration the time period we are waiting to expire
 * @param units the units the duration is expressed in
 *
 * @return true if the specified duration has expired since the reference
 *              point.
 */
bool timeExpired(uint32_t reference, uint32_t duration, TIMEUNIT units) {
  return timeElapsed(reference, getTicks(), units) > duration;
  }

