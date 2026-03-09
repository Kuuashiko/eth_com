#include "stdio.h"
#include "746.h"


int main()
{

	t_RCC_registers *RCC_map = (t_RCC_registers *)D_RCC_ADDR;
    t_SYSCFG_registers *SYSCFG_map = (t_SYSCFG_registers *)D_SYSCFG_ADDR;

    RCC_set_RCC_CR(RCC_map,0x00000001);
    SYSCFG_set_RMII_ETH(SYSCFG_map);
return 0;
}
