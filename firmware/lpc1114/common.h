/*---------------------------------------------------------------------------*
* LPC1114 shared structures
*----------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*---------------------------------------------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

/** Pin definition
 *
 * This structure is used to maintain enough information about an IO pin to
 * determine the appropriate registers to use.
 */
typedef struct {
  uint8_t m_port  : 1;
  uint8_t m_pin   : 4;
  uint8_t m_func  : 2;
  uint8_t m_iocon : 8;
  } PINDEF;

#endif /* __COMMON_H */

