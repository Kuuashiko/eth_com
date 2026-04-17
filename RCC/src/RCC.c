/*
 * RCC.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "RCC.h"

/* Local Types */

/* Public functions */


/**
 * @brief RCC_enable_eth_clock
 * 
 * - Enable selected bit of RCC_AHB1 register to enable the ethernet clocks, bits 25 to 28
 * 
 * @param [in,out] io_RCC_drv : pointer to RCC registers
 * @param [in] i_ETH_clk : ETH param required to be set 
 * 
 * @return void
 * 
 **/
void RCC_enable_eth_clock(t_RCC_registers_s *io_RCC_drv, enum_ETH_clk i_ETH_clk)
{
	io_RCC_drv->RCC_AHB1ENR |= i_ETH_clk & D_MASK_ETH_clk;
}

/**
 * @brief RCC_enable_eth_clock
 * 
 * - Enable bits  required of RCC_AHB1 register to enable the GPIO Banks A to K (GPIO are on bits 0 to 10)
 * 
 * @param [in,out] io_RCC_drv : pointer to RCC registers
 * @param [in] i_gpio : GPIO bank required to be set 
 * 
 * @return void
 * 
 **/
void RCC_enable_gpio_clock(t_RCC_registers_s *io_RCC_drv,enum_GPIO_x i_gpio)
{
	io_RCC_drv->RCC_AHB1ENR |=  i_gpio & D_MASK_GPIOx;
}


/**
 * @brief RCC_enable_eth_clock
 * 
 * - Enable write in SYSCFG register
 * 
 * @param [in,out] io_RCC_drv : pointer to RCC registers
 * 
 * @return void
 * 
 **/
void RCC_enable_SYSCFG_clock(t_RCC_registers_s *io_RCC_drv)
{
	io_RCC_drv->RCC_APB2ENR |= D_BIT_SYSCFG_APB2ENR;
}


/**
 * @brief RCC_enable_eth_clock
 * 
 * - Enable selected bits of apb1enr register to enable the timer, 2 to 7 and 12 to 14 are available but only 2 to 5 has been mapped
 * 
 * @param [in,out] io_RCC_drv : pointer to RCC registers
 * @param [in] i_timer_x : Timer number required to be set 
 * 
 * @return void
 * 
 **/
void RCC_enable_timer_clock(t_RCC_registers_s *io_RCC_drv, enum_TIMER_x i_timer_x)
{
	io_RCC_drv->RCC_APB1ENR |= i_timer_x & D_MASK_TIMER_x;
}

/**
 * @brief RCC_enable_HSE_clock
 * 
 * - Enable HSE and set system frequency to HSE clock instead of default HSI clock
 * 
 * @param [in,out] io_RCC_drv : pointer to RCC registers
 * 
 * @return void
 */
void RCC_enable_HSE_clock(t_RCC_registers_s *io_RCC_drv)
{
	io_RCC_drv->RCC_CR |= D_HSEON_CR;

	/* wait for HSE to be ready */

	while (((io_RCC_drv->RCC_CR & D_HSERDY_CR ) >> D_OFFSET_HSERDY ) == E_BIT_DISABLE)
	{
		// Wait HSERDY to be up
	}

	io_RCC_drv->RCC_CFGR = E_HSE << D_OFFSET_SW_CFGR;

	while (((io_RCC_drv->RCC_CFGR & D_MASK_SWS) >> D_OFFSET_SWS_CFGR) != E_HSE )
	{
		// wait for system to switch on HSE clock 
	}

	io_RCC_drv->RCC_CR &= ~D_HSION_CR; // disable hsi
}
