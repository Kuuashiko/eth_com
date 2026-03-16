#include "stdio.h"
#include "746.h"


int main()
{

	t_RCC_registers *RCC_map = (t_RCC_registers *)D_RCC_ADDR;
    t_SYSCFG_registers *SYSCFG_map = (t_SYSCFG_registers *)D_SYSCFG_ADDR;
    t_GPIO_Bank *GPIO_Bank = (t_GPIO_Bank *)D_GPIO_ADDR;
    
    RCC_enable_gpio_clock(RCC_map, 0x00000047U); /* Enable GPIOA, GPIOB, GPIOC & GPIOG clock */
    RCC_enable_SYSCFG_clock(RCC_map);/* Enable write in SYSCFG register */
    GPIO_init_ETH(GPIO_Bank);
    SYSCFG_set_RMII_ETH(SYSCFG_map);
    RCC_enable_eth_clock(RCC_map);
    
    uint32_t dmabmr = *(uint32_t *)0x40029000U;
    uint32_t *macmiiar = (uint32_t *) 0x40028010U;
    *macmiiar = 0x840U;
    uint32_t macmiidr = *(uint32_t *)0x40028014U;
    
return 0;
}
