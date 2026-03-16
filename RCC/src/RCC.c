/*
 * RCC.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "RCC.h"

/* Local Types */

/* Public functions */

void RCC_set_RCC_CR(t_RCC_registers *RCC_drv, uint32_t value){

	RCC_drv->RCC_CR = value;

}

/* Enable bit 25, 26 et 27 of RCC_AHB1 register to enable the ethernet clocks */
void RCC_enable_eth_clock(t_RCC_registers *RCC_drv)
{
	RCC_drv->RCC_AHB1ENR |= 0x0E000000U;
}

/* Enable bits  required of RCC_AHB1 register to enable the GPIO Banks A to K*/
void RCC_enable_gpio_clock(t_RCC_registers *RCC_drv, uint32_t i_value)
{
	RCC_drv->RCC_AHB1ENR |= i_value & 0x000007FFU;
}

/* Enable bit 25, 26 et 27 of RCC_AHB1 register to enable the ethernet clocks */
void RCC_enable_SYSCFG_clock(t_RCC_registers *RCC_drv)
{
	RCC_drv->RCC_APB2ENR |= 0x00004000U;
}