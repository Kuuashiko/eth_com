/*
 * SYSCFG.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "SYSCFG.h"
 

/* Local Types */

/* Public functions */


/**
 * @brief SYSCFG_set_RMII_ETH
 * 
 * - set the eth config in RMII mode, must be done before eth activation
 * 
 * @param [in,out] io_SYSCFG_regs : pointer to SYSCFG registers
 * 
 * @return void
 * 
 **/
void SYSCFG_set_RMII_ETH(t_SYSCFG_registers_s *io_SYSCFG_regs)
{
	io_SYSCFG_regs->SYSCFG_PMC |= D_RMII_VALUE << D_BIT_MII_RMII_SEL;
}
