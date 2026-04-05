/*
 * boot.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#include "boot.h"


/**
 * @brief boot
 * 
 * Configure material configuration to have ethernet communication
 * 
 * @param void
 * 
 * @return void
 **/
void boot(void) 
{
    t_RCC_registers_s *RCC_map = (t_RCC_registers_s *)D_RCC_ADDR;
    t_SYSCFG_registers_s *SYSCFG_map = (t_SYSCFG_registers_s *)D_SYSCFG_ADDR;
    t_GPIO_Bank_s *GPIO_Bank = (t_GPIO_Bank_s *)D_GPIO_ADDR;
    t_ETH_regs_s *ETH_map = (t_ETH_regs_s *)D_ETH_ADDR;
    t_NVIC_registers_s *NVIC_map = (t_NVIC_registers_s *)D_NVIC_ADDR;
    

    // Configure gpio banks for eth rmii
    RCC_enable_gpio_clock(RCC_map, E_GPIOA); /* Enable GPIOA, GPIOC & GPIOG clock */
    RCC_enable_gpio_clock(RCC_map, E_GPIOC);
    RCC_enable_gpio_clock(RCC_map, E_GPIOG);
    
    
    RCC_enable_SYSCFG_clock(RCC_map);/* Enable write in SYSCFG register */
    
    // enable 32 bits timer to clocks ethernet communication
    RCC_enable_timer_clock(RCC_map, E_TIMER_2); /* Enable timer 2 */
    NVIC_enable_interrupt(NVIC_map, E_ETH); /* Enable Ethernet interrupt in NVIC */

    // init gpio for eth rmii mode
    GPIO_init_ETH(GPIO_Bank);
    
    // set rmii mode in syscfg
    SYSCFG_set_RMII_ETH(SYSCFG_map);
    
    //enable clock for mac, tx & rx
    RCC_enable_eth_clock(RCC_map,E_ETH_MACEN);
    RCC_enable_eth_clock(RCC_map,E_ETH_MACRXEN);
    RCC_enable_eth_clock(RCC_map,E_ETH_MACTXEN);

    //configure ethernet settings
    ETH_conf(ETH_map);

}