/*---------------------------------------------------------------------------*
* SensNode - SPI implementation for XMC1100
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Provides the SPI interface functions for the XMC1100 based board. Because
* the XMC1100 only has two serial channels (and they are used for I2C and
* the UART) we provide SPI support through software.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

// Current SPI state
static bool g_spiPolarity;
static bool g_spiPhase;
static bool g_spiMSBFirst;

//----------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------

/** Configure the SPI interface
 *
 * This function sets the operating mode for the SPI interface for future
 * data transfer calls.
 *
 * @param polarity the polarity of the SPI clock - true = HIGH, false = LOW
 * @param phase the phase of the SPI clock - true = HIGH, false = LOW
 * @param msbFirst true if data should be sent MSB first, false if LSB first.
 */
void spiConfig(bool polarity, bool phase, bool msbFirst) {
  g_spiPolarity = polarity;
  g_spiPhase = phase;
  g_spiMSBFirst = msbFirst;
  }

/** Write a sequence of bytes to the SPI interface
 *
 * This function assumes the target device has been selected by the caller.
 *
 * @param pData the buffer containing the data to write
 * @param count the number of bytes to write
 */
void spiWrite(const uint8_t *pData, int count) {
  for(int i=0; i<count; i++)
    shiftOut(g_spiPolarity, g_spiPhase, g_spiMSBFirst, PIN_SCK, PIN_MOSI, pData[i], 8);
  }

/** Read a sequence of bytes from the SPI interface
 *
 * This function assumes the target device has been selected by the caller.
 * During the read the call will keep MOSI at 0.
 *
 * @param pData pointer to a buffer to receive the data
 * @param count the number of bytes to read.
 */
void spiRead(uint8_t *pData, int count) {
  for(int i=0; i<count; i++)
    pData[i] = (uint8_t)shiftIn(g_spiPolarity, g_spiPhase, g_spiMSBFirst, PIN_SCK, PIN_MISO, 8);
  }

/** Read and write to the SPI interface
 *
 * This function assumes the target device has been selected by the caller.
 *
 * @param pOutput a buffer containing the bytes to write to the SPI port
 * @param pInput a buffer to receive the bytes read from the SPI port
 * @param count the number of bytes to transfer. Both buffers must be at
 *        least this size.
 */
void spiTransfer(const uint8_t *pOutput, uint8_t *pInput, int count) {
  for(int i=0; i<count; i++)
    pInput[i] = (uint8_t)shiftInOut(g_spiPolarity, g_spiPhase, g_spiMSBFirst, PIN_SCK, PIN_MISO, PIN_MOSI, pOutput[i], 8);
  }

