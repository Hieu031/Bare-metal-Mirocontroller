#include "device_registers.h"
#include <stdint.h>

/* ================= CONFIG ================= */
#define LED_PIN   (5)     // VD: PTB5 -> LED cảnh báo
#define MOTOR_PIN (0)     // PTD0 -> FTM0_CH0 PWM output
#define ADC_CH    (12)    // Channel 12 -> giả lập feedback từ cảm biến

/* UART Debug Config */
#define UART_BAUD (115200u)
#define UART_CLOCK (8000000u)   // 8 MHz default IRC

/* ================== Delay (thô sơ) ================== */
static void delay(volatile uint32_t t) {
    while(t--) __asm("nop");
}

/* ================== UART ================== */
void UART0_Init(void) {
    /* Enable clock */
    PCC->PCCn[PCC_LPUART0_INDEX] |= BIT(30);

    /* Reset CTRL */
    LPUART0->CTRL = 0x0;

    /* Baud rate = UART_CLOCK / (16 * SBR) */
    uint16_t sbr = (UART_CLOCK / (16 * UART_BAUD));
    LPUART0->BAUD = (sbr & 0x1FFF);

    /* Enable TX, RX */
    LPUART0->CTRL = BIT(18) | BIT(19);
}

void UART0_SendChar(char c) {
    while(!(LPUART0->STAT & BIT(23))); // TDRE
    LPUART0->DATA = c;
}

void UART0_SendString(const char *s) {
    while(*s) {
        UART0_SendChar(*s++);
    }
}

/* ================== GPIO ================== */
void GPIO_Init(void) {
    /* Enable clock for PORTB, PORTD */
    PCC->PCCn[PCC_PORTB_INDEX] |= BIT(30);
    PCC->PCCn[PCC_PORTD_INDEX] |= BIT(30);

    /* PTB5 -> GPIO output */
    GPIOB->PDDR |= BIT(LED_PIN);
}

/* ================== FTM0 (PWM) ================== */
void FTM0_Init(void) {
    PCC->PCCn[PCC_FTM0_INDEX] |= BIT(30);

    FTM0->MODE |= BIT(2); // WPDIS
    FTM0->SC = 0;         // Stop counter
    FTM0->CNTIN = 0;
    FTM0->MOD = 7999;     // PWM period = (MOD+1)/Fclk = 8000/1MHz = 8ms (~125Hz)

    /* Edge-aligned PWM, high-true pulses */
    FTM0->CnSC[0] = (BIT(5) | BIT(3));
    FTM0->CnV[0] = 0;

    /* Start with prescaler=1 */
    FTM0->SC = BIT(3);
}

void FTM0_SetDuty(uint8_t duty) {
    if(duty > 100) duty = 100;
    uint32_t value = (FTM0->MOD * duty) / 100;
    FTM0->CnV[0] = value;
}

/* ================== ADC0 ================== */
void ADC0_Init(void) {
    PCC->PCCn[PCC_ADC0_INDEX] |= BIT(30);

    /* 12-bit, bus clock */
    ADC0->CFG1 = 0x0C;
    ADC0->SC3 = 0;
}

uint16_t ADC0_Read(uint8_t channel) {
    ADC0->SC1[0] = (channel & 0x1F);
    while(!(ADC0->SC1[0] & BIT(7))); // COCO flag
    return (uint16_t)(ADC0->R[0]);
}

/* ================== MAIN ================== */
int main(void) {
    GPIO_Init();
    UART0_Init();
    FTM0_Init();
    ADC0_Init();

    UART0_SendString("FRDM-KE16Z Motor Control Demo\r\n");

    while(1) {
        /* Đọc giá trị cảm biến (ADC) */
        uint16_t adc_val = ADC0_Read(ADC_CH);
        uint8_t duty = (adc_val * 100) / 4095;

        /* Cập nhật PWM duty */
        FTM0_SetDuty(duty);

        /* Cảnh báo: nếu duty > 70% thì bật LED */
        if(duty > 70) {
            GPIOB->PSOR = BIT(LED_PIN);
        } else {
            GPIOB->PCOR = BIT(LED_PIN);
        }

        /* In giá trị ra UART */
        char buf[64];
        int len = 0;
        len = sprintf(buf, "ADC=%u Duty=%u%%\r\n", adc_val, duty);
        for(int i=0; i<len; i++) UART0_SendChar(buf[i]);

        delay(500000);
    }

    return 0;
}
