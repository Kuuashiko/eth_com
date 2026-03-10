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
	GPIOs->GPIOA.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD1;
	GPIOs->GPIOA.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD7;
    GPIOs->GPIOB.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD11;
    GPIOs->GPIOB.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD12;
    GPIOs->GPIOB.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD13;
	GPIOs->GPIOC.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD4;
	GPIOs->GPIOC.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD5;
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
