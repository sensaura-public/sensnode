/*---------------------------------------------------------------------------*
* Clocked transfer and software SPI
*----------------------------------------------------------------------------*
* 01-Sep-2015 ShaneG
*
* Provides low level clocked transfer operations (to send and receive data
* from shift registers) and a software implementation of the SPI class.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

//---------------------------------------------------------------------------
// Clocked data transfer
//---------------------------------------------------------------------------

/** Shift data out using clocked transfer
 *
 * @param data the pin to use for the data transfer
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param value the value to send
 * @param bits the number of bits to send
 */
void shiftOut(DIGITAL_PIN data, DIGITAL_PIN clock, int mode, uint32_t value, int bits) {
  // TODO: Implement this
  }

/** Shift data in using a clocked transfer
 *
 * @param data the pin to use for the data transfer
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param bits the number of bits to send
 *
 * @return the data value received
 */
uint32_t shiftIn(DIGITAL_PIN data, DIGITAL_PIN clock, int mode, int bits) {
  // TODO: Implement this
  return 0;
  }

/** Exchange data in using a clocked transfer
 *
 * @param in the pin to use for input data
 * @param out the pin to use for output data
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param value the value to send
 * @param bits the number of bits to send
 *
 * @return the data value received
 */
uint32_t shiftInOut(DIGITAL_PIN in, DIGITAL_PIN out, DIGITAL_PIN clock, int mode, uint32_t value, int bits) {
  // TODO: Implement this
  }

//---------------------------------------------------------------------------
// Software SPI implementation
//---------------------------------------------------------------------------

/** Constructor
 */
SoftSPI::SoftSPI(DIGITAL_PIN miso, DIGITAL_PIN mosi, DIGITAL_PIN sck) {
  m_miso = miso;
  m_mosi = mosi;
  m_sck = sck;
  }

/** Initialise the SPI interface with the specific mode
 *
 * This method may be called multiple times to change the operating mode.
 * The mode values supported are:
 *
 * Mode CPOL CPHA
 *  0    0    0
 *  1    0    1
 *  2    1    0
 *  3    1    1
 */
bool SoftSPI::init(int mode) {
  // Configure the pins
  digitalInit(m_miso, INPUT, false);
  digitalInit(m_mosi, OUTPUT, false);
  digitalInit(m_sck, OUTPUT, false);
  digitalWrite(m_sck, mode & POLARITY_HIGH);
  // Save the mode
  m_mode = mode;
  }

/** Write a sequence of bytes to the SPI interface
 *
 * This method assumes the target device has been selected by the caller.
 *
 * @param pData the buffer containing the data to write
 * @param count the number of bytes to write
 */
void SoftSPI::write(const uint8_t *pData, int count) {
  for(int index=0; index<count; index++)
    shiftOut(m_mosi, m_sck, m_mode, (uint32_t)pData[index], 8);
  }

/** Read a sequence of bytes from the SPI interface
 *
 * This method assumes the target device has been selected by the caller.
 * During the read the call will keep MOSI at 0.
 *
 * @param pData pointer to a buffer to receive the data
 * @param count the number of bytes to read.
 */
void SoftSPI::read(uint8_t *pData, int count) {
  for(int index=0; index<count; index++)
    pData[index] = (uint8_t)(shiftIn(m_miso, m_sck, m_mode, 8) & 0xFF);
  }

/** Read and write to the SPI interface
 *
 * This method assumes the target device has been selected by the caller.
 *
 * @param pOutput a buffer containing the bytes to write to the SPI port
 * @param pInput a buffer to receive the bytes read from the SPI port
 * @param count the number of bytes to transfer. Both buffers must be at
 *        least this size.
 */
void SoftSPI::readWrite(const uint8_t *pOutput, uint8_t *pInput, int count) {
  for(int index=0; index<count; index++)
    pInput[index] = (uint8_t)(shiftInOut(m_miso, m_mosi, m_sck, m_mode, pOutput[index], 8) & 0xFF);
  }

