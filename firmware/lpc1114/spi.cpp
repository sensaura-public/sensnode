/*--------------------------------------------------------------------------*
* SPI Implementation for the LPC1114
*---------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*
* This board uses SoftSPI to provide the SPI interface due to board routing
* issues.
*--------------------------------------------------------------------------*/
#include <sensnode.h>

// Create the SPI instance with the appropriate pin mappings.
static SoftSPI lpcSPI = SoftSPI(D5, D4, D3);
SPI *spi = &lpcSPI;

