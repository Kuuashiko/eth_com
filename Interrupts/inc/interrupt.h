/* Interrupt functions ARM Cortex_M7 x STM32F746
 *
 * interupt.h 
 * Created on: 4 mars 2026
 *      Author: milko
  */

#ifndef INC_INTERRUPT_H_
#define INC_INTERRUPT_H_

#include "sys/types.h"
#include "localtypes.h"
/* Locals Constants */

#define D_NVIC_ADDR              0xE000E004U
#define D_MAX_INTERRUPT_NUMBER   97U
#define D_LENGTH_32              32U

typedef enum interrupt_id{
    E_WWDG,
    E_PVD,
    E_TAMP_STAMP,
    E_RTC_WKUP,
    E_FLASH,
    E_RCC,
    E_EXTI0,
    E_EXTI1,
    E_EXTI2,
    E_EXTI3,
    E_EXTI4,
    E_DMA1_Stream0,
    E_DMA1_Stream1,
    E_DMA1_Stream2,
    E_DMA1_Stream3,
    E_DMA1_Stream4,
    E_DMA1_Stream5,
    E_DMA1_Stream6,
    E_ADC,
    E_CAN1_TX,
    E_CAN1_RX0,
    E_CAN1_RX1,
    E_CAN1_SCE,
    E_EXTI9_5,
    E_TIM1_BRK_TIM9,
    E_TIM1_UP_TIM10,
    E_TIM1_TRG_COM_TIM11,
    E_TIM1_CC,
    E_TIM2,
    E_TIM3,
    E_TIM4,
    E_I2C1_EV,
    E_I2C1_ER,
    E_I2C2_EV,
    E_I2C2_ER,
    E_SPI1,
    E_SPI2,
    E_USART1,
    E_USART2,
    E_USART3,
    E_EXTI15_10,
    E_RTC_Alarm,
    E_OTG_FS_WKUP,
    E_TIM8_BRK_TIM12,
    E_TIM8_UP_TIM13,
    E_TIM8_TRG_COM_TIM14,
    E_TIM8_CC,
    E_DMA1_Stream7,
    E_FSMC,
    E_SDMMC1,
    E_TIM5,
    E_SPI3,
    E_UART4,
    E_UART5,
    E_TIM6_DAC,
    E_TIM7,
    E_DMA2_Stream0,
    E_DMA2_Stream1,
    E_DMA2_Stream2,
    E_DMA2_Stream3,
    E_DMA2_Stream4,
    E_ETH,
    E_ETH_WKUP,
    E_CAN2_TX,
    E_CAN2_RX0,
    E_CAN2_RX1,
    E_CAN2_SCE,
    E_OTG_FS,
    E_DMA2_Stream5,
    E_DMA2_Stream6,
    E_DMA2_Stream7,
    E_USART6,
    E_I2C3_EV,
    E_I2C3_ER,
    E_OTG_HS_EP1_OUT,
    E_OTG_HS_EP1_IN,
    E_OTG_HS_WKUP,
    E_OTG_HS,
    E_DCMI,
    E_CRYP,
    E_HASH_RNG,
    E_FPU,
    E_UART7,
    E_UART8,
    E_SPI4,
    E_SPI5,
    E_SPI6,
    E_SAI1,
    E_LCD_G,
    E_LCD_ERR,
    E_DMA2D,
    E_SAI2,
    E_QUADSPI,
    E_LPTIMER1,
    E_HDMI_CEC,
    E_I2C4_EV,
    E_I2C4_ER,
    E_SPDIF_RX

}enum_E_INTERRUPT_ID;


/* Struct NVIC register map */
typedef struct NVIC_registers {
    uint32_t ICTR;
    uint32_t reserved_0[62]; 
    uint32_t ISER[8];
    uint32_t reserved_1[18]; 
    uint32_t ICER[8]; 
    uint32_t reserved_2[18];       
    uint32_t ISPR[8]; 
    uint32_t reserved_3[18]; 
    uint32_t ICPR[8]; 
    uint32_t reserved_4[18]; 
    uint32_t IABR[8]; 
    uint32_t reserved_5[38];
    uint32_t IPR[60]; 
}t_NVIC_registers_s;

/* Public functions */
int32_t NVIC_enable_interrupt(t_NVIC_registers_s *NVIC_drv, enum_E_INTERRUPT_ID i_interrupt_id);



#endif /* INC_INTERRUPT_H_ */
