/*
 * RCC.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "ETH.h"



/* Locals Constants */
#define D_BIT_MII_RMII_SEL 23U
#define D_RMII_VALUE       1U   



/* Extern variables */
extern t_FRAME_ETH ETH_send;
extern t_FRAME_ETH ETH_receive;

extern uint8_t *Buff_ETH_SEND;
extern uint8_t *Buff_ETH_RECEIVE;

/* Local Types */

/* Private functions */


void set_mac_params (t_MAC_regs *MAC)
{
    MAC->CR     |= 0x0000480CU; /* Enable half duplex (bit 11), enable tx (bit 3), rx (bit 2) a set speed at 100 mbps (bit 14)  and loopback mode if 580c no lm 480c*/
    MAC->FFR    |= 0x80000010U; /* Enable receive all (bit 31 (PA), bit 4 (PAM)) */
    MAC->A0HR   |= 0x00004D4FU; /* "MO" in ASCII */
    MAC->A0LR   |= 0x4E41434FU; /* "NACO" in ASCII */
}

void init_desc_eth(t_TX_descriptor *TX_DSC, t_RX_descriptor *RX_DSC, uint8_t *ETH_SEND, uint8_t *ETH_RECEIVE )
{
    TX_DSC->TDES0 = 0x30E00000U; /* Clear all control bits */  
    TX_DSC->TDES1 = 0x00000000U; /* Clear all control bits */
    TX_DSC->TDES2 = D_BUFFER_SEND_ADDR; /* Buffer address */
    TX_DSC->TDES3 = (uint32_t)TX_DSC;
    RX_DSC->RDES0 = 0x80000000U; /* Clear all control bits */
    RX_DSC->RDES1 = 0x00004600U; /* Clear all control bits */
    RX_DSC->RDES2 = D_BUFFER_RECEIVE_ADDR; /* Buffer address */
    RX_DSC->RDES3 = (uint32_t)RX_DSC;
}


void set_dma_config (t_DMA_regs *DMA,t_TX_descriptor *TX_DSC, t_RX_descriptor *RX_DSC)
{
    DMA->RDLAR = (uint32_t)RX_DSC; /* set RX descriptor address */
    DMA->TDLAR = (uint32_t)TX_DSC; /* set TX descriptor address */
    DMA->OMR |= 0x00202002U; /* Start the DMA transmission */
}

void set_header_eth_udp()
{

    uint16_t *end_addr = (uint16_t *)(Buff_ETH_SEND + D_HEADER_LENGTH);
    
    
    ETH_send.head_eth_udp.mac_dest[0] = 0xFFFF; /* Broadcast MAC address */
    ETH_send.head_eth_udp.mac_dest[1] = 0xFFFF;
    ETH_send.head_eth_udp.mac_dest[2] = 0xFFFF;
    ETH_send.head_eth_udp.mac_source[0] = 0x4D4F; /* "MO" in ASCII */
    ETH_send.head_eth_udp.mac_source[1] = 0x4E41; /* "NA" in ASCII */
    ETH_send.head_eth_udp.mac_source[2] = 0x434F; /* "CO" in ASCII */
    ETH_send.head_eth_udp.protocol = 0x0800; /* Ethertype for IPv4 */
    ETH_send.head_eth_udp.ihl_dsc_esn = 0x4500; /* Version 4, IHL 5 (20 bytes) , Default value for DSCP and ECN */
    ETH_send.head_eth_udp.total_length = sizeof(t_HEAD_ETH_UDP); /* Total length of the UDP packet */
    ETH_send.head_eth_udp.identification = 0x1234; /* Example identification */
    ETH_send.head_eth_udp.flags_offset = 0x4000; /* Don't fragment flag */
    ETH_send.head_eth_udp.ttl_prot_ip = 0x4011; /* Time to live & Protocol number for UDP*/
    ETH_send.head_eth_udp.header_checksum = 0; /* Compute by MAC */
    ETH_send.head_eth_udp.ip_src = 0xC0000000; /* Example source IP:*/
    ETH_send.head_eth_udp.ip_dest = 0xC0000001; /* Example destination IP: */
    ETH_send.head_eth_udp.udp_src = 0x1994; /* Example source port */
    ETH_send.head_eth_udp.udp_dest = 0x0310; /* Example destination port */
    ETH_send.head_eth_udp.length = 0; /* Updated later */
    ETH_send.head_eth_udp.checksum = 0; /* Compute by MAC */


    
    memcpy(&Buff_ETH_SEND[0], ETH_send.head_eth_udp.mac_dest, sizeof(uint16_t)*3); /* Copy MAC destination */
    memcpy(&Buff_ETH_SEND[6], ETH_send.head_eth_udp.mac_source, sizeof(uint16_t)*3); /* Copy MAC source  0 0x4D4F */
    memcpy(&Buff_ETH_SEND[12], &ETH_send.head_eth_udp.protocol, sizeof(uint16_t)); /* Copy Ethertype */
    memcpy(&Buff_ETH_SEND[14], &ETH_send.head_eth_udp.ihl_dsc_esn, sizeof(uint16_t)); /* Copy Version, IHL, DSCP and ECN */
    memcpy(&Buff_ETH_SEND[16], &ETH_send.head_eth_udp.total_length, sizeof(uint16_t)); /* Copy Total length */
    memcpy(&Buff_ETH_SEND[18], &ETH_send.head_eth_udp.identification, sizeof(uint16_t)); /* Copy Identification */
    memcpy(&Buff_ETH_SEND[20], &ETH_send.head_eth_udp.flags_offset, sizeof(uint16_t)); /* Copy Flags and Fragment offset */
    memcpy(&Buff_ETH_SEND[22], &ETH_send.head_eth_udp.ttl_prot_ip, sizeof(uint16_t)); /* Copy Time to live and Protocol */
    memcpy(&Buff_ETH_SEND[24], &ETH_send.head_eth_udp.header_checksum, sizeof(uint16_t)); /* Copy Header checksum */
    memcpy(&Buff_ETH_SEND[26], &ETH_send.head_eth_udp.ip_src, sizeof(uint32_t)); /* Copy Source IP address */
    *(uint32_t *)&Buff_ETH_SEND[26] = ((*(uint32_t *)&Buff_ETH_SEND[26] >> 16) & 0xFFFF) | ((*(uint32_t *)&Buff_ETH_SEND[26] & 0xFFFF) << 16);
    memcpy(&Buff_ETH_SEND[30], &ETH_send.head_eth_udp.ip_dest, sizeof(uint32_t)); /* Copy Destination IP address */
    *(uint32_t *)&Buff_ETH_SEND[30] = ((*(uint32_t *)&Buff_ETH_SEND[30] >> 16) & 0xFFFF) | ((*(uint32_t *)&Buff_ETH_SEND[30] & 0xFFFF) << 16);
    memcpy(&Buff_ETH_SEND[34], &ETH_send.head_eth_udp.udp_src, sizeof(uint16_t)); /* Copy UDP source port */
    memcpy(&Buff_ETH_SEND[36], &ETH_send.head_eth_udp.udp_dest, sizeof(uint16_t)); /* Copy UDP destination port */
    memcpy(&Buff_ETH_SEND[38], &ETH_send.head_eth_udp.length, sizeof(uint16_t)); /* Copy UDP length */
    memcpy(&Buff_ETH_SEND[40], &ETH_send.head_eth_udp.checksum, sizeof(uint16_t)); /* Copy UDP checksum */


    /* Set byte in big-endian format */
    for ( uint16_t *base_addr_buff = (uint16_t *)Buff_ETH_SEND; base_addr_buff < end_addr ; base_addr_buff++)
    {
    	*base_addr_buff= M_Swap16(*base_addr_buff); /* Swap bytes for big-endian format */
    }

}   

//void set_bytes_frame_eth_udp(uint16_t *i_base_addr_frame, uint32_t i_frame_length)
//{
//    
//    uint32_t end_addr = (uint32_t)i_base_addr_frame + i_frame_length;
//    for ( i_base_addr_frame; i_base_addr_frame < end_addr ; i_base_addr_frame++)
//    {
//        *i_base_addr_frame= M_Swap16(*i_base_addr_frame); /* Swap bytes for big-endian format */
//    }
//}

void set_payload_send_eth(uint32_t i_length_payload)
{

    memcpy(&Buff_ETH_SEND[16], &ETH_send.head_eth_udp.total_length, sizeof(uint16_t)); /* Copy Total length */
    memcpy(&Buff_ETH_SEND[38], &ETH_send.head_eth_udp.length, sizeof(uint16_t)); /* Copy UDP length */
    memcpy(&Buff_ETH_SEND[42], ETH_send.payload, i_length_payload); /* Copy UDP payload */

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


void ETH_conf(t_ETH_regs *ETH_regs)
{
	set_mac_params(&ETH_regs->MAC);
	set_header_eth_udp();
}
