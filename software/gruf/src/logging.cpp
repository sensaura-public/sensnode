/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Logging
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Handle logging output for the application.
*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <gruf.h>

// Current verbosity level
VERBOSITY g_verbosity = NORMAL;

/** Set the application verbosity
 *
 * The verbosity level starts as NORMAL but can be changed by the command line
 * options.
 *
 * @param verbosity the required verbosity level
 */
void setVerbosity(VERBOSITY verbosity) {
  if(verbosity<QUIET)
    g_verbosity = QUIET;
  else if(verbosity>VERBOSE)
    g_verbosity = VERBOSE;
  else
    g_verbosity = verbosity;
  }

/** Emit a debugging message
 *
 * Debug messages are only displayed in verbose mode.
 *
 * @param cszFormat format string (as per 'printf()')
 */
void DLog(const char *cszFormat, ...) {
  if(g_verbosity<VERBOSE)
    return;
  // Get the arguments
  va_list args;
  va_start(args, cszFormat);
  // Emit the message
  fprintf(stdout, "DEBUG: ");
  vfprintf(stdout, cszFormat, args);
  fprintf(stdout, "\n");
  }

/** Emit a informational message
 *
 * Informational messages are not displayed in quiet mode.
 *
 * @param cszFormat format string (as per 'printf()')
 */
void ILog(const char *cszFormat, ...) {
  if(g_verbosity<NORMAL)
    return;
  // Get the arguments
  va_list args;
  va_start(args, cszFormat);
  // Emit the message
  vfprintf(stdout, cszFormat, args);
  fprintf(stdout, "\n");
  }

/** Emit an error message
 *
 * Error messages are always displayed.
 *
 * @param cszFormat format string (as per 'printf()')
 */
void ELog(const char *cszFormat, ...) {
  // Get the arguments
  va_list args;
  va_start(args, cszFormat);
  // Emit the message
  fprintf(stderr, "ERROR: ");
  vfprintf(stderr, cszFormat, args);
  fprintf(stderr, "\n");
  }

