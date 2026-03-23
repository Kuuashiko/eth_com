#include "746.h"

#define D_FRAME_ETH_LENGTH 1514U

static t_TX_descriptor *TX_DESC = (t_TX_descriptor *)0x2004C000U;
static t_RX_descriptor *RX_DESC = (t_RX_descriptor *)0x2004C020U;


uint8_t *Buff_ETH_SEND = (uint8_t *)D_BUFFER_SEND_ADDR;
uint8_t *Buff_ETH_RECEIVE = (uint8_t *)D_BUFFER_RECEIVE_ADDR;

t_FRAME_ETH ETH_send;
t_FRAME_ETH ETH_receive;


/* Private functions*/




int main()
{

	t_RCC_registers *RCC_map = (t_RCC_registers *)D_RCC_ADDR;
    t_SYSCFG_registers *SYSCFG_map = (t_SYSCFG_registers *)D_SYSCFG_ADDR;
    t_GPIO_Bank *GPIO_Bank = (t_GPIO_Bank *)D_GPIO_ADDR;
    t_ETH_regs *ETH_map = (t_ETH_regs *)D_ETH_ADDR;



    memset(&ETH_send, 0x00, sizeof(t_FRAME_ETH));
    memset(&ETH_receive, 0x00, sizeof(t_FRAME_ETH));
    memset(Buff_ETH_SEND, 0x00, D_FRAME_ETH_LENGTH);
    memset(Buff_ETH_RECEIVE, 0x00, D_FRAME_ETH_LENGTH);
    uint32_t data = M_Swap32(0x50494E47U); /* "PING" in ASCII */
    
    RCC_enable_gpio_clock(RCC_map, 0x00000047U); /* Enable GPIOA, GPIOB, GPIOC & GPIOG clock */
    RCC_enable_SYSCFG_clock(RCC_map);/* Enable write in SYSCFG register */
    GPIO_init_ETH(GPIO_Bank);
    SYSCFG_set_RMII_ETH(SYSCFG_map);
    RCC_enable_eth_clock(RCC_map);
    ETH_conf(ETH_map);
    init_desc_eth(TX_DESC, RX_DESC, (uint8_t *)Buff_ETH_SEND, (uint8_t *)Buff_ETH_RECEIVE);
    set_dma_config(&ETH_map->DMA, TX_DESC, RX_DESC);


    memcpy(ETH_send.payload, &data, sizeof(data));
    ETH_send.head_eth_udp.length = M_Swap16(D_HEADER_LENGTH + (sizeof(data)-20)); /* Length of UDP payload (total length - IP header) */
    ETH_send.head_eth_udp.total_length = M_Swap16(D_HEADER_LENGTH + sizeof(data)); /* Total length of the UDP packet (IP header + UDP header + payload) */
    TX_DESC->TDES1 |= D_HEADER_LENGTH + sizeof(data); /* Set the frame length in TDES1 */
    //set_bytes_frame_eth_udp((uint16_t *)ETH_send, D_HEADER_LENGTH + sizeof(data) ); /* Set the bytes of the frame in Big endian to the length of the UDP payload */
    set_payload_send_eth(sizeof(data)); /* Prepare the buffer to send with the header and the payload */
    
    while (1) {
        if ( ( (TX_DESC->TDES0 & 0x80000000) >> 31 ) == 0)
        {
            TX_DESC->TDES0 |= 0x80000000U; /* Send frame */
        	ETH_map->DMA.TPDR = 1;
        }

    }


    //uint32_t dmabmr = *(uint32_t *)0x40029000U;
    //uint32_t *macmiiar = (uint32_t *) 0x40028010U;
    //*macmiiar = 0x840U;
    //uint32_t macmiidr = *(uint32_t *)0x40028014U;
    
return 0;
}
