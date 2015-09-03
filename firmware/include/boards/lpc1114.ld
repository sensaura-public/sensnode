/*--------------------------------------------------------------------------*
* Linker script for LPC1114
*---------------------------------------------------------------------------*
* 03-Sep-2015
*
* Based on original code by Frank Duignan, updated to support C++ static
* initialisers.
*
* References:
*   http://www.linuxselfhelp.com/gnu/ld/html_chapter/ld_toc.html
*   http://www.embedded.com/design/mcus-processors-and-socs/4026080/Building-Bare-Metal-ARM-Systems-with-GNU-Part-3
*--------------------------------------------------------------------------*/

/** Memory layout for LPC1114
 */
MEMORY
{
  flash : org = 0x00000000, len = 32k
  ram   : org = 0x10000000, len = 4k
}

/** Define linker sections
 */
SECTIONS
{
  /* Layout flash first with vectors at the beginning */
  . = ORIGIN(flash);
  .text : {
    KEEP(*(.vectors)); /* The interrupt vectors */
    *(.text);
    } >flash
  . = ALIGN(4);
  .init_array : {
    __init_array_start = .;
    KEEP (*(.init_array*))
    __init_array_end = .;
    } >flash
  . = ORIGIN(ram);
  /* Initialised data. Stored in flash and copied to RAM */
  .data : {
    INIT_DATA_VALUES = LOADADDR(.data);
    INIT_DATA_START = .;
      *(.data);
    INIT_DATA_END = .;
  } >ram AT>flash
  /* Uninitialised data. Startup code sets all to zero */
  BSS_START = .;
  .bss : {
      *(.bss);
  } > ram
  BSS_END = .;
}
