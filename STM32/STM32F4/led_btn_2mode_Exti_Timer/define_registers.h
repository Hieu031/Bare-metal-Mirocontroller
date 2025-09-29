#ifndef DEFINE_REGISTERS_H
#define DEFINE_REGISTERS_H

#include <stdint.h> /* Standard libarary C to define uint32_t, help code more portable */

/* ===== Base address ======== */
#define PERIPH_BASE         0x40000000UL                    /* Address start of memory layout */
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x00020000UL)    /* Address this register help enable clock GPIOA, GPIOD */
#define APB1PERIPH_BASE     (PERIPH_BASE + 0x00000000UL)    /* This enable TIM2 */
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x00010000UL)    /* This enable EXTI, SYSCFG */

#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800UL)        /* Reset and Clock Control address base */
#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000UL)        /* GPIOA address base */
#define GPIOD_BASE      (AHB1PERIPH_BASE + 0x0C00UL)        /* GPIOD address base */
#define SYSCFG_BASE     (APB2PERIPH_BASE + 0x3800UL)        /* SYSCFG address base */
#define EXTI_BASE       (APB2PERIPH_BASE + 0x3C00UL)        /* EXTI address base */
#define TIM2_BASE       (APB1PERIPH_BASE + 0x0000UL)        /* TIMER2 address base */
#define NVIC_ISER_BASE  0xE000E100UL                        /* Address of NVIC - get from Cortex-M4 user guide */

/* ===== RCC ====== */
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))   /* Enable clock for GPIOA, GPIOD, DMA,...  */
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))   /* Enable clock for TIM2, USART2,... */
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))   /* Enable clock for SYSCFG, USART1,... */

/* ====== GPIO ======= */
/* Struct register of 1 GPIO (follow RM0090, each register offset 4 byte) */
typedef struct {
    volatile uint32_t MODER;    /* Choose mode for each pin (input/output/alt/analog) */
    volatile uint32_t OTYPER;   /* Type output (push-pull / open-drain) */
    volatile uint32_t OSPEEDR;  /* Output speed (low/medium/high/very high) */
    volatile uint32_t PUPDR;    /* Choose pull-up/pull-down */
    volatile uint32_t IDR;      /* Read data pin */
    volatile uint32_t ODR;      /* Write data pin */
    volatile uint32_t BSRR;     /* Set/Reset pin via bit */
    volatile uint32_t LCKR;     /* Lock register: lock configure pin */
    volatile uint32_t AFRL;     /* Alternate Function Low Register (pin 0->7) */
    volatile uint32_t AFRH;     /* Alternate Function High register (pin 8->15) */
} GPIO_typeDef;

/* Pointer point to address base of GPIO */
#define GPIOA   ((GPIO_typeDef *) GPIOA_BASE)
#define GPIOD   ((GPIO_typeDef *) GPIOD_BASE)

/* ==== SYSCFG ===== */
/* SYSCFG helps route EXTI external interrupts to specific pins   */
typedef struct {
    volatile uint32_t MEMRMP;       /* Memory remap */
    volatile uint32_t PMC;          /* Peripheral mode configuration */
    volatile uint32_t EXTICR[4];    /* External interrupt configuration (EXTI0-3 in EXTICR[0], EXTI4-7 in EXTICR[1]) */
    uint32_t RESERVED[2];
    volatile uint32_t CMPCR;
} SYSCFG_TypeDef;

/* pointer to pointer address base to use struct above */
#define SYSCFG  ((SYSCFG_TypeDef *) SYSCFG_BASE);

/* ===== EXTI ===== */
/* Register of External Interrupt Manage */
typedef struct {
    volatile uint32_t IMR;      /* Interrupt mask register */
    volatile uint32_t EMR;      /* Event mask register */
    volatile uint32_t RTSR;     /* Rising trigger selection (up edge) */
    volatile uint32_t FTSR;     /* Falling trigger selection (down edge) */
    volatile uint32_t SWIER;    /* Software interrupt event register */
    volatile uint32_t PR;       /* Pending register (write 1 to clear ) */
} EXTI_TypeDef;

/* ponter to access struct */
#define EXTI    ((EXTI_TypeDef *) EXTI_BASE)

/* ===== TIM2 ===== */
/* Register of TIM2 */
typedef struct {
    volatile uint32_t CR1;      /* Control register 1 */
    volatile uint32_t CR2;      /* Control register 2 */
    volatile uint32_t SMCR;     /* Slave mode control register */
    volatile uint32_t DIER;     /* DMA/Interrupt enable register */
    volatile uint32_t SR;       /* Status register */
    volatile uint32_t EGR;      /* Event generation register */
    volatile uint32_t CCMR1;    /* Capture/Compare mode register 1 */
    volatile uint32_t CCMR2;    /* Capture/Compare mode register 2 */
    volatile uint32_t CCER;     /* Capture/Compare enable register */
    volatile uint32_t CNT;      /* Counter value */
    volatile uint32_t PSC;      /* Presscaler */
    volatile uint32_t ARR;      /* Auto-reload register */
} TIM_TypeDef;

/* pointer access  */
#define TIM2 ((TIM_TypeDef *)TIM2_BASE)

/* ==== NVIC (Nested Vector Interrupt Controller) ==== */
/* NVIC_ISER: Interrupt Set-enable Register
   Each bit enable 1 IRQ. 
   NVIC_ISER0 manages IRQ 0-31
   NVIC_ISER1 manages IRQ 32-63
*/
#define NVIC_ISER0 (*(volatile uint32_t *)(NVIC_ISER_BASE + 0x00)) /* Set enable for IRQ 0...31 */
#define NVIC_ISER1 (*(volatile uint32_t *)(NVIC_ISER_BASE + 0x04)) /* Set enable for IRQ 32..63 */

/* ==== Helper ==== */
/* Macro BIT(x): create mask with bit x set = 1 */
#define BIT(x) (1U << (x))

#endif /* DEFINE_REGISTERS_H */