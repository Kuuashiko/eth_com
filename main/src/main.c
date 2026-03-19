#include "stdio.h"
#include "746.h"

static t_TX_descriptor *TX_DESC = (t_TX_descriptor *)0x2004C000U;
static t_RX_descriptor *RX_DESC = (t_RX_descriptor *)0x2004C020U;

t_HEAD_ETH_UDP head_eth_udp;
/* Private functions*/




int main()
{

	t_RCC_registers *RCC_map = (t_RCC_registers *)D_RCC_ADDR;
    t_SYSCFG_registers *SYSCFG_map = (t_SYSCFG_registers *)D_SYSCFG_ADDR;
    t_GPIO_Bank *GPIO_Bank = (t_GPIO_Bank *)D_GPIO_ADDR;
    t_ETH_regs *ETH_map = (t_ETH_regs *)D_ETH_ADDR;
    t_FRAME_ETH ETH_send;
    t_FRAME_ETH ETH_receive;



    uint32_t data = 0x50494E47U; /* "PING" in ASCII */
    
    RCC_enable_gpio_clock(RCC_map, 0x00000047U); /* Enable GPIOA, GPIOB, GPIOC & GPIOG clock */
    RCC_enable_SYSCFG_clock(RCC_map);/* Enable write in SYSCFG register */
    GPIO_init_ETH(GPIO_Bank);
    SYSCFG_set_RMII_ETH(SYSCFG_map);
    RCC_enable_eth_clock(RCC_map);
    ETH_conf(ETH_map);
    init_desc_eth(TX_DESC, RX_DESC, (uint8_t *)&ETH_send, (uint8_t *)&ETH_receive);
    set_dma_config(&ETH_map->DMA, TX_DESC, RX_DESC);


    ETH_send.payload = (uint8_t *)&data;
    ETH_send.head_eth_udp.length = M_Swap16(sizeof(t_HEAD_ETH_UDP) + sizeof(data))-20; /* Length of UDP payload (total length - IP header) */
    ETH_send.head_eth_udp.total_length = M_Swap16(sizeof(t_HEAD_ETH_UDP) + sizeof(data)); /* Total length of the UDP packet (IP header + UDP header + payload) */
    TX_DESC->TDES1 |= sizeof(t_HEAD_ETH_UDP) + sizeof(data); /* Set the frame length in TDES1 */
    TX_DESC->TDES0 |= 0x80000000U; /* Send frame */
    while (1) {
        if ( ( (TX_DESC->TDES0 & 0x80000000) >> 31 ) == 1)
    	ETH_map->DMA.TDLAR = 1;
    }


    uint32_t dmabmr = *(uint32_t *)0x40029000U;
    uint32_t *macmiiar = (uint32_t *) 0x40028010U;
    *macmiiar = 0x840U;
    uint32_t macmiidr = *(uint32_t *)0x40028014U;
    
return 0;
}
