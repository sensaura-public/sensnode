/*--------------------------------------------------------------------------*
* Nokia 5110 LCD Driver Interface
*---------------------------------------------------------------------------*
* 31-Aug-2015 ShaneG
*
*---------------------------------------------------------------------------*/
#ifndef __NOKIA5110_H
#define __NOKIA5110_H

// Bring in required definitions
#include <sensnode.h>

class Nokia5110 {
  public:
    /** Initialise the driver on a specific SPI interface
     */
    bool init(PIN reset, PIN cd, PIN select);
  }

#endif /* __NOKIA5110_H */

