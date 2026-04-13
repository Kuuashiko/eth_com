/*
 * ETH.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "ETH.h"




/* Global variables */
t_TX_descriptor_s *TX_DESC = (t_TX_descriptor_s *)D_ADDR_DSC_TX;
t_RX_descriptor_s *RX_DESC = (t_RX_descriptor_s *)D_ADDR_DSC_RX;
t_FRAME_ETH_s *ETH_send = (t_FRAME_ETH_s *)D_BUFFER_SEND_ADDR;
t_FRAME_ETH_s *ETH_receive = (t_FRAME_ETH_s *)D_BUFFER_RECEIVE_ADDR;
static volatile uint32_t frame_received;
static uint8_t payload_save[D_MAX_PAYLOAD_SIZE];

/* Private functions prototypes */
void set_mac_params (t_MAC_regs_s *io_MAC);
void init_desc_eth(void);
void set_dma_config (t_DMA_regs_s *io_DMA);
void set_bytes_frame_eth_udp(uint16_t *i_base_addr_frame, uint32_t i_frame_length);

/* Private functions */

/** 
* @brief set_mac_params                                 
* 
*Set the MAC config :                                  
*                                                      
* - MACCR : enable Transmit, Receive, Full duplex mode    
*and set speed at 100 mbps                             
*                                                      
*  - MACFFR : enable receive all to receive all eth       
* frames                        
**/ 
 void set_mac_params (t_MAC_regs_s *io_MAC)
{
    io_MAC->CR     |= ((E_BIT_ENABLE << D_OFFSET_TE_MACCR) | (E_BIT_ENABLE << D_OFFSET_RE_MACCR) | (E_BIT_ENABLE << D_OFFSET_DM_MACCR) | (E_BIT_ENABLE << D_OFFSET_FES_MACCR));
    io_MAC->FFR    |= ((E_BIT_ENABLE << D_OFFSET_PA_MACFFR) | (E_BIT_ENABLE << D_OFFSET_PAM_MACFFR)); /* Enable receive all (bit 31 (PA), bit 4 (PAM)) */
}


/*
* @brief init_desc_eth :
* 
* - Init TX & RX descriptors
*/
void init_desc_eth(void)
{
    TX_DESC->TDES0 = ((E_BIT_ENABLE << D_OFFSET_TDES0_LS) | (E_BIT_ENABLE << D_OFFSET_TDES0_FS) | (E_CHKSUM_IP_HEADER_PAYLOAD_PSEUDO_HEADER << D_OFFSET_TDES0_CIC) | (E_BIT_ENABLE << D_OFFSET_TDES0_TER)); /* Set LS and FS for single buffer frame, set checksum insertion for IP header + payload + pseudo header, set TER to indicate the end of the ring */ 
    TX_DESC->TDES1 = D_DEFAULT_TDES1_CTRL; /* Clear all control bits */
    TX_DESC->TDES2 = D_BUFFER_SEND_ADDR; /* Buffer address */
    TX_DESC->TDES3 = (uint32_t)TX_DESC;
    RX_DESC->RDES0 = E_BIT_ENABLE << D_OFFSET_RDES0_OWN; /* Set ownership of desc to DMA */
    RX_DESC->RDES1 = ((D_MAX_ETH_SIZE << D_OFFSET_RBS) | (E_BIT_ENABLE << D_OFFSET_RDES1_RCH) | (E_BIT_ENABLE << D_OFFSET_RDES1_RER)); /* Set the receive buffer size, set RCH to indicate that RDES2 contains the next desc address, set RER to indicate the end of the ring */
    RX_DESC->RDES2 = D_BUFFER_RECEIVE_ADDR; /* Buffer address */
    RX_DESC->RDES3 = (uint32_t)RX_DESC;
}

/** 
* @brief set_dma_config                                 
* 
*Set the DMA config :                                  
*                                                      
* - RDLAR & TDLAR : set RX and TX descriptor addresses                    
*
* - OMR : start reception, transmission and TSF to be sure that full frame is in memory before tx
*
* - IER : enable receive interrupt and normal interrupt summary for the ETH_IRQHandler                         
**/ 
void set_dma_config (t_DMA_regs_s *io_DMA)
{
    io_DMA->RDLAR = (uint32_t)RX_DESC; /* set RX descriptor address */
    io_DMA->TDLAR = (uint32_t)TX_DESC; /* set TX descriptor address */
    io_DMA->OMR |= ((E_BIT_ENABLE << D_OFFSET_SR_DMAOMR) | (E_BIT_ENABLE << D_OFFSET_ST_DMAOMR) | (E_BIT_ENABLE << D_OFFSET_TSF_DMAOMR)); /* Start SR start reception, ST start transmission, TSF transmit store & forward */
    io_DMA->IER |= ((E_BIT_ENABLE << D_OFFSET_RIE_DMAIER) | (E_BIT_ENABLE << D_OFFSET_NISE_DMAIER)); /* Enable the Receive interrupt & normal interrupt summary */
}


/** 
* @brief set_header_eth_udp                                 
* 
*Set the Ethernet UDP header :                                  
*                                                      
* - Set the the tx frame param initial values.                              
**/ 
void set_header_eth_udp()
{
    memset(ETH_send, 0x00, sizeof(t_FRAME_ETH_s));
    memset(ETH_receive, 0x00, sizeof(t_FRAME_ETH_s));
    ETH_send->head_eth_udp.mac_dest[0] = D_MAC_DEST_BROADCAST; /* Broadcast MAC address */
    ETH_send->head_eth_udp.mac_dest[1] = D_MAC_DEST_BROADCAST;
    ETH_send->head_eth_udp.mac_dest[2] = D_MAC_DEST_BROADCAST;
    ETH_send->head_eth_udp.mac_source[0] = M_Swap16(D_MAC_SOURCE_0); /* "MO" */
    ETH_send->head_eth_udp.mac_source[1] = M_Swap16(D_MAC_SOURCE_1); /* "NA" */
    ETH_send->head_eth_udp.mac_source[2] = M_Swap16(D_MAC_SOURCE_2); /* "CO" */
    ETH_send->head_eth_udp.protocol = M_Swap16(D_ETHERTYPE_IPV4); /* Ethertype for IPv4 */
    ETH_send->head_eth_udp.ihl_dsc_esn = M_Swap16(D_IP_VERSION_IHL); /* Version 4, IHL 5 (20 bytes) , Default value for DSCP and ECN */
    ETH_send->head_eth_udp.total_length = 0; /* Updated later */
    ETH_send->head_eth_udp.identification = M_Swap16(D_IDENTIFICATION); /* Example identification */
    ETH_send->head_eth_udp.flags_offset = M_Swap16(D_FLAGS_OFFSET); /* Don't fragment flag */
    ETH_send->head_eth_udp.ttl_prot_ip = M_Swap16(D_TTL_PROT_IP); /* Time to live & Protocol number for UDP*/
    ETH_send->head_eth_udp.header_checksum = 0; /* Compute by MAC */
    ETH_send->head_eth_udp.ip_src = 0; /* Updated by user */
    ETH_send->head_eth_udp.ip_dest = 0; /* Updated by user */
    ETH_send->head_eth_udp.udp_src = 0; /* Updated by user */
    ETH_send->head_eth_udp.udp_dest = 0; /* Updated by user */
    ETH_send->head_eth_udp.length = 0; /* Updated later */
    ETH_send->head_eth_udp.checksum = 0; /* Compute by MAC */
}   

/* Public functions */

/** 
* @brief set_dma_config                                 
* 
*Set the Ethernet config :                                  
*                                                      
* - Configure MAC parameters
*
* - Configure Ethernet UDP header
*
* - Init TX and RX descriptors
*
* - Configure DMA parameters
*
* @param[in,out] io_ETH_regs : pointer to the Ethernet registers
*                                                                                           
*                                                      
* @return void                                  
**/ 
void ETH_conf(t_ETH_regs_s *io_ETH_regs)
{
	set_mac_params(&io_ETH_regs->MAC);
	set_header_eth_udp();
    init_desc_eth();
    set_dma_config(&io_ETH_regs->DMA);
}


/** 
* @brief ETH_set_frame_length                                 
* 
* - Set the frame length in the UDP header and TX descriptor.                                 
*                                                      
*  
* @param[in] i_length_payload : Payload length in bytes
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_frame_length(uint32_t i_length_payload)
{
    ETH_send->head_eth_udp.length = M_Swap16(D_UDP_HEADER_SIZE + i_length_payload); /* Length of UDP payload (total length - IP header) */
    ETH_send->head_eth_udp.total_length = M_Swap16(D_IP_HEADER_SIZE + D_UDP_HEADER_SIZE + i_length_payload); /* Total length of the UDP packet (IP header + UDP header + payload) */
    TX_DESC->TDES1 |= D_HEADER_LENGTH + i_length_payload; /* Set the frame length in TDES1 */
}

/** 
* @brief ETH_set_payload                                 
* 
* - Set the payload in th TX buffer.                                 
*                                                      
*  
* @param[in] i_payload : Payload table
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_payload(uint8_t i_payload[], uint32_t i_payload_size)
{
    if (i_payload != NULL )
    {
        memcpy(ETH_send->payload, i_payload,i_payload_size);
    }
    
}

/** 
* @brief ETH_get_payload                                 
* 
* - Set the payload in th TX buffer.                                 
*                                                      
*  
* @param[in] i_payload : Payload table
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_get_payload(uint8_t o_payload[], uint32_t i_payload_size)
{
    if (o_payload != NULL )
    {
        memcpy(o_payload, payload_save,i_payload_size);// copy buffer saved into app buffer
        
        memset(payload_save, 0x00, sizeof(payload_save));// flush rx buffer save
    
        
        uint32_t *end_addr = (uint32_t *)(o_payload + i_payload_size);
        /* swap buffer endianness by 32 bits words */
        for (uint32_t *curr_pos = (uint32_t *)o_payload; curr_pos < end_addr; curr_pos++)
        {
            *curr_pos = M_Swap32(*curr_pos);
        }
        // set rcv flag back to 0
        frame_received = 0;
    }

}

/** 
* @brief ETH_set_ip_dest                                 
* 
* - Set the ip dest in ethernet header.                                 
*                                                      
*  
* @param[in] i_ip_dst : Ip destination 
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_ip_dest(uint32_t i_ip_dst)
{
    ETH_send->head_eth_udp.ip_dest = M_Swap32(i_ip_dst);
}

/** 
* @brief ETH_set_ip_src                                 
* 
* - Set the ip source in ethernet header.                                 
*                                                      
*  
* @param[in] i_ip_src : Ip source 
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_ip_src(uint32_t i_ip_src)
{
    ETH_send->head_eth_udp.ip_src = M_Swap32(i_ip_src);
}

/** 
* @brief ETH_set_udp_dest                                
* 
* - Set the udp dest in ethernet header.                                 
*                                                      
*  
* @param[in] i_udp_dest : Udp dest 
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_udp_dest(uint16_t i_udp_dest)
{
    ETH_send->head_eth_udp.udp_dest = M_Swap16(i_udp_dest);
}   

/** 
* @brief ETH_set_udp_src                                
* 
* - Set the udp src in ethernet header.                                 
*                                                      
*  
* @param[in] i_udp_src : Udp src 
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_udp_src(uint16_t i_udp_src)
{
    ETH_send->head_eth_udp.udp_src = M_Swap16(i_udp_src);
}

/** 
* @brief ETH_set_own_DMA_TX_DESC                                 
* 
* - Set the ownership to the DMA in the TX descriptor.                                 
*                                                      
*  
* @param void 
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_send_frame(t_DMA_regs_s *io_DMA)
{
    io_DMA->TPDR = D_SEND_VALUE;
}

/** 
* @brief ETH_set_own_DMA_TX_DESC                                 
* 
* - Set the ownership to the DMA in the TX descriptor.                                 
*                                                      
*  
* @param void 
*                                                                               
*                                                      
* @return void                           
**/ 
void ETH_set_own_DMA_TX_DESC(void)
{
    TX_DESC->TDES0 |= ( E_BIT_ENABLE << D_OFFSET_TDES0_OWN );
}

/** 
* @brief ETH_get_receive_flag                                
* 
* - Get the reveive flag value.                                 
*                                                      
*  
* @param void 
*                                                                               
*                                                      
* @return frame_received                           
**/ 
uint32_t ETH_get_receive_flag(void)
{
    return frame_received;
}

/** 
* @brief ETH_IRQHandler                                 
* 
* Handle for ETH interrupt.                                  
*                                                      
* On frame reception, proceed as fallows :
*
* - Clear the receive flag in the DMA status register
*
* - Check if the received frame is a command frame by checking  UDP dest in the header
*
* - If it's a command frame, copy & swap the payload to the command structure and set the frame_received flag to 1
*
* - Set the ownership of the RX descriptor back to the DMA
* 
* @param void 
*                                                                                           
*                                                      
* @return void                         
**/ 
void ETH_IRQHandler(void)
{
    t_ETH_regs_s *ETH_map = (t_ETH_regs_s *)D_ETH_ADDR;
    ETH_map->DMA.SR |= ( E_BIT_ENABLE << D_OFFSET_RS_DMAOMR ); /* Clear the receive flag */
    if (M_Swap16(ETH_receive->head_eth_udp.udp_dest) == D_UDP_DEST_CMD)
    {
        frame_received=1;
        memcpy(&payload_save, ETH_receive->payload, sizeof(payload_save)); /* Copy the received data to the receive buffer */
    }
    RX_DESC->RDES0 |= E_BIT_ENABLE << D_OFFSET_RDES0_OWN; /* Set the ownership bit back to DMA */
        
}
