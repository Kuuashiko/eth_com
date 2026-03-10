/*
 * RCC.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
#include "stdio.h"
#include "sys/types.h"
/* Locals Constants */

#define D_RCC_ADDR      0x40023800U

/* Struct RCC register map */
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
}t_RCC_registers;

/* Public functions prototypes */

void RCC_set_RCC_CR(t_RCC_registers *RCC_drv, uint32_t value);
void RCC_enable_eth_clock(t_RCC_registers *RCC_drv);
void RCC_enable_gpio_clock(t_RCC_registers *RCC_drv, uint32_t i_value);
#endif /* INC_RCC_H_ */
