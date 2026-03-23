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
	GPIOs->GPIOA.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD2;
	GPIOs->GPIOA.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD7;
    GPIOs->GPIOG.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD11;
    GPIOs->GPIOG.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD13;
    GPIOs->GPIOG.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD14;
	GPIOs->GPIOC.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD1;
	GPIOs->GPIOC.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD4;
	GPIOs->GPIOC.MODER |= E_ALT_FUNCT << D_OFFSET_MODE_SPEED_PUPD5;
}

void set_speed_mode (t_GPIO_Bank *GPIOs)
{
	GPIOs->GPIOA.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD1;
	GPIOs->GPIOA.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD2;
	GPIOs->GPIOA.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD7;
	GPIOs->GPIOG.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD11;
	GPIOs->GPIOG.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD13;
	GPIOs->GPIOG.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD14;
	GPIOs->GPIOC.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD1;
	GPIOs->GPIOC.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD4;
	GPIOs->GPIOC.OSPEEDR |= E_VERY_HIGH_SPEED << D_OFFSET_MODE_SPEED_PUPD5;
}

void set_io_ph0 (t_GPIO_Bank *GPIOs)
{
	GPIOs->GPIOH.BSRR |= E_SET_RESET << D_OFFSET_SET_RESET0;
}

void set_num_alt_function(t_GPIO_Bank *GPIOs)
{
	GPIOs->GPIOA.AFLR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION1_9;
	GPIOs->GPIOA.AFLR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION2_10;
	GPIOs->GPIOA.AFLR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION7_15;
	GPIOs->GPIOG.AFHR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION3_11;
	GPIOs->GPIOG.AFHR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION5_13;
	GPIOs->GPIOG.AFHR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION6_14;
	GPIOs->GPIOC.AFLR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION1_9;
	GPIOs->GPIOC.AFLR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION4_12;
	GPIOs->GPIOC.AFLR |= E_AF11 << D_OFFSET_ALTERNATE_FUNCTION5_13;
}
/* Public functions */
//0b10

/* --------------------------------------------------*/
/* Brief GPIO_init_ETH   */
/* set the GPIO for RMII mode CF Table 12 DS10916.   */
/*                                                   */
/* ETH_RMII_REF_CLK --> GPIO A Port 1                */
/* ETH_MDIO         --> GPIO A Port 2                */
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
	set_alternate_function_mode(GPIOs);
	set_speed_mode(GPIOs);
	set_num_alt_function(GPIOs);	
}
