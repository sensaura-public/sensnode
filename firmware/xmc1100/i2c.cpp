/*---------------------------------------------------------------------------*
* SensNode - I2C implementation for XMC1100
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Provides the I2C interface functions for the XMC1100 based board.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

/** Initialise the I2C interface
 *
 * This function sets up the I2C interface on PIN0/PIN1 and disables the use
 * of those pins for general purpose IO. Future calls to pinConfig() for
 * either pin will fail.
 */
void i2cConfig() {
  // TODO: Implement this
  }

/** Write a bit stream to the I2C device
 *
 * This function is used to send a sequence of bits to the i2c slave device
 * identified by the address.
 *
 * @param address the address of the slave device
 * @param data the data to send, the lowest 'count' bits will be sent in
 *             MSB order.
 * @param count the number of bits to write.
 */
void i2cWriteBits(uint8_t address, uint32_t data, int count) {
  // TODO: Implement this
  }

/** Read a bit stream from the I2C device
 *
 * This function is used to read a sequence of bits from the i2c slave
 * identified by the address.
 *
 * @param address the address of the slave device
 * @param count the number of bits to read
 *
 * @return a 32 bit value containing the bits read in the least significant
 *         bits.
 */
uint32_t i2cReadBits(uint8_t address, int count) {
  // TODO: Implement this
  return 0;
  }

/** Write a sequence of byte values to the i2c slave
 *
 * @param address the address of the slave device
 * @param pData pointer to a buffer containing the data to send
 * @param count the number of bytes to transmit
 */
void i2cWriteBytes(uint8_t address, const uint8_t *pData, int count) {
  // TODO: Implement this
  }

/** Read a sequence of bytes from the i2c slave
 *
 * @param address the address of the slave device
 * @param pData a pointer to a buffer to receive the data read
 * @param count the maximum number of bytes to read
 *
 * @return the number of bytes read from the slave.
 */
int i2cReadBytes(uint8_t address, uint8_t *pData, int count) {
  // TODO: Implement this
  }

