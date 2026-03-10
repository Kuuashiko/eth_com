/*
 * RCC.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_SYSCFG_H_
#define INC_SYSCFG_H_
#include "stdio.h"
#include "sys/types.h"
/* Locals Constants */

#define D_SYSCFG_ADDR                    0x40020000U

#define D_OFFSET_MODE_SPEED_PUPD0        0U
#define D_OFFSET_MODE_SPEED_PUPD1        2U
#define D_OFFSET_MODE_SPEED_PUPD2        4U
#define D_OFFSET_MODE_SPEED_PUPD3        6U
#define D_OFFSET_MODE_SPEED_PUPD4        8U
#define D_OFFSET_MODE_SPEED_PUPD5        10U
#define D_OFFSET_MODE_SPEED_PUPD6        12U
#define D_OFFSET_MODE_SPEED_PUPD7        14U
#define D_OFFSET_MODE_SPEED_PUPD8        16U
#define D_OFFSET_MODE_SPEED_PUPD9        18U
#define D_OFFSET_MODE_SPEED_PUPD10       20U
#define D_OFFSET_MODE_SPEED_PUPD11       22U
#define D_OFFSET_MODE_SPEED_PUPD12       24U
#define D_OFFSET_MODE_SPEED_PUPD13       26U
#define D_OFFSET_MODE_SPEED_PUPD14       28U
#define D_OFFSET_MODE_SPEED_PUPD15       30U

#define D_OFFSET_OTYPE_IDR_ODR_LOCK0     0U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK1     1U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK2     2U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK3     3U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK4     4U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK5     5U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK6     6U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK7     7U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK8     8U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK9     9U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK10    10U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK11    11U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK12    12U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK13    13U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK14    14U
#define D_OFFSET_OTYPE_IDR_ODR_LOCK15    15U
#define D_OFFSET_LCCK                    16U

#define D_OFFSET_SET_RESET0              0U
#define D_OFFSET_SET_RESET1              1U
#define D_OFFSET_SET_RESET2              2U
#define D_OFFSET_SET_RESET3              3U
#define D_OFFSET_SET_RESET4              4U
#define D_OFFSET_SET_RESET5              5U
#define D_OFFSET_SET_RESET6              6U
#define D_OFFSET_SET_RESET7              7U
#define D_OFFSET_SET_RESET8              8U
#define D_OFFSET_SET_RESET9              9U
#define D_OFFSET_SET_RESET10             10U
#define D_OFFSET_SET_RESET11             11U
#define D_OFFSET_SET_RESET12             12U
#define D_OFFSET_SET_RESET13             13U
#define D_OFFSET_SET_RESET14             14U
#define D_OFFSET_SET_RESET15             15U
#define D_OFFSET_SET_RESET16             16U
#define D_OFFSET_SET_RESET17             17U
#define D_OFFSET_SET_RESET18             18U
#define D_OFFSET_SET_RESET19             19U
#define D_OFFSET_SET_RESET20             20U
#define D_OFFSET_SET_RESET21             21U
#define D_OFFSET_SET_RESET22             22U
#define D_OFFSET_SET_RESET23             23U
#define D_OFFSET_SET_RESET24             24U
#define D_OFFSET_SET_RESET25             25U
#define D_OFFSET_SET_RESET26             26U
#define D_OFFSET_SET_RESET27             27U
#define D_OFFSET_SET_RESET28             28U
#define D_OFFSET_SET_RESET29             29U
#define D_OFFSET_SET_RESET30             30U
#define D_OFFSET_SET_RESET31             31U

#define D_OFFSET_ALTERNATE_FUNCTION0_8   0U 
#define D_OFFSET_ALTERNATE_FUNCTION1_9   4U
#define D_OFFSET_ALTERNATE_FUNCTION2_10  8U
#define D_OFFSET_ALTERNATE_FUNCTION3_11  12U
#define D_OFFSET_ALTERNATE_FUNCTION4_12  16U
#define D_OFFSET_ALTERNATE_FUNCTION5_13  20U
#define D_OFFSET_ALTERNATE_FUNCTION6_14  24U
#define D_OFFSET_ALTERNATE_FUNCTION7_15  28U


typedef enum mode{
	E_INPUT,
	E_GEN_PURP_OUT,
	E_ALT_FUNCT,
	E_ANALOG
}t_MODER_mode;

typedef enum type{
	E_PUSH_PULL,
	E_OPEN_DRAIN
}t_TYPER_mode;

typedef enum speed{
	E_LOW_SPEED,
	E_MED_SPEED,
	E_HIGH_SPEED,
	E_VERY_HIGH_SPEED
}t_SPEED_mode;

typedef enum up_down{
	E_NO_PULLUP_PULLDOWN,
	E_PULLUP,
	E_PULLDOWN
}t_PUPDR_mode;

typedef enum odr{
	E_NO_ACTION,
	E_SET_RESET,
}t_ODR_mode;

typedef enum lock{
	E_UNLOCK,
	E_LOCK
}t_LOCK_mode;

typedef enum alt_func{
	E_AF0,
	E_AF1,
	E_AF2,
	E_AF3,
	E_AF4,
	E_AF5,
	E_AF6,
	E_AF7,
	E_AF8,
	E_AF9,
	E_AF10,
	E_AF11,
	E_AF12,
	E_AF13,
	E_AF14,
	E_AF15,
}t_ALT_FUNCT_mode;

/* Struct RCC register map */
typedef struct GPIOx_registers {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFLR;
	uint32_t AFHR;
	uint32_t reserved[246];
}t_GPIOx_registers;

typedef struct GPIO_Bank {
	t_GPIOx_registers GPIOA;
    t_GPIOx_registers GPIOB;
	t_GPIOx_registers GPIOC;
	t_GPIOx_registers GPIOD;
	t_GPIOx_registers GPIOE;
	t_GPIOx_registers GPIOF;
	t_GPIOx_registers GPIOG;
	t_GPIOx_registers GPIOH;
	t_GPIOx_registers GPIOI;
	t_GPIOx_registers GPIOJ;
	t_GPIOx_registers GPIOK;
}t_GPIO_Bank;


/* Public functions prototypes */

void GPIO_init_ETH(t_GPIO_Bank *GPIOs);


#endif /* INC_RCC_H_ */
