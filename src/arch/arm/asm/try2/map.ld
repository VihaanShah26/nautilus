ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
  RAM   (rwx): ORIGIN = 0x20000000, LENGTH =  64K
}

SECTIONS
{
  /* Place vector table and code at 0x0000_0000 */
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
  } > FLASH

  /* Define the top of the stack here */
  . = ALIGN(8);
  _estack = ORIGIN(RAM) + LENGTH(RAM);
}
