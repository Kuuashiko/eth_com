/*
 * ETH_constants.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_ETH_CONSTANTS_H_
#define INC_ETH_CONSTANTS_H_
#include "sys/types.h"

/* General Constants */
#define D_ETH_ADDR                      0x40028000U /* Eth registers base address */
#define D_ETH_HEADER_SIZE               14U /* Ethernet header size in bytes */
#define D_IP_HEADER_SIZE                20U /* IP header size in bytes */
#define D_UDP_HEADER_SIZE               8U  /* UDP header size in bytes */
#define D_HEADER_LENGTH                 (D_ETH_HEADER_SIZE + D_IP_HEADER_SIZE + D_UDP_HEADER_SIZE) /* Ethernet header (14 bytes) + IP header (20 bytes) + UDP header (8 bytes) */
#define D_BUFFER_SEND_ADDR              0x2004D000U /* Address of the send buffer */
#define D_BUFFER_RECEIVE_ADDR           0x2004E000U /* Address of the receive buffer */
#define D_IP_HEADER_LENGTH              20U
#define D_MAX_ETH_SIZE                  1536U /* Maximum Ethernet frame size (including header and CRC) */
#define D_PING_HEX_VALUE                0x50494E47U /* "PING" in ASCII */
#define D_SEND_VALUE                    1U
#define D_MAX_PAYLOAD_SIZE              1472U

/* Offsets for ETH registers used*/
/* MAC register description : 38.8.1*/
/* ETH_MACCR*/
#define D_OFFSET_RE_MACCR               2U /* bit for enable Receive*/
#define D_OFFSET_TE_MACCR               3U /* bit for enable Transmit*/
#define D_OFFSET_DM_MACCR               11U /* bit for enable Duplex mode*/
#define D_OFFSET_FES_MACCR              14U /* bit for set speed at 100 mb */

/* ETH_MACFFR*/
#define D_OFFSET_PAM_MACFFR             4U /* bit for receive multicast  */
#define D_OFFSET_PA_MACFFR              31U /* bit for receive all  */

/* DMA register description : 38.8.4*/
/* ETH_DMAOMR */
#define D_OFFSET_SR_DMAOMR              1U /* bit for start/stop reception of frames */
#define D_OFFSET_ST_DMAOMR              13U /* bit for start/stop transmission of frames */
#define D_OFFSET_TSF_DMAOMR             21U /* bit for transmit store & forward */

/* ETH_DMAIER */
#define D_OFFSET_RIE_DMAIER             6U /* bit for receive interrupt enable */
#define D_OFFSET_NISE_DMAIER            16U /* bit for normal interrupt summary enable */

/* ETH_DMASR */
#define D_OFFSET_RS_DMAOMR              6U /* bit for receive status */

/* IP/UDP Constants */
#define D_MAC_DEST_BROADCAST            0xFFFFU
#define D_MAC_SOURCE_0                  0x4D4FU /* "MO" in ASCII */
#define D_MAC_SOURCE_1                  0x4E41U /* "NA" in ASCII */
#define D_MAC_SOURCE_2                  0x434FU /* "CO" in ASCII */
#define D_ETHERTYPE_IPV4                0x0800U /* Ethertype for IPv4 */
#define D_IP_VERSION_IHL                0x4500U /* Version 4, IHL 5 (20 bytes) , Default value for DSCP and ECN */
#define D_IDENTIFICATION                0x1234U /* identification */
#define D_FLAGS_OFFSET                  0x4000U /* flags and fragment offset */
#define D_TTL_PROT_IP                   0x4011U /* TTL and protocol UDP */
#define D_IP_SRC                        0xC0000000U /*  source IP */
#define D_IP_DEST                       0xC0000001U /*  destination IP */  
#define D_UDP_SRC                       0x0310U /* Example source port */
#define D_UDP_DST                       0x1994U /* Example destination port */
#define D_UDP_DEST_CMD                  0x1103U /* UDP destination port for commands */

/* Ethernet Descriptors */
/* Chapters 38.6.7 Tx Configuration  & 38.6.8 Rx Configuration */
#define D_ADDR_DSC_TX                   0x2004C000U /* Rx Descriptor address */
#define D_ADDR_DSC_RX                   0x2004C020U /* Tx Descriptor address */

/* Offset for TDES0 */
#define D_OFFSET_TDES0_OWN              31U /* bit for the ownership of the descriptor */
#define D_OFFSET_TDES0_LS               29U /* bit to indicate the last segment of the frame */ 
#define D_OFFSET_TDES0_FS               28U /* bit to indicate the first segment of the frame */
#define D_OFFSET_TDES0_CIC              22U /* bits for checksum insertion control */
#define D_OFFSET_TDES0_TER              21U /* bit to indicate the end of the ring */

/* Offset for TDES1 */
#define D_DEFAULT_TDES1_CTRL            0x00000000U /* Default control bits for TDES1 */
#define D_MASK_TDES1_TBS1               0x00001FFFU /* Mask for the length field in TDES1 */

/* Offset for RDES0 */
#define D_OFFSET_RDES0_OWN              31U /* bit for the ownership of the descriptor */

/* Offset for RDES1 */
#define D_OFFSET_RBS                    0U /* bits for the receive buffer size */
#define D_OFFSET_RDES1_RCH              14U /* bit to indicates that the adress is the next desc address */
#define D_OFFSET_RDES1_RER              15U /* Bit to indicate the end of the ring */


#endif /* INC_ETH_H_ */