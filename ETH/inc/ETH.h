/*
 * ETH.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_ETH_H_
#define INC_ETH_H_
#include "sys/types.h"
#include "memory.h"
#include "ETH_constants.h"
#include "localtypes.h"

/* Macros */
#define M_Swap16(word_16)   (                                 \
                                (((word_16) << 8) & 0xFF00U )| \
                                (((word_16) >> 8) & 0x00FFU )  \
                            )

#define M_Swap32(word_32)   (                                     \
                                (((word_32) << 24) & 0xFF000000U )| \
                                (((word_32) << 8)  & 0x00FF0000U )| \
                                (((word_32) >> 8)  & 0x0000FF00U )| \
                                (((word_32) >> 24) & 0x000000FFU )  \
                            )




/* MAC mapping*/
/* MAC register description : 38.8.1*/
typedef struct MAC_regs {
    uint32_t CR;
    uint32_t FFR;
    uint32_t HTHR;
    uint32_t HTLR;
    uint32_t MIIAR;
    uint32_t MIIDR;
    uint32_t FCR;
    uint32_t VLANTR;
    uint32_t res_1[2];
    uint32_t RWUFFR;
    uint32_t PMTCSR;
    uint32_t res_2;
    uint32_t DBGR;
    uint32_t SR;
    uint32_t IMR;
    uint32_t A0HR;
    uint32_t A0LR;
    uint32_t A1HR;
    uint32_t A1LR;
    uint32_t A2HR;
    uint32_t A2LR;
    uint32_t A3HR;
    uint32_t A3LR;
}t_MAC_regs_s;

/* MMC mapping*/
/* MMC register description : 38.8.2 */
typedef struct MMC_regs {
    uint32_t CR;
    uint32_t RIR;
    uint32_t TIR;
    uint32_t RIMR;
    uint32_t TIMR;
    uint32_t res_1[14];
    uint32_t TGFSCCR;
    uint32_t TGFMSCCR;
    uint32_t res_2[5];
    uint32_t TGFCR;
    uint32_t res_3[10];
    uint32_t RFCECR;
    uint32_t RFAECR;
    uint32_t res_4[10];
    uint32_t RGUFCR;
}t_MMC_regs_s;

/* PTP mapping */
/* TimeStamp registers : 38.8.3 */
typedef struct PTP_regs {
    uint32_t TSCR;
    uint32_t SSIR;
    uint32_t TSHR;
    uint32_t TSLR;
    uint32_t TSHUR;
    uint32_t TSLUR;
    uint32_t TSAR;
    uint32_t TTHR;
    uint32_t TTLR;
    uint32_t res_1;
    uint32_t TSSR;
}t_PTP_regs_s;

/* DMA mapping */
/* DMA register description : 38.8.4 */
typedef struct DMA_regs {
    uint32_t BMR;
    uint32_t TPDR;
    uint32_t RPDR;
    uint32_t RDLAR;
    uint32_t TDLAR;
    uint32_t SR;
    uint32_t OMR;
    uint32_t IER;
    uint32_t MFBOCR;
    uint32_t RSWTR;
    uint32_t res[8];
    uint32_t CHTDR;
    uint32_t CHRDR;
    uint32_t CHTBAR;
    uint32_t CHRBAR;
}t_DMA_regs_s;

/* Mapping of all ETHERNET registers*/
/* MAC register description : 38.8.5  ( contains full mapping of all sub registers above )*/
typedef struct ETH_regs {
	t_MAC_regs_s MAC;
    uint32_t res_1[40];
	t_MMC_regs_s MMC;
	uint32_t res_2[334];
    t_PTP_regs_s PTP;
    uint32_t res_3[565];
    t_DMA_regs_s DMA;
}t_ETH_regs_s;



/* ETH descriptors */
/* TX desc config : 38.6.7 */
typedef struct TX_descriptor {
    uint32_t TDES0;
    uint32_t TDES1;
    uint32_t TDES2;
    uint32_t TDES3;
}t_TX_descriptor_s;

/* RX desc config : 38.6.8 */
typedef struct RX_descriptor {
    uint32_t RDES0;
    uint32_t RDES1;
    uint32_t RDES2;
    uint32_t RDES3;
}t_RX_descriptor_s;


/* IP/UDP Header */
typedef struct __attribute__((packed)) HEAD_ETH_UDP  {
    uint16_t mac_dest[3];
    uint16_t mac_source[3];
    uint16_t protocol;
    uint16_t ihl_dsc_esn;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_offset;
    uint16_t ttl_prot_ip;
    uint16_t header_checksum;
    uint32_t ip_src;
    uint32_t ip_dest;
    uint16_t udp_src;
    uint16_t udp_dest;
    uint16_t length;
    uint16_t checksum;

}t_HEAD_ETH_UDP_s;

typedef struct FRAME_ETH {
    t_HEAD_ETH_UDP_s head_eth_udp;
    uint8_t payload[D_MAX_PAYLOAD_SIZE];   /* Pointer to the payload data, can be up to 1472 bytes for Ethernet frames */
}t_FRAME_ETH_s;   



/* enumerates */
typedef enum {
    E_CHKSUM_DISABLE,
    E_CHKSUM_IP_HEADER,
    E_CHKSUM_IP_HEADER_PAYLOAD,
    E_CHKSUM_IP_HEADER_PAYLOAD_PSEUDO_HEADER,
} enum_CHKSM_INS_CTRL;

/* public functions prototypes */
void ETH_conf(t_ETH_regs_s *io_ETH_regs);
void ETH_set_frame_length(uint32_t i_length_payload);
void ETH_get_payload(uint8_t o_payload[], uint32_t i_payload_size);
void ETH_set_payload(uint8_t i_payload[], uint32_t i_payload_size);
void ETH_set_ip_dest(uint32_t i_ip_dst);
void ETH_set_ip_src(uint32_t i_ip_src);
void ETH_set_udp_dest(uint16_t i_udp_dest);
void ETH_set_udp_src(uint16_t i_udp_src);
void ETH_set_own_DMA_TX_DESC(void);
void ETH_send_frame(t_DMA_regs_s *io_DMA);
uint32_t ETH_get_receive_flag(void);

#endif /* INC_ETH_H_ */
