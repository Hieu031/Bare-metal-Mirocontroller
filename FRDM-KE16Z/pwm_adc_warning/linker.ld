MEMORY
{
    FLASH   (rx)    : ORIGIN = 0x00000000, LENGTH = 256K
    RAM     (rwx)   : ORIGIN = 0x1FFFF000, LENGTH = 32K
}

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        *(.text)
        *(.rodata*)
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        *(.data*)
    } > RAM

    .bss :
    {
        *(.bss)
        *(COMMON)
    } > RAM

}
