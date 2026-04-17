/*
 * RCC.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
#include "sys/types.h"
#include "localtypes.h"
/* Locals Constants */

#define D_RCC_ADDR             0x40023800U

#define D_MASK_GPIOx           0x000007FFU /* GPIO are on bits 0 to 10 in ahb1enr register*/
#define D_MASK_ETH_clk         0x1E000000U /* ETH clocks are on bits 25 to 28 in ahb1enr register*/
#define D_MASK_TIMER_x         0x0000000FU /* Timer clocks are on bits 0 to 8 in apb1enr register, but only 2 to 5 (bit 0 to 3) mapped*/

/* 5.3.1 RCC_CR register*/
#define D_HSION_CR             D_BIT_0
#define D_HSEON_CR             D_BIT_16 /* HSEON bit in RCC_CR*/
#define D_HSERDY_CR            D_BIT_17 /* HSERDY bit in RCC_CR */

#define D_OFFSET_HSERDY        17U
#define D_OFFSET_HSEON         17U

/* 5.3.2 RCC_CFGR register */
#define D_MASK_SW              0x00000003U
#define D_MASK_SWS             0x0000000CU

#define D_OFFSET_SW_CFGR       0U /* System Clock switch in RCC_CFGR register */
#define D_OFFSET_SWS_CFGR      2U /* System Clock switch status in RCC_CFGR register */


/* 5.3.14 RCC_APB2ENR register*/
#define D_BIT_SYSCFG_APB2ENR   D_BIT_14 /* SYSCFGEN bit in RCC_APB2ENR register*/




/* Struct RCC register map */
/* RCC registers 5.3 */
typedef struct RCC_registers {
	uint32_t RCC_CR;
	uint32_t RCC_PLLCFGR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_AHB1RSTR;
	uint32_t RCC_ABH2RSTR;
	uint32_t RCC_ABH3RSTR;
	uint8_t  reserved_1[4];
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_APB2RSTR;
	uint8_t  reserved_2[8];
	uint32_t RCC_AHB1ENR;
	uint32_t RCC_AHB2ENR;
	uint32_t RCC_AHB3ENR;
	uint8_t  reserved_3[4];
	uint32_t RCC_APB1ENR;
	uint32_t RCC_APB2ENR;
	uint8_t  reserved_4[8];
	uint32_t RCC_AHB1LPENR;
	uint32_t RCC_AHB2LPENR;
	uint32_t RCC_AHB3LPENR;
	uint8_t  reserved_5[4];
	uint32_t RCC_APB1LPENR;
	uint32_t RCC_APB2LPENR;
	uint8_t  reserved_6[8];
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
	uint8_t  reserved[8];
	uint32_t RCC_SSCGR;
	uint32_t RCC_PLLI2SCFGR;
	uint32_t RCC_PLLSAICFGR;
	uint32_t RCC_DCKCFGR1;
	uint32_t RCC_DCKCFGR2;
}t_RCC_registers_s;

typedef enum GPIOx {
	E_GPIOA = D_BIT_0,
	E_GPIOB = D_BIT_1,
	E_GPIOC = D_BIT_2,
	E_GPIOD = D_BIT_3,
	E_GPIOE = D_BIT_4,
	E_GPIOF = D_BIT_5,
	E_GPIOG = D_BIT_6,
	E_GPIOH = D_BIT_7,
	E_GPIOI = D_BIT_8,
	E_GPIOJ = D_BIT_9,
	E_GPIOK = D_BIT_10
}enum_GPIO_x;

typedef enum ETH_clocks{
	E_ETH_MACEN = D_BIT_25,
	E_ETH_MACTXEN = D_BIT_26,
	E_ETH_MACRXEN = D_BIT_27,
	E_ETH_PTPEN = D_BIT_28
}enum_ETH_clk;

typedef enum TIMER_id{
	E_TIMER_2 = D_BIT_0,
	E_TIMER_3 = D_BIT_1,
	E_TIMER_4 = D_BIT_2,
	E_TIMER_5 = D_BIT_3
}enum_TIMER_x;

typedef enum SYSTEM_CLOCK{
	E_HSI,
	E_HSE,
	E_PLL,
}enum_SYSTEM_CLOCK;


/* Public functions prototypes */

void RCC_enable_eth_clock(t_RCC_registers_s *io_RCC_drv, enum_ETH_clk i_ETH_clk);
void RCC_enable_SYSCFG_clock(t_RCC_registers_s *io_RCC_drv);
void RCC_enable_gpio_clock(t_RCC_registers_s *io_RCC_drv, enum_GPIO_x i_gpio);
void RCC_enable_timer_clock(t_RCC_registers_s *io_RCC_drv, enum_TIMER_x i_timer_x);
void RCC_enable_HSE_clock(t_RCC_registers_s *io_RCC_drv);
#endif /* INC_RCC_H_ */
