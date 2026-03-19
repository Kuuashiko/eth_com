/*
 * RCC.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_ETH_H_
#define INC_ETH_H_
#include "stdio.h"
#include "sys/types.h"

/* Macros */
#define M_Swap16(word_16)   (                      \
                                ((word_16) << 8) | \
                                ((word_16) >> 8)   \
                            )

#define M_Swap32(word_32)   (                                     \
                                ((word_32) << 24) & 0xFF000000U | \
                                ((word_32) << 8)  & 0x00FF0000U | \
                                ((word_32) >> 8)  & 0x0000FF00U | \
                                ((word_32) >> 24) & 0x000000FFU   \
                            )


/* Locals Constants */
#define D_ETH_ADDR                    0x40028000U



/* MAC mapping*/
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
}t_MAC_regs;

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
}t_MMC_regs;

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
}t_PTP_regs;

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
}t_DMA_regs;

/* Mapping of all ETHERNET registers*/
typedef struct ETH_regs {
	t_MAC_regs MAC;
    uint32_t res_1[40];
	t_MMC_regs MMC;
	uint32_t res_2[334];
    t_PTP_regs PTP;
    uint32_t res_3[565];
    t_DMA_regs DMA;
}t_ETH_regs;

typedef struct TX_descriptor {
    uint32_t TDES0;
    uint32_t TDES1;
    uint32_t TDES2;
    uint32_t TDES3;
}t_TX_descriptor;

typedef struct RX_descriptor {
    uint32_t RDES0;
    uint32_t RDES1;
    uint32_t RDES2;
    uint32_t RDES3;
}t_RX_descriptor;

typedef struct HEAD_ETH_UDP {
    uint16_t mac_dest[3];
    uint16_t mac_source[3];
    uint16_t protocol;
    uint8_t version_ihl;
    uint8_t dsc_esn;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_offset;
    uint8_t ttl;
    uint8_t protocol_ip;
    uint16_t header_checksum;
    uint32_t ip_src;
    uint32_t ip_dest;
    uint16_t udp_src;
    uint16_t udp_dest;
    uint16_t length;
    uint16_t checksum;

}t_HEAD_ETH_UDP;

typedef struct FRAME_ETH {
    t_HEAD_ETH_UDP head_eth_udp;
    uint8_t *payload;   /* Pointer to the payload data, can be up to 1472 bytes for Ethernet frames */
}t_FRAME_ETH;   

/* Extern variables */
extern t_HEAD_ETH_UDP head_eth_udp;

/* public functions prototypes */
void ETH_conf(t_ETH_regs *ETH_regs);
void set_mac_params (t_MAC_regs *MAC);
void init_desc_eth(t_TX_descriptor *TX_DSC, t_RX_descriptor *RX_DSC, uint8_t *ETH_SEND, uint8_t *ETH_RECEIVE );
void set_dma_config (t_DMA_regs *DMA,t_TX_descriptor *TX_DSC, t_RX_descriptor *RX_DSC);

#endif /* INC_ETH_H_ */
