/*---------------------------------------------------------------------------*
* LPC1114 implementation of serial port and debugging
*----------------------------------------------------------------------------*
* 04-Sep-2015 ShaneG
*
* Set up UART0 and enable debugging and default serial access.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <platform.h>

// Status register (U0LSR) bits
#define U0LSR_RDR  BIT0 // Receive data ready
#define U0LSR_THRE BIT5 // Transmit register ready

// Default baud rate for first initialisation
#define DEFAULT_BAUD_RATE 57600

/** Set up the TX/RX pins and enable the UART clock
 */
static void setupPins() {
  IOCON_PIO1_6 = 1; // RX mode
  IOCON_PIO1_7 = 1; // TX mode
  // Enable clock to UART
  SYSAHBCLKCTRL |= BIT12;
  }

/** Configure the serial port for a specific baud rate
 *
 * To avoid look up tables and floating point math this function uses a very
 * simplistic method of calculating the divisors for the baud rate - this
 * mean for some rates accuracy could be an issue.
 *
 * @param baud the baud rate to set
 */
static void setupSerial(int baud) {
  UARTCLKDIV = 1;
  uint32_t DL = SYSTEM_CLOCK / (16 * baud);
  U0LCR = BIT0 | BIT1 | BIT7; // 8N1, enable baud config
  U0DLM = (DL >> 8) & 0xFF;
  U0DLL = DL & 0xFF;
  U0LCR = BIT0 | BIT1; // 8N1, disable baud config
  U0FCR = BIT0 | BIT1 | BIT2; // Enable and clear FIFO buffer
  }

/** Implementation of the Serial interface for the LPC1114
 */
class LPCSerial : public Serial {
  public:
    /** Constructor
     *
     * Initialise the serial port with the default baud rate so debugging will
     * work immediately.
     */
    LPCSerial() {
      setupPins();
      setupSerial(DEFAULT_BAUD_RATE);
      }

    /** Initialise the port with the specified baud rate.
     *
     * @param baud the baud rate to use.
     *
     * @return true if the port was configured correctly.
     */
    virtual bool init(int baud) {
      setupSerial(baud);
      return true;
      }

    /** Determine if data is available to read
     *
     * @return true if data is available to read.
     */
    virtual bool available() {
      return U0LSR & U0LSR_RDR;
      }

    /** Read a single byte from the serial port
     *
     * @return the value of the byte read or -1 if no data is available.
     */
    virtual int read() {
      if(!(U0LSR & U0LSR_RDR))
        return -1;
      return U0RBR & 0xff;
      }

    /** Write a single character to the stream
     *
     * @param ch the character to write.
     *
     * @return true if the write was successful
     */
    virtual bool write(char ch) {
      while(!(U0LSR & U0LSR_THRE));
      U0THR = ch;
      }
  };

// Set up default serial and debug output stream
static LPCSerial lpcSerial = LPCSerial();
Serial *serial = &lpcSerial;
OutputStream *debug = &lpcSerial;

