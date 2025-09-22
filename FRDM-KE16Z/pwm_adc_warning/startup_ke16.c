#include <stdint.h>

/* Stack top (at the end of RAM, 16KB RAM @0x1FFFF000) */
#define STACK_TOP       0x20004000

/* Prototype */
void Reset_Handler(void);
void Default_Handler(void);

/* Vector table */
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void)) STACK_TOP, /* Initial stack pointer */
    Reset_Handler,              /* Reset Handler */
    Default_Handler,            /* NMI */
    Default_Handler,            /* HardFault */
};

/* Reset handler */
extern int main(void);
void Reset_Handler(void){
    main();
} 

/* Default handler */
void Default_Handler(void) {
    while (1);
}