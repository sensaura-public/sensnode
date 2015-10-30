/*--------------------------------------------------------------------------*
* SensNode - Date and time manipulation
*---------------------------------------------------------------------------*
* 30-Oct-2015 ShaneG
*
* Implements the platform independant date and time manipulation functions.
*--------------------------------------------------------------------------*/
#include <sensnode.h>

/** Determine if the date and time are valid
 *
 * Helper function to validate the values in a DATETIME structure.
 *
 * @param pDateTime pointer to a structure containing the new date and time.
 *
 * @return true if the values are valid, false otherwise.
 */
bool isDateTimeValid(DATETIME *pDateTime) {
  // TODO: Implement this
  return false;
  }

/** Convert a date time structure to a timestamp
 *
 * A timestamp is an integer value representing the number of seconds since
 * 1/1/1970. Using a timestamp makes conversion and comparison of DATETIME
 * values easier.
 *
 * @param pDateTime pointer to a structure containing the date and time.
 *
 * @return the number of seconds since 1/1/1970 to the date and time specified
 *         in the structure. If the structure represents a time prior to the
 *         epoch or contains invalid information the return value will be 0.
 */
uint32_t toTimestamp(DATETIME *pDateTime) {
  // TODO: Implement this
  return 0;
  }

/** Convert a timestamp to a date time structure
 *
 * A timestamp is an integer value representing the number of seconds since
 * 1/1/1970. Using a timestamp makes conversion and comparison of DATETIME
 * values easier.
 *
 * @param pDateTime pointer to a structure to receive the date and time.
 * @param timestamp the timestamp value to convert.
 */
void fromTimestamp(DATETIME *pDateTime, uint32_t timestamp) {
  // TODO: Implement this
  }

