/*--------------------------------------------------------------------------*
* Startup/Initialisation code for the LPC1114
*---------------------------------------------------------------------------*
* 03-Sep-2015 ShaneG
*
* Provides system startup and the interupt vector table. Based on code
* by Frank Duignan (http://eleceng.dit.ie/frank).
*--------------------------------------------------------------------------*/
#include <platform.h>

// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;

//---------------------------------------------------------------------------
// Interrupt vectors
//
// The 'vectors' section is placed at the beginning of flash by the linker
// script.
//---------------------------------------------------------------------------

/** The interrupt vector table itself.
 */
const void * Vectors[] __attribute__((section(".vectors"))) = {
  (void *)0x10001000,      /* Top of stack */
  systemInit,              /* Reset Handler */
  defaultInterruptHandler, /* NMI */
  defaultInterruptHandler, /* Hard Fault */
  0,	                   /* Reserved */
  0,                       /* Reserved */
  0,                       /* Reserved */
  0,                       /* Reserved */
  0,                       /* Reserved */
  0,                       /* Reserved */
  0,                       /* Reserved */
  defaultInterruptHandler, /* SVC */
  0,                       /* Reserved */
  0,                       /* Reserved */
  defaultInterruptHandler, /* PendSV */
  defaultInterruptHandler, /* SysTick */
  /* External interrupt handlers follow */
  defaultInterruptHandler, /* PIO0_0 */
  defaultInterruptHandler, /* PIO0_1 */
  defaultInterruptHandler, /* PIO0_2 */
  defaultInterruptHandler, /* PIO0_3 */
  defaultInterruptHandler, /* PIO0_4 */
  defaultInterruptHandler, /* PIO0_5 */
  defaultInterruptHandler, /* PIO0_6 */
  defaultInterruptHandler, /* PIO0_7 */
  defaultInterruptHandler, /* PIO0_8 */
  defaultInterruptHandler, /* PIO0_9 */
  defaultInterruptHandler, /* PIO0_10 */
  defaultInterruptHandler, /* PIO0_11 */
  defaultInterruptHandler, /* PIO1_0 */
  defaultInterruptHandler, /* C_CAN */
  defaultInterruptHandler, /* SSP1 */
  defaultInterruptHandler, /* I2C */
  defaultInterruptHandler, /* CT16B0 */
  defaultInterruptHandler, /* CT16B1 */
  defaultInterruptHandler, /* CT32B0 */
  defaultInterruptHandler, /* CT32B1 */
  defaultInterruptHandler, /* SSP0 */
  defaultInterruptHandler, /* UART */
  defaultInterruptHandler, /* RESERVED */
  defaultInterruptHandler, /* RESERVED */
  defaultInterruptHandler, /* ADC */
  defaultInterruptHandler, /* WDT */
  defaultInterruptHandler, /* BOD */
  defaultInterruptHandler, /* RESERVED */
  defaultInterruptHandler, /* PIO3 */
  defaultInterruptHandler, /* PIO2 */
  defaultInterruptHandler, /* PIO1 */
  defaultInterruptHandler  /* PIO0 */
  };

//---------------------------------------------------------------------------
// System initialisation
//
// These set of functions initialise the environment for the C/C++ library,
// set up the PLL and system clock and any interrupts that are required.
//---------------------------------------------------------------------------

/** Initialise the system clock and PLL
 */
static void initClock() {
  // This function sets the main clock to the PLL
  // The PLL input is the built in 12MHz RC oscillator
  // This is multiplied up to 48MHz for the main clock
  // MSEL = 3, PSEL = 1 see page 51 of UM10398 user manual
  SYSPLLCLKSEL = 0; // select internal RC oscillator
  SYSPLLCTRL = (3 << 0) | (1 << 5); // set divisors/multipliers
  PDRUNCFG &= ~BIT7; // Power up the PLL.
  SYSPLLCLKUEN = 1; // inform PLL of update
  // TODO: Wait for stabilisation?
  MAINCLKSEL = 3; // Use PLL as main clock
  MAINCLKUEN = 1; // Inform core of clock update
  // Set up the system tick timer. We don't use interrupts, we
  // just want the time to increment on the system clock.
  SYST_CSR = BIT0 | BIT2;
  SYST_RVR = TICKS_MAX;
  SYST_CVR = 0;
  // Set up clock sources needed
  SYSAHBCLKCTRL &= ~(BIT11);
  SYSAHBCLKCTRL |= (BIT13 | BIT16); // ADC and IOCON
  }

/** Main initialisation function
 */
void systemInit() {
  // Global and static data initialisation
  unsigned char *src;
  unsigned char *dest;
  unsigned len;
  src = &INIT_DATA_VALUES;
  dest = &INIT_DATA_START;
  len = &INIT_DATA_END-&INIT_DATA_START;
  while(len--)
    *dest++ = *src++;
  // zero out the uninitialized global/static variables
  dest = &BSS_START;
  len = &BSS_END - &BSS_START;
  while (len--)
    *dest++ = 0;
  // Initialise the system clock and system tick configuration
  initClock();
  // Enter the main function
  main();
  }

