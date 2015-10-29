/*---------------------------------------------------------------------------*
* Clocked transfer and software SPI
*----------------------------------------------------------------------------*
* 01-Sep-2015 ShaneG
*
* Provides low level clocked transfer operations (to send and receive data
* from shift registers) and a software implementation of the SPI class.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

/** Shift data out using clocked transfer
 *
 * @param polarity the polarity of the SPI clock - true = HIGH, false = LOW
 * @param phase the phase of the SPI clock - true = HIGH, false = LOW
 * @param msbFirst true if data should be sent MSB first, false if LSB first.
 * @param clock the pin to use for the clock
 * @param output the pin to use for the output data
 * @param value the value to send
 * @param bits the number of bits to send
 */
void shiftOut(bool polarity, bool phase, bool msbFirst, PIN clock, PIN output, uint32_t value, int bits) {
  // TODO: Implement this
  }

/** Shift data in using clocked transfer
 *
 * @param polarity the polarity of the SPI clock - true = HIGH, false = LOW
 * @param phase the phase of the SPI clock - true = HIGH, false = LOW
 * @param msbFirst true if data should be sent MSB first, false if LSB first.
 * @param clock the pin to use for the clock
 * @param input the pin to use for the input data
 * @param bits the number of bits to read
 *
 * @return the data read
 */
uint32_t shiftIn(bool polarity, bool phase, bool msbFirst, PIN clock, PIN input, int bits) {
  // TODO: Implement this
  return 0;
  }

/** Exchange data using a clocked transfer
 *
 * @param polarity the polarity of the SPI clock - true = HIGH, false = LOW
 * @param phase the phase of the SPI clock - true = HIGH, false = LOW
 * @param msbFirst true if data should be sent MSB first, false if LSB first.
 * @param clock the pin to use for the clock
 * @param input the pin to use for the input data
 * @param output the pin to use for the output data
 * @param value the value to send
 * @param bits the number of bits to transfer
 *
 * @return the data read
 */
uint32_t shiftInOut(bool polarity, bool phase, bool msbFirst, PIN clock, PIN input, PIN output, uint32_t data, int bits) {
  // TODO: Implement this
  return 0;
  }

