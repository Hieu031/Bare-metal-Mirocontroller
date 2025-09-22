.syxtax unified
.cpu cortex-m4
.thumb

.global _estack
.global Reset_Handler

.word _estack
.global Reset_Handler

.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler
.word BusFault_Handler
.word UsageFault_Handler
.word 0,0,0,0
.word SVC_Handler
.word DebugMon_Handler
.word 0
.word PendSV_Handler
.word SysTick_Handler
.word EXTI0_IRQHandler   /* IRQ6 */
.word EXTI1_IRQHandler   /* IRQ7 */
.word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.word TIM2_IRQHandler    /* IRQ28 */

.section .text
Reset_Handler:
    bl main
    b .

NMI_Handler:        b .
HardFault_Handler:  b .
MemManage_Handler:  b .
BusFault_Handler:   b .
UsageFault_Handler: b .
SVC_Handler:        b .
DebugMon_Handler:   b .
PendSV_Handler:     b .
SysTick_Handler:    b .