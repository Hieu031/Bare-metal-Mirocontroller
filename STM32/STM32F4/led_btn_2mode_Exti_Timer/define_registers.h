#ifndef DEFINE_REGISTERS_H
#define DEFINE_REGISTERS_H

#include <stdint.h>

/* ===== Base address ======== */
#define PERIPH_BASE         0x40000000UL
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE     (PERIPH_BASE + 0x00000000UL)
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x00010000UL)

#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOD_BASE      (AHB1PERIPH_BASE + 0x0C00UL)
#define SYSCFG_BASE     (APB2PERIPH_BASE + 0x3800UL)
#define EXTI_BASE       (APB2PERIPH_BASE + 0x3C00UL)
#define TIM2_BASE       (APB1PERIPH_BASE + 0x0000UL)
#define NVIC_ISER_BASE  0xE000E100UL

/* ===== RCC ====== */
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))

/* ====== GPIO ======= */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_typeDef;

#define GPIOA   ((GPIO_typeDef *) GPIOA_BASE)
#define GPIOD   ((GPIO_typeDef *) GPIOD_BASE)

/* ==== SYSCFG ===== */
typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[2]; 
} SYSCFG_TypeDef;

#define SYSCFG  ((SYSCFG_TypeDef *) SYSCFG_BASE);

/* ===== EXTI ===== */
typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

#define EXTI    ((EXTI_TypeDef *) EXTI_BASE)

/* ===== TIM2 ===== */
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIM_TypeDef;

#define TIM2 ((TIM_TypeDef *)TIM2_BASE)

/* ==== NVIC ==== */
#define NVIC_ISER0 (*(volatile uint32_t *)(NVIC_ISER_BASE + 0x00))
#define NVIC_ISER1 (*(volatile uint32_t *)(NVIC_ISER_BASE + 0x04))

/* ==== Helper ==== */
#define BIT(x) (1U << (x))

#endif /* DEFINE_REGISTERS_H */