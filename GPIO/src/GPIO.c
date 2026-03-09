/*
 * RCC.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "GPIO.h"
 
/* Locals Constants */
#define D_BIT_MII_RMII_SEL 23U
#define D_RMII_VALUE       1U   


/* Local Types */

/* Private functions */
void set_alternate_function_mode (t_GPIO_Bank *GPIOs)
{
	GPIOs->GPIOA.MODER |= 0x00002008;
    GPIOs->GPIOB.MODER |= 0x0A800000;
	GPIOs->GPIOC.MODER |= 0x00000A00;
}

/* Public functions */
//0b10

/* --------------------------------------------------*/
/* Brief GPIO_init_ETH   */
/* set the GPIO for RMII mode CF Table 12 DS10916.   */
/*                                                   */
/* ETH_RMII_REF_CLK --> GPIO A Port 1                */
/* ETH_RMII_CRS_DV  --> GPIO A Port 7                */  
/* ETH_RMII_TX_EN   --> GPIO B Port 11               */  
/* ETH_RMII_TXD0    --> GPIO B Port 12               */  
/* ETH_RMII_TXD1    --> GPIO B Port 13               */ 
/* ETH_RMII_RXD0    --> GPIO C Port 4                */  
/* ETH_RMII_RXD1    --> GPIO C Port 5                */  
/*                                                   */ 
/*---------------------------------------------------*/


void GPIO_init_ETH(t_GPIO_Bank *GPIOs)
{
	

}
