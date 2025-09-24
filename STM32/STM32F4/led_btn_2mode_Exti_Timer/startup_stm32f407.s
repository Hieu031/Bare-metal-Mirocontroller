.syntax unified
.cpu cortex-m4
.thumb

.global _estack
.global Reset_Handler

/* Vector Table: Must be placed at start of FLASH (.isr_vector section) */
.section .isr_vector, "a", %progbits
.word   _estack             /* Initial stack pointer (top of RAM) */
.word   Reset_Handler       /* Reset Handler (entry point) */
.word   NMI_Handler         /* NMI Handler */
.word   HardFault_Handler   /* Hard Fault Handler */
.word   MemManage_Handler   /* Memory Management Fault Handler */
.word   BusFault_Handler    /* Bus Fault Handler */
.word   UsageFault_Handler  /* Usage Fault Handler */
.word   0                   /* Reserved */
.word   0                   /* Reserved */
.word   0                   /* Reserved */
.word   0                   /* Reserved */
.word   SVC_Handler         /* SVCall Handler */
.word   DebugMon_Handler    /* Debug Monitor Handler */
.word   0                   /* Reserved */
.word   PendSV_Handler      /* PendSV Handler */
.word   SysTick_Handler     /* SysTick Handler */
.word   EXTI0_IRQHandler    /* External interrupt 0 */
.word   EXTI1_IRQHandler    /* External interrupt 1 */
.word   TIM2_IRQHandler     /* Timer 2 interrupt */
/* More IRQ handlers can be added here if needed */

.section .text

/* Default handlers (loop forever) */
NMI_Handler:        b .
HardFault_Handler:  b .
MemManage_Handler:  b .
BusFault_Handler:   b .
UsageFault_Handler: b .
SVC_Handler:        b .
DebugMon_Handler:   b .
PendSV_Handler:     b .
SysTick_Handler:    b .
EXTI0_IRQHandler:   b .
EXTI1_IRQHandler:   b .
TIM2_IRQHandler:    b .
