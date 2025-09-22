#ifndef DEFINE_REGISTERS_H
#define DEFINE_REGISTERS_H

#include <stdint.h>

/* ================= BASE ADDRESSES ================= */
#define PCC_BASE        (0x40065000u)   
#define GPIOA_BASE      (0x48000000u)
#define GPIOB_BASE      (0x48000400u)
#define GPIOC_BASE      (0x48000800u)
#define GPIOD_BASE      (0x48000C00u)
#define GPIOE_BASE      (0x48001000u)
#define FTM0_BASE       (0x40038000u)
#define ADC0_BASE       (0x4003B000u)
#define LPUART0_BASE    (0x40042000u)
#define LPUART1_BASE    (0x40043000u)

/* ================= GPIO ================= */
typedef struct {
    volatile uint32_t PDOR;   // Data Output Register
    volatile uint32_t PSOR;   // Set Output Register
    volatile uint32_t PCOR;   // Clear Output Register
    volatile uint32_t PTOR;   // Toggle Output Register
    volatile uint32_t PDIR;   // Data Input Register
    volatile uint32_t PDDR;   // Data Direction Register
} GPIO_Type;

#define GPIOA ((GPIO_Type *)GPIOA_BASE)
#define GPIOB ((GPIO_Type *)GPIOB_BASE)
#define GPIOC ((GPIO_Type *)GPIOC_BASE)
#define GPIOD ((GPIO_Type *)GPIOD_BASE)
#define GPIOE ((GPIO_Type *)GPIOE_BASE)

/* ================= PCC (Peripheral Clock Control) ================= */
typedef struct {
    volatile uint32_t PCCn[128];   // mỗi module 1 clock gate
} PCC_Type;

#define PCC ((PCC_Type *)PCC_BASE)

/* PCC index (KE16Z RM, bảng PCC) */
#define PCC_FTM0_INDEX   (38)
#define PCC_ADC0_INDEX   (40)
#define PCC_LPUART0_INDEX (42)
#define PCC_LPUART1_INDEX (43)
#define PCC_PORTA_INDEX  (73)
#define PCC_PORTB_INDEX  (74)
#define PCC_PORTC_INDEX  (75)
#define PCC_PORTD_INDEX  (76)
#define PCC_PORTE_INDEX  (77)

/* ================= FTM (FlexTimer Module) ================= */
typedef struct {
    volatile uint32_t SC;        // Status and Control
    volatile uint32_t CNT;       // Counter
    volatile uint32_t MOD;       // Modulo
    volatile uint32_t CnSC[8];   // Channel Status and Control
    volatile uint32_t CnV[8];    // Channel Value
    volatile uint32_t CNTIN;     
    volatile uint32_t STATUS;
    volatile uint32_t MODE;
    volatile uint32_t SYNC;
    volatile uint32_t OUTINIT;
    volatile uint32_t OUTMASK;
    volatile uint32_t COMBINE;
    volatile uint32_t DEADTIME;
    volatile uint32_t EXTTRIG;
    volatile uint32_t POL;
    volatile uint32_t FMS;
    volatile uint32_t FILTER;
    volatile uint32_t FLTCTRL;
    volatile uint32_t QDCTRL;
    volatile uint32_t CONF;
    volatile uint32_t FLTPOL;
    volatile uint32_t SYNCONF;
    volatile uint32_t INVCTRL;
    volatile uint32_t SWOCTRL;
    volatile uint32_t PWMLOAD;
} FTM_Type;

#define FTM0 ((FTM_Type *)FTM0_BASE)

/* ================= ADC ================= */
typedef struct {
    volatile uint32_t SC1[2];  // Status and Control 1
    volatile uint32_t CFG1;    // Configuration 1
    volatile uint32_t CFG2;    // Configuration 2
    volatile uint32_t R[2];    // Result registers
    volatile uint32_t CV1;     
    volatile uint32_t CV2;
    volatile uint32_t SC2;     
    volatile uint32_t SC3;
} ADC_Type;

#define ADC0 ((ADC_Type *)ADC0_BASE)

/* ================= LPUART ================= */
typedef struct {
    volatile uint32_t BAUD;    // Baud Rate
    volatile uint32_t STAT;    // Status
    volatile uint32_t CTRL;    // Control
    volatile uint32_t DATA;    // Data Register
    volatile uint32_t MATCH;   // Match Address
    volatile uint32_t MODIR;   // Modem IrDA
    volatile uint32_t FIFO;    // FIFO control
    volatile uint32_t WATER;   // Watermark
} LPUART_Type;

#define LPUART0 ((LPUART_Type *)LPUART0_BASE)
#define LPUART1 ((LPUART_Type *)LPUART1_BASE)

/* ================= BIT MASKS HELPER ================= */
#define BIT(x) (1U << (x))

#endif // DEFINE_REGISTERS_H
