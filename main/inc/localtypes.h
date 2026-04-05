/*
 * localtypes.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_LTYPES_H_
#define INC_LTYPES_H_

#define D_BIT_0           0x00000001U
#define D_BIT_1           0x00000002U
#define D_BIT_2           0x00000004U
#define D_BIT_3           0x00000008U
#define D_BIT_4           0x00000010U
#define D_BIT_5           0x00000020U
#define D_BIT_6           0x00000040U
#define D_BIT_7           0x00000080U
#define D_BIT_8           0x00000100U
#define D_BIT_9           0x00000200U
#define D_BIT_10          0x00000400U
#define D_BIT_11          0x00000800U
#define D_BIT_12          0x00001000U
#define D_BIT_13          0x00002000U
#define D_BIT_14          0x00004000U
#define D_BIT_15          0x00008000U
#define D_BIT_16          0x00010000U
#define D_BIT_17          0x00020000U
#define D_BIT_18          0x00040000U
#define D_BIT_19          0x00080000U
#define D_BIT_20          0x00100000U
#define D_BIT_21          0x00200000U
#define D_BIT_22          0x00400000U
#define D_BIT_23          0x00800000U
#define D_BIT_24          0x01000000U
#define D_BIT_25          0x02000000U
#define D_BIT_26          0x04000000U
#define D_BIT_27          0x08000000U
#define D_BIT_28          0x10000000U
#define D_BIT_29          0x20000000U
#define D_BIT_30          0x40000000U
#define D_BIT_31          0x80000000U

#define D_MAX_UINT32      0xFFFFFFFFU

typedef enum BIT_STATE {
    E_BIT_DISABLE,
    E_BIT_ENABLE
}enum_E_BIT_STATE;

typedef enum status {
    E_STATUS_OK = 0,
    E_STATUS_ERROR = -1
}enum_STATUS;

#endif /* INC_RCC_H_ */