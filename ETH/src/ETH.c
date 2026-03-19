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



/* Local Types */

/* Private functions */


void set_mac_params (t_MAC_regs *MAC)
{
    MAC->CR     |= 0x0000080CU; /* Enable half duplex (bit 11), enable tx (bit 3) & rx (bit 2) */
    MAC->FFR    |= 0x80000010U; /* Enable receive all (bit 31 (PA), bit 4 (PAM)) */
    MAC->A0HR   |= 0x00004D4FU; /* "MO" in ASCII */
    MAC->A0LR   |= 0x4E41434FU; /* "NACO" in ASCII */
}

void init_desc_eth(t_TX_descriptor *TX_DSC, t_RX_descriptor *RX_DSC, uint8_t *ETH_SEND, uint8_t *ETH_RECEIVE )
{
    TX_DSC->TDES0 = 0x30E00000U; /* Clear all control bits */  
    TX_DSC->TDES1 = 0x00000000U; /* Clear all control bits */
    TX_DSC->TDES2 = (uint32_t)ETH_SEND; /* Buffer address */
    TX_DSC->TDES3 = (uint32_t)TX_DSC;
    RX_DSC->RDES0 = 0x80000000U; /* Clear all control bits */
    RX_DSC->RDES1 = 0x00004600U; /* Clear all control bits */
    RX_DSC->RDES2 = (uint32_t)ETH_RECEIVE; /* Buffer address */
    RX_DSC->RDES3 = (uint32_t)RX_DSC;
}


void set_dma_config (t_DMA_regs *DMA,t_TX_descriptor *TX_DSC, t_RX_descriptor *RX_DSC)
{
    DMA->RDLAR = (uint32_t)RX_DSC; /* set RX descriptor address */
    DMA->TDLAR = (uint32_t)TX_DSC; /* set TX descriptor address */
    DMA->OMR |= 0x00002002U; /* Start the DMA transmission */
}

void set_header_eth_udp()
{
    head_eth_udp.mac_dest[0] = 0xFFFF; /* Broadcast MAC address */
    head_eth_udp.mac_dest[1] = 0xFFFF;
    head_eth_udp.mac_dest[2] = 0xFFFF;
    head_eth_udp.mac_source[0] = M_Swap16(0x4D4F); /* "MO" in ASCII */
    head_eth_udp.mac_source[1] = M_Swap16(0x4E41); /* "NA" in ASCII */
    head_eth_udp.mac_source[2] = M_Swap16(0x434F); /* "CO" in ASCII */
    head_eth_udp.protocol = M_Swap16(0x0800); /* Ethertype for IPv4 */
    head_eth_udp.version_ihl = 0x45; /* Version 4, IHL 5 (20 bytes) */
    head_eth_udp.dsc_esn = 0x00; /* Default value for DSCP and ECN */
    head_eth_udp.total_length = sizeof(t_HEAD_ETH_UDP); /* Total length of the UDP packet */
    head_eth_udp.identification = M_Swap16(0x1234); /* Example identification */
    head_eth_udp.flags_offset = M_Swap16(0x4000); /* Don't fragment flag */
    head_eth_udp.ttl = 64; /* Time to live */
    head_eth_udp.protocol_ip = 17; /* Protocol number for UDP */
    head_eth_udp.header_checksum = 0; /* Compute by MAC */
    head_eth_udp.ip_src = M_Swap32(0xC0000000); /* Example source IP:*/
    head_eth_udp.ip_dest = M_Swap32(0xC0000001); /* Example destination IP: */
    head_eth_udp.udp_src = M_Swap16(0x1994); /* Example source port */
    head_eth_udp.udp_dest = M_Swap16(0x0310); /* Example destination port */
    head_eth_udp.length = 0; /* Updated later */
    head_eth_udp.checksum = 0; /* Compute by MAC */
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
