/*---------------------------------------------------------------------------*
* SensNode - Common serial port functions
*----------------------------------------------------------------------------*
* 29-Oct-2015 ShaneG
*
* Implements the common (not platform specific) serial port functions.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

/** Write a single character to the serial port
 *
 * @param ch the character to write.
 *
 * @return true if the write was successful
 */
static bool serial_putc(char ch, void *pData) {
  serialWrite(ch);
  return true;
  }

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------

/** Print a sequence of characters to the serial port.
 *
 * This function may be used to print a NUL terminated string (if the length
 * parameter < 0) or a fixed sequence of bytes (if length >= 0).
 *
 * The function is blocking and will not return until all characters have been
 * transmitted.
 *
 * @param cszString pointer to a buffer containing the data to be transmitted.
 * @param length the number of bytes to send. If length < 0 the buffer is treated
 *               as a NUL terminated string and sending will terminate with the
 *               first 0 byte.
 *
 * @return the number of bytes sent.
 */
int serialPrint(const char *cszString, int length) {
  if(cszString==NULL)
    cszString = "(null)";
  if(length<0) {
    length = 0;
    while(*cszString) {
      serialWrite(*cszString);
      cszString++;
      length++;
      }
    }
  else {
    for(int i=0; i<length; i++)
      serialWrite(cszString[i]);
    }
  return length;
  }

/** Print a formatted string to the serial port.
 *
 * This function utilises the @see vformat function to transmit a formatted
 * string to the serial port.
 *
 * The function is blocking and will not return until all characters have been
 * transmitted.
 *
 * @param cszString the format string to use to generate the output.
 *
 * @return the number of bytes sent.
 */
int serialFormat(const char *cszString, ...) {
  va_list args;
  va_start(args, cszString);
  int result = vformat((FN_PUTC)&serial_putc, NULL, cszString, args);
  va_end(args);
  return result;
  }

