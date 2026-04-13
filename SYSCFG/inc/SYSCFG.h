/*
 * SYSCFG.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_SYSCFG_H_
#define INC_SYSCFG_H_
#include "stdio.h"
#include "sys/types.h"


/* Locals Constants */
#define D_SYSCFG_ADDR      0x40013800U
#define D_BIT_MII_RMII_SEL 23U
#define D_RMII_VALUE       1U   


/* Struct SYSCFG register map */
/* SYSCFG registers 7.2.8 */
typedef struct SYSCFG_registers {
	uint32_t SYSCFG_MEMRMP;
	uint32_t SYSCFG_PMC;
	uint32_t SYSCFG_EXTICR1;
	uint32_t SYSCFG_EXTICR2;
	uint32_t SYSCFG_EXTICR3;
	uint32_t SYSCFG_EXTICR4;
	uint32_t SYSCFG_CMPCR;
}t_SYSCFG_registers_s;

/* Public functions prototypes */

void SYSCFG_set_RMII_ETH(t_SYSCFG_registers_s *io_SYSCFG_regs);


#endif /* INC_RCC_H_ */
