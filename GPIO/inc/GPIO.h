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

#define D_SYSCFG_ADDR      0x40020000U

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
