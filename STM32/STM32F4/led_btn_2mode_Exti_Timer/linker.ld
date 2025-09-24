ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
  /*
    FLASH memory region:
    - Start address: 0x8000000
    - Size: 1024 KB (1 MB)
    - Attributes: r = read, x = execute (code can run from FLASH)
  */
  RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 128K
  /*
    RAM memory region:
    - Start address: 0x20000000
    - Size: 128 KB
    - Attributes: r = read, w = write, x = execute
      (in practice, code usually runs from FLASH, but linker allows execute in RAM too)
  */
}

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))   /* Keep vector table */
  } > FLASH

  .text :
  {
    *(.text*)               /* Code */
    *(.rodata*)             /* Read-only data */
  } > FLASH

  .data : AT (LOADADDR(.text) + SIZEOF(.text))
  {
    _sdata = .;             /* Start of .data in RAM */
    *(.data*)               /* Initialized variables */
    _edata = .;             /* End of .data in RAM */
  } > RAM
  _sidata = LOADADDR(.data); /* Load address of .data in FLASH */

  .bss :
  {
    _sbss = .;              /* Start of .bss */
    *(.bss*)                /* Uninitialized variables */
    *(COMMON)               /* Common symbols */
    _ebss = .;              /* End of .bss */
  } > RAM
}