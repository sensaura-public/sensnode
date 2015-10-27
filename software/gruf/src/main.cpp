/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Main Program
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Main program for the flashing tool.
*---------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <gruf.h>
#include <optionparser.h>

// Version information
#define VER_MAJOR 0
#define VER_MINOR 1

/** Program entry point
 */
int main(int argc, char *argv[]) {
  ILog("Grand Unified Flasher V%d.%02d", VER_MAJOR, VER_MINOR);
  return 0;
  }

