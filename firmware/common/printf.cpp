/*---------------------------------------------------------------------------*
* SensNode string formatting support
*----------------------------------------------------------------------------*
* 19-Nov-2014 ShaneG
*
* Implement the portable string formatting functions.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

//---------------------------------------------------------------------------
// Helper functions
//---------------------------------------------------------------------------

/** Write a sequence of bytes to the ouput stream
 *
 * @param cszString pointer to the buffer containing the data to write
 * @param length the number of bytes to write. If this is less than zero
 *               the string is assumed to be NUL terminated.
 *
 * @return the number of bytes written. This may be less than requested.
 */
static int write(FN_PUTC pfnPutC, void *pData, const char *cszString, int length) {
  int index, count = 0;
  if(length < 0) {
    for(index=0; cszString[index]; index++) {
      if((*pfnPutC)(cszString[index], pData))
        count++;
      }
    }
  else {
    for(index=0; index<length; index++) {
      if((*pfnPutC)(cszString[index], pData))
        count++;
      }
    }
  return count;
  }

/** Write a numeric value in hex
 *
 * @param value the value to write
 * @param digits the minimum number of digits to use.
 *
 * @return the number of characters written
 */
static int writeHex(FN_PUTC pfnPutC, void *pData, uint32_t value, int digits) {
  // TODO: Implement this
  return 0;
  }

/** Write a numeric value in decimal
 *
 * @param value the value to write
 *
 * @return the number of characters written
 */
static int writeInt(FN_PUTC pfnPutC, void *pData, uint32_t value) {
  bool emit = false;
  // Special case for 0
  if(value==0) {
    (*pfnPutC)('0', pData);
    return 1;
    }
  // Emit the value, skip leading zeros
  int written = 0;
  for(uint16_t divisor = 10000; divisor > 0; divisor = divisor / 10) {
    uint8_t digit = value / divisor;
    value = value % divisor;
    if((digit>0)||emit) {
      if((*pfnPutC)('0' + digit, pData))
        written++;
      emit = true;
      }
    }
  return written;
  }

/** Do the actual formatting
 *
 * This function uses the current two characters of the input string to
 * determine what to print.
 *
 * @param pStream pointer to the output stream
 * @param ch1 the current character of the format string
 * @param ch2 the next character of the format string
 * @param args the argument list containing the embedded items
 *
 * @return true if both characters should be skipped, false if we only need
 *              to move ahead by one.
 */
static bool _printf(FN_PUTC pfnPutC, void *pData, int& written, char ch1, char ch2, va_list args) {
  bool skip = true;
  // Fail fast
  if(ch1=='%') {
    // Use the second character to determine what is requested
    if((ch2=='%')||(ch2=='\0')) {
      if((*pfnPutC)('%', pData))
        written++;
      }
    else if(ch2=='c') {
      if((*pfnPutC)(va_arg(args, int), pData))
        written++;
      }
    else {
      switch(ch2) {
        case 'u':
          written += writeInt(pfnPutC, pData, va_arg(args, unsigned int));
          break;
        case 'x':
          written += writeHex(pfnPutC, pData, va_arg(args, unsigned int), 8);
          break;
        case 's':
          written += write(pfnPutC, pData, va_arg(args, char *), -1);
          break;
        default:
          if((*pfnPutC)(ch2, pData))
            written++;
          break;
        }
      }
    }
  else {
    if((*pfnPutC)(ch1, pData))
      written++;
    skip = false;
    }
  return skip;
  }

/** Structure maintaining information about an output buffer
 */
struct SPRINTF_DATA {
  char *m_szOutput; //! Buffer to contain the output
  int   m_length;   //! Size of output buffer
  int   m_index;    //! Index of next character to write
  };

/** Write a single character to a buffer
 *
 * @param ch the character to write.
 *
 * @return true if the write was successful
 */
static bool sprintf_putc(char ch, SPRINTF_DATA *pData) {
  if(pData->m_index==pData->m_length)
    return false;
  pData->m_szOutput[pData->m_index++] = ch;
  return true;
  }

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------

/** Generate a formatted string
 *
 * This function is used to generate strings from a format. This implementation
 * uses a user provided function pointer to output the data as it is generated.
 *
 * The function supports a subset of the 'printf' string formatting syntax.
 * Allowable insertion types are:
 *
 *  %% - Display a % character. There should be no entry in the variable
 *       argument list for this entry.
 *  %u - Display an unsigned integer in decimal. The matching argument may
 *       be any 16 bit value.
 *  %U - Display an unsigned integer in decimal. The matching argument may
 *       be any 32 bit value.
 *  %x - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 16 bit value.
 *  %X - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 32 bit value.
 *  %c - Display a single ASCII character. The matching argument may be any 8
 *       bit value.
 *  %s - Display a NUL terminated string from RAM. The matching argument must
 *       be a pointer to a RAM location.
 *
 * @param pfnPutC pointer the character output function
 * @param pData pointer to a user provided data block. This is passed to the
 *              character output function with each character.
 * @param cszFormat pointer to a nul terminated format string.
 * @param args the variadic argument list.
 *
 * @return the number of characters generated.
 */
int vprintf(FN_PUTC pfnPutC, void *pData, const char *cszString, va_list args) {
  char ch1, ch2 = *cszString;
  int written = 0;
  for(int index=1; ch2!='\0'; index++) {
    ch1 = ch2;
    ch2 = cszString[index];
    if(_printf(pfnPutC, pData, written, ch1, ch2, args)) {
      // Move ahead an extra character so we wind up jumping by two
      ch1 = ch2;
      ch2 = cszString[++index];
      }
    }
  return written;
  }

/** Print a formatted string
 *
 * This function supports a subset of the 'printf' string formatting syntax.
 * Allowable insertion types are:
 *
 *  %% - Display a % character. There should be no entry in the variable
 *       argument list for this entry.
 *  %u - Display an unsigned integer in decimal. The matching argument may
 *       be any 32 bit value.
 *  %x - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 32 bit value.
 *  %b - Display a single byte in hexadecimal.
 *  %c - Display a single ASCII character. The matching argument may be any 8
 *       bit value.
 *  %s - Display a NUL terminated string from RAM. The matching argument must
 *       be a pointer to a RAM location.
 *
 * @param szBuffer pointer to the buffer to place the string in
 * @param length the size of the buffer.
 * @param cszString pointer to a nul terminated format string in RAM.
 *
 * @return the number of characters (excluding the terminating NUL) that
 *         were written. If this value is equal to length the resulting
 *         string will not be NUL terminated.
 */
int sprintf(char *szBuffer, int length, const char *cszString, ...) {
  va_list args;
  va_start(args, cszString);
  if(length<=0)
    return length;
  SPRINTF_DATA data;
  data.m_szOutput = szBuffer;
  data.m_length = length;
  data.m_index = 0;
  int result = vprintf((FN_PUTC)&sprintf_putc, &data, cszString, args);
  va_end(args);
  // Add a terminating NUL if there is room
  if(data.m_index!=data.m_length)
    data.m_szOutput[data.m_index] = '\0';
  return result;
  }

