#include "define_registers.h"

#define BTN1    0U
#define BTN2    1U
#define LED1    12U
#define LED2    13U
#define LED3    14U

/* 0 = Idle, 1 = Blink, 2 = Chase */
volatile uint8_t mode = 0; 

/* ====== EXTI ISR for PA0 (BTN) ======= */
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & BIT(0)) {
        mode = 1; /* Blink mode */
        EXTI->PR |= BIT(0); /* Clear pending */
    }
}

/* ======= EXTI ISR for PA1 (BTN2) ============= */
void EXTI1_IRQHandler(void) {
    mode = 2; /* chase led */
    EXTI->PR |= BIT(1);
}

/* ======== TIM2 ISR (200ms) =============== */
void TIM2_IRQHandler(void) {
    if (TIM2->SR & BIT(0)) {
        TIM2->SR &= ~BIT(0); /* Clear UIF */

        if (mode == 1) {
            static uint8_t state = 0;
            if (state) {
                GPIOD->ODR &= ~(BIT(12) | BIT(13) | BIT(14)); /* Toggle bit to blink led */
            }
            else
            {
                GPIOD->ODR |= (BIT(12) | BIT(13) | BIT(14));
            }
            state ^= 1;
        }
        else if (mode == 2) {
            static uint8_t pos = 0;
            GPIOD->ODR &= ~(BIT(12) | BIT(13) | BIT(14));
            GPIOD->ODR |= BIT12(12 + pos);
            pos = (pos + 1) % 3;
        }
    }
}

int main(void) {
    /* Enable clocks */
    RCC_AHB1ENR |= BIT(0); /* GPIOA */
    RCC_AHB1ENR |= BIT(3); /* GPIOD */
    RCC_APB2ENR |= BIT(14); /* SYSCFG */
    RCC_APB1ENR |= BIT(0); /* TIM2 */

    /* Configure PA0, PA1 as input (buttons) */
    GPIOA->MODER &= ~((3U << (0*2)) | (3U <<(1*2)));
    GPIOA->PUPDR |= (1U << (0*2)) | (1u << (1*2)); /* Pull up */

    /* Configure PD12, PD13, PD14 as output (LEDs) */
    GPIOD->MODER |= (1U << (12*2)) | (1U << (13*2)) | (1U << (14*2));

    /* Configure TIM2: 200ms interval */
    TIM2->PSC = 16000 - 1;  /* 16MHz / 16000 = 1kHz */
    TIM2->ARR = 200 - 1;    /* 200ms */
    TIM2->DIER |= BIT(0);   /* Update interrupt enbale */
    TIM2->CR1 |= BIT(0);    /* Counter enable */
    
    /* Enable TIM2 interrupt in NVIC (IRQ28) */
    NVIC_ISER0 |= BIT(28);

    while (1) {
        /* Handler task but here, everything handler in ITRQ */
    }
}