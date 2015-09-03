/*--------------------------------------------------------------------------*
* Interrupt handling
*---------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*
* Provides the default interrupt behaviour.
*--------------------------------------------------------------------------*/
#include <platform.h>

/** Default interrupt handler
 *
 * This is used as the interrupt handler when no others have been defined, it
 * simply puts the processor into an endless loop.
 */
void defaultInterruptHandler() {
  while(1);
  }

/** Pure virtual crash handler
 *
 * Not an interrupt, but used to handle calls to pure virtual methods.
 */
extern "C" void __cxa_pure_virtual() {
  while (1);
  }


