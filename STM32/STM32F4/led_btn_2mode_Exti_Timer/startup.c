#include <stdint.h>

/* 
   These symbols are defined in the linker script (.ld file).
   They mark the start and end of memory regions.
*/
extern uint32_t _sidata;  /* Start address of .data in FLASH (load address) */
extern uint32_t _sdata;   /* Start address of .data in RAM */
extern uint32_t _edata;   /* End address of .data in RAM */
extern uint32_t _sbss;    /* Start address of .bss in RAM */
extern uint32_t _ebss;    /* End address of .bss in RAM */

/* Forward declaration of main() */
int main(void);

/* Reset Handler: This runs after MCU reset */
void Reset_Handler(void) {
    uint32_t *src, *dst;

    /* Copy .data section from FLASH to RAM */
    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Zero initialize the .bss section in RAM */
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* Call main() */
    main();

    /* If main() ever returns, loop forever */
    while (1);
}
