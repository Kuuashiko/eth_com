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