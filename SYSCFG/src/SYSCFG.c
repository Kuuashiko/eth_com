/*
 * RCC.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "SYSCFG.h"
 
/* Locals Constants */
#define D_BIT_MII_RMII_SEL 23U
#define D_RMII_VALUE       1U   


/* Local Types */

/* Public functions */


/* set the eth config in RMII mode, must be done before eth activation */
void SYSCFG_set_RMII_ETH(t_SYSCFG_registers *SYS_CFG_regs)
{
	SYS_CFG_regs->SYSCFG_PMC |= D_RMII_VALUE << D_BIT_MII_RMII_SEL;
}
