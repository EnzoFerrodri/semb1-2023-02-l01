/****************************************************************************
 * main.c
 *
 *   Authors: Daniel Pereira de Carvalho <daniel.carvalho@ufu.br>
 *            Marcelo Barros de Almeida  <marcelo.barros@ufu.br>
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

 /****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SRAM_START  0x20000000U                  /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE   (128U * 1024U)               /* Tam. SRAM STM32F411 128K */
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F411 */

#define STACK_START SRAM_END                     /* Inicio da Stack */

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

int main(void);

/* Prototipos de funcoes para as System Exceptions */

void reset_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hardfault_handler(void) __attribute__((weak, alias("default_handler")));
void memmanage_handler(void) __attribute__((weak, alias("default_handler")));
void busfault_handler(void) __attribute__((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__((weak, alias("default_handler")));
void svc_handler(void) __attribute__((weak, alias("default_handler")));
void debugmon_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));
void WWDG_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI16_PVD_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI21_TAMP_STAMP_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI22_RTC_WKUP_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream0_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream1_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream3_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream4_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream5_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream6_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream7_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void ADC_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM1_UP_TIM10_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM4_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI17_RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void EXTI18_OTG_FS_WKUP_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream7_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void SDIO_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM5_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void SPI3_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream0_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream1_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream3_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream4_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void OTG_FS_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream5_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream6_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream7_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void USART6_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void I2C3_EV_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void I2C3_ER_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void FPU_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void SPI4_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void SPI5_IRQHandler(void) __attribute__((weak, alias("default_handler")));

 /****************************************************************************
 * External Data
 ****************************************************************************/

/* Variaveis exportadas pelo linker script */

extern uint32_t _sdata;     /* Inicio da secao .data */
extern uint32_t _edata;     /* Fim da secao .data */
extern uint32_t _la_data;   /* Origem da secao .data na FLASH */

extern uint32_t _sbss;      /* Inicio da secao .bss */
extern uint32_t _ebss;      /* Fim da secao .bss */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Tabela de Vetores de Interrupção */

uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
  STACK_START,                            /* 0x0000 0000 */
  (uint32_t)reset_handler,                /* 0x0000 0004 */
  (uint32_t)nmi_handler,                  /* 0x0000 0008 */
  (uint32_t)hardfault_handler,            /* 0x0000 000c */
  (uint32_t)memmanage_handler,            /* 0x0000 0010 */
  (uint32_t)busfault_handler,             /* 0x0000 0014 */
  (uint32_t)usagefault_handler,           /* 0x0000 0018 */
  0,                                      /* 0x0000 001c */
  0,                                      /* 0x0000 0020 */
  0,                                      /* 0x0000 0024 */
  0,                                      /* 0x0000 0028 */
  (uint32_t)svc_handler,                  /* 0x0000 002c */
  (uint32_t)debugmon_handler,             /* 0x0000 0030 */
  0,                                      /* 0x0000 0034 */
  (uint32_t)pendsv_handler,               /* 0x0000 0038 */
  (uint32_t)systick_handler,              /* 0x0000 003c */
  (uint32_t)WWDG_IRQHandler,              /* 0x0000 0040 */
  (uint32_t)EXTI16_PVD_IRQHandler,        /* 0x0000 0044 */
  (uint32_t)EXTI21_TAMP_STAMP_IRQHandler, /* 0x0000 0048 */
  (uint32_t)EXTI22_RTC_WKUP_IRQHandler,   /* 0x0000 004c */
  (uint32_t)FLASH_IRQHandler,             /* 0x0000 0050 */
  (uint32_t)RCC_IRQHandler,               /* 0x0000 0054 */
  (uint32_t)EXTI0_IRQHandler,             /* 0x0000 0058 */
  (uint32_t)EXTI1_IRQHandler,             /* 0x0000 005c */
  (uint32_t)EXTI2_IRQHandler,             /* 0x0000 0060 */
  (uint32_t)EXTI3_IRQHandler,             /* 0x0000 0064 */
  (uint32_t)EXTI4_IRQHandler,             /* 0x0000 0068 */
  (uint32_t)DMA1_Stream0_IRQHandler,      /* 0x0000 006c */
  (uint32_t)DMA1_Stream1_IRQHandler,      /* 0x0000 0070 */
  (uint32_t)DMA1_Stream2_IRQHandler,      /* 0x0000 0074 */
  (uint32_t)DMA1_Stream3_IRQHandler,      /* 0x0000 0078 */
  (uint32_t)DMA1_Stream4_IRQHandler,      /* 0x0000 007c */
  (uint32_t)DMA1_Stream5_IRQHandler,      /* 0x0000 0080 */
  (uint32_t)DMA1_Stream6_IRQHandler,      /* 0x0000 0084 */
  (uint32_t)DMA1_Stream7_IRQHandler,      /* 0x0000 0088 */
  (uint32_t)ADC_IRQHandler,               /* 0x0000 008c */
  (uint32_t)0,                             /* 0x0000 0090 */
  (uint32_t)0,                             /* 0x0000 0094 */
  (uint32_t)0,                             /* 0x0000 0098 */
  (uint32_t)EXTI9_5_IRQHandler,            /* 0x0000 009c */
  (uint32_t)TIM1_BRK_TIM9_IRQHandler,     /* 0x0000 00a0 */
  (uint32_t)TIM1_UP_TIM10_IRQHandler,     /* 0x0000 00a4 */
  (uint32_t)TIM1_TRG_COM_TIM11_IRQHandler,/* 0x0000 00a8 */
  (uint32_t)TIM1_CC_IRQHandler,           /* 0x0000 00ac */
  (uint32_t)TIM2_IRQHandler,              /* 0x0000 00b0 */
  (uint32_t)TIM3_IRQHandler,              /* 0x0000 00b4 */
  (uint32_t)TIM4_IRQHandler,              /* 0x0000 00b8 */
  (uint32_t)I2C1_EV_IRQHandler,           /* 0x0000 00bc */
  (uint32_t)I2C1_ER_IRQHandler,           /* 0x0000 00c0 */
  (uint32_t)I2C2_EV_IRQHandler,           /* 0x0000 00c4 */
  (uint32_t)I2C2_ER_IRQHandler,           /* 0x0000 00c8 */
  (uint32_t)SPI1_IRQHandler,              /* 0x0000 00cc */
  (uint32_t)SPI2_IRQHandler,              /* 0x0000 00d0 */
  (uint32_t)USART1_IRQHandler,            /* 0x0000 00d4 */
  (uint32_t)USART2_IRQHandler,            /* 0x0000 00d8 */
  (uint32_t)0,                             /* 0x0000 00dc */
  (uint32_t)0,                             /* 0x0000 00e0 */
  (uint32_t)EXTI15_10_IRQHandler,         /* 0x0000 00e4 */
  (uint32_t)EXTI17_RTC_Alarm_IRQHandler,   /* 0x0000 00e8 */
  (uint32_t)EXTI18_OTG_FS_WKUP_IRQHandler,/* 0x0000 00ec */
  (uint32_t)0,                             /* 0x0000 00f0 */
  (uint32_t)0,                             /* 0x0000 00f4 */
  (uint32_t)0,                             /* 0x0000 00f8 */
  (uint32_t)DMA1_Stream7_IRQHandler,      /* 0x0000 00fc */
  (uint32_t)0,                             /* 0x0000 0100 */
  (uint32_t)0,                             /* 0x0000 0104 */
  (uint32_t)TIM5_IRQHandler,              /* 0x0000 0108 */
  (uint32_t)SPI3_IRQHandler,              /* 0x0000 010c */
  (uint32_t)DMA2_Stream0_IRQHandler,      /* 0x0000 0110 */
  (uint32_t)DMA2_Stream1_IRQHandler,      /* 0x0000 0114 */
  (uint32_t)DMA2_Stream2_IRQHandler,      /* 0x0000 0118 */
  (uint32_t)DMA2_Stream3_IRQHandler,      /* 0x0000 011c */
  (uint32_t)DMA2_Stream4_IRQHandler,      /* 0x0000 0120 */
  (uint32_t)0,                             /* 0x0000 0124 */
  (uint32_t)0,                             /* 0x0000 0128 */
  (uint32_t)0,                             /* 0x0000 012c */
  (uint32_t)0,                             /* 0x0000 0130 */
  (uint32_t)0,                             /* 0x0000 0134 */
  (uint32_t)0,                             /* 0x0000 0138 */
  (uint32_t)0,                             /* 0x0000 013c */
  (uint32_t)0,                             /* 0x0000 0140 */
  (uint32_t)OTG_FS_IRQHandler,            /* 0x0000 0144 */
  (uint32_t)DMA2_Stream5_IRQHandler,      /* 0x0000 0148 */
  (uint32_t)DMA2_Stream6_IRQHandler,      /* 0x0000 014c */
  (uint32_t)DMA2_Stream7_IRQHandler,      /* 0x0000 0150 */
  (uint32_t)USART6_IRQHandler,            /* 0x0000 0154 */
  (uint32_t)I2C3_EV_IRQHandler,           /* 0x0000 0158 */
  (uint32_t)I2C3_ER_IRQHandler,           /* 0x0000 015c */
  (uint32_t)0,                             /* 0x0000 0160 */
  (uint32_t)0,                             /* 0x0000 0164 */
  (uint32_t)0,                             /* 0x0000 0168 */
  (uint32_t)0,                             /* 0x0000 016c */
  (uint32_t)0,                             /* 0x0000 0170 */
  (uint32_t)0,                             /* 0x0000 0174 */
  (uint32_t)0,                             /* 0x0000 0178 */
  (uint32_t)0,                             /* 0x0000 017c */
  (uint32_t)0,                             /* 0x0000 0180 */
  (uint32_t)FPU_IRQHandler,               /* 0x0000 0184 */
  (uint32_t)0,                             /* 0x0000 0188 */
  (uint32_t)0,                             /* 0x0000 018c */
  (uint32_t)0,                             /* 0x0000 0190 */
  (uint32_t)SPI4_IRQHandler,              /* 0x0000 0194 */
  (uint32_t)SPI5_IRQHandler,              /* 0x0000 0198 */
  (uint32_t)0,                             /* 0x0000 019c */
  (uint32_t)0,                             /* 0x0000 01a0 */
  (uint32_t)0,                             /* 0x0000 01a4 */
  (uint32_t)0,                             /* 0x0000 01a8 */
  (uint32_t)0,                             /* 0x0000 01ac */
  (uint32_t)0,                             /* 0x0000 01b0 */
  (uint32_t)0,                             /* 0x0000 01b4 */
  (uint32_t)0,                             /* 0x0000 01b8 */
  (uint32_t)0,                             /* 0x0000 01bc */
  (uint32_t)0,                             /* 0x0000 01c0 */
  (uint32_t)0,                             /* 0x0000 01c4 */
  (uint32_t)0,                             /* 0x0000 01c8 */
  (uint32_t)0,                             /* 0x0000 01cc */
  (uint32_t)0,                             /* 0x0000 01d0 */
  (uint32_t)0,                             /* 0x0000 01d4 */
  (uint32_t)0,                             /* 0x0000 01d8 */
  (uint32_t)0,                             /* 0x0000 01dc */
  (uint32_t)0,                             /* 0x0000 01e0 */
  (uint32_t)0,                             /* 0x0000 01e4 */
  (uint32_t)0,                             /* 0x0000 01e8 */
  (uint32_t)0,                             /* 0x0000 01ec */
  (uint32_t)0,                             /* 0x0000 01f0 */
  (uint32_t)0,                             /* 0x0000 01f4 */
  (uint32_t)0,                             /* 0x0000 01f8 */
  (uint32_t)0,                             /* 0x0000 01fc */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

void reset_handler(void)
{
  uint32_t i; 

  /* Copia a secao .data para a RAM */
   
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *pDst = (uint8_t*)&_sdata;                      /* SRAM */
  uint8_t *pSrc = (uint8_t*)&_la_data;                    /* FLASH */
  
  for(i = 0; i < size; i++)
  {
    *pDst++ = *pSrc++;
  }

  /* Preenche a secao .bss com zero */

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t*)&_sbss;
  for(i = 0 ; i < size; i++)
  {
    *pDst++ = 0;
  }

  /* Chama a funcao main() */

  main();
}

void default_handler(void)
{
  while(1){};
}