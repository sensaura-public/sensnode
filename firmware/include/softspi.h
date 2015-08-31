/*--------------------------------------------------------------------------*
* Software SPI interface
*---------------------------------------------------------------------------*
* 31-Aug-2015 ShaneG
*
*---------------------------------------------------------------------------*/
#ifndef __SOFTSPI_H
#define __SOFTSPI_H

// Bring in required definitions
#include <sensnode.h>

/** Software SPI interface
 *
 * This is an SPI interface that uses bitbanging on standard digital pins
 * to implement the protocol. It can be used where the hardware does not
 * supply an SPI interface or the hardware interface cannot be used for
 * some reason.
 */
class SoftSPI : public SPI {
  private:
    DIGITAL_PIN m_miso; //!< The pin being used for MISO
    DIGITAL_PIN m_mosi; //!< The pin being used for MOSI
    DIGITAL_PIN m_sck;  //!< The pin being used for SCK
    int         m_mode; //!< The currently active mode

  public:
    /** Constructor
     *
     * The pins to use for the software implementation are specified in the
     * constructor and will be configured the first time 'init()' is called.
     *
     * @param miso the digital pin to use for MISO
     * @param mosi the digital pin to use for MOSI
     * @param sck the digital pin to use for SCK
     */
    SoftSPI(DIGITAL_PIN miso, DIGITAL_PIN mosi, DIGITAL_PIN sck);

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
    virtual bool init(int mode = 0);

    /** Write a sequence of bytes to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pData the buffer containing the data to write
     * @param count the number of bytes to write
     */
    virtual void write(const uint8_t *pData, int count);

    /** Read a sequence of bytes from the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     * During the read the call will keep MOSI at 0.
     *
     * @param pData pointer to a buffer to receive the data
     * @param count the number of bytes to read.
     */
    virtual void read(uint8_t *pData, int count);

    /** Read and write to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pOutput a buffer containing the bytes to write to the SPI port
     * @param pInput a buffer to receive the bytes read from the SPI port
     * @param count the number of bytes to transfer. Both buffers must be at
     *        least this size.
     */
    virtual void readWrite(const uint8_t *pOutput, uint8_t *pInput, int count);
  };

#endif /* __SOFTSPI_H */

