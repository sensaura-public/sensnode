/*--------------------------------------------------------------------------*
* NRF24L01 Driver Interface
*---------------------------------------------------------------------------*
* 31-Aug-2015 ShaneG
*
*---------------------------------------------------------------------------*/
#ifndef __NRF24L01_H
#define __NRF24L01_H

// Bring in required definitions
#include <sensnode.h>

class NRF24L01 {
  public:
    /** Initialise the driver on a specific SPI interface
     */
    bool init(SPI *pSPI, DIGITAL_PIN select);
  }

#endif /* __NRF24L01_H */

