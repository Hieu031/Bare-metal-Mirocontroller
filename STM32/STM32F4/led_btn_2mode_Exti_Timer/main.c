#include "define_registers.h"

#define BTN1_PIN    0U
#define BTN2_PIN    1U
#define LED1_PIN    12U
#define LED2_PIN    13U
#define LED3_PIN    14U

/* Mode led */
#define MODE_IDLE   0   /* Mode intially (all led off) */
#define MODE_BLINK  1   /* Mode blink led */
#define MODE_CHASE  2   /* Mode chase led */

volatile uint8_t mode = MODE_IDLE;

/* ====== EXTI ISR for PA0 (BTN) ======= */
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & BIT(BTN1_PIN)) {
        mode = 1; /* Blink mode */
        EXTI->PR |= BIT(0); /* Clear pending */
    }
}

/* ======= EXTI ISR for PA1 (BTN2) ============= */
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & BIT(BTN2_PIN)) {
        mode = 2; /* chase led */
        EXTI->PR |= BIT(1);
    }
}

/* ======== TIM2 ISR (200ms) =============== */
void TIM2_IRQHandler(void) {
    if (TIM2->SR & BIT(0)) {
        TIM2->SR &= ~BIT(0); /* Clear update flag */

        if (mode == MODE_IDLE) {
            /* all led off */
            GPIOD->ODR &= ~(BIT(LED1_PIN) | BIT(LED2_PIN) | BIT(LED3_PIN));
        }
        else if (mode == MODE_BLINK) {
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
        else if (mode == MODE_CHASE) {
            static uint8_t pos = 0;
            GPIOD->ODR &= ~(BIT(12) | BIT(13) | BIT(14));
            GPIOD->ODR |= BIT(12 + pos);
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
    GPIOD->MODER &= ~((3U << (12*2)) | (3U << (13*2)) | (3U << (14*2))); 
    GPIOD->MODER |= (1U << (12*2)) | (1U << (13*2)) | (1U << (14*2));

    /* Map PA0, PA1 -> EXTI0, EXTI1 */
    SYSCFG->EXTICR[0] &= ~((0xF << 0) | (0xF << 4)); // PA = 0000

    /* Cấu hình EXTI cho PA0, PA1 */
    EXTI->IMR  |= BIT(BTN1_PIN) | BIT(BTN2_PIN);   // unmask
    EXTI->RTSR |= BIT(BTN1_PIN) | BIT(BTN2_PIN);   // rising edge

    /* Enable NVIC cho EXTI0, EXTI1 */
    NVIC_ISER0 |= BIT(6);  // EXTI0_IRQn
    NVIC_ISER0 |= BIT(7);  // EXTI1_IRQn

    /* Configure TIM2: 200ms interval */
    TIM2->PSC = 16000 - 1;  /* 16MHz / 16000 = 1kHz */
    TIM2->ARR = 200 - 1;    /* 200ms */
    TIM2->DIER |= BIT(0);   /* Update interrupt enbale */
    TIM2->CR1 |= BIT(0);    /* Counter enable */
    
    /* Enable TIM2 interrupt in NVIC (IRQ28) */
    NVIC_ISER0 |= BIT(28);

    /* Idle mode ngay từ đầu -> tắt hết LED */
    GPIOD->ODR &= ~(BIT(LED1_PIN) | BIT(LED2_PIN) | BIT(LED3_PIN));

    while (1) {
        /* Handler task but here, everything handler in ITRQ */
    }
}