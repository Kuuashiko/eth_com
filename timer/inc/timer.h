/*
 * TIMER.h
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "sys/types.h"
#include "localtypes.h"
/* Locals Constants */

#define D_TIMER_ADDR                    0x40000000U /* Base adress of Timer registers*/
#define D_PERIOD_TICKS                  100U /* Number of timer ticks for the desired period in microseconds */
#define D_TIMER_CLOCK_FREQ              16U /* Timer clock frequency in MHz */
#define D_CEN_BIT                       0x00000001U /* Bit for start/stop Timer in CR1*/
#define D_RESET_VALUE                   0U
#define D_BIT_UG                        D_BIT_0



/* Struct TIMERx register map */
typedef struct TIMERx_registers {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
    uint32_t reserved_1;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
    uint32_t reserved_2;
    uint32_t DCR;
    uint32_t DMAR;
    uint32_t OR; /* Option register, only for TIM2 and TIM5 */
    uint32_t reserved_3[235]; /* Reserved space to align the structure to the size of the timer register map */
}t_TIMERx_registers_s;


typedef struct TIMER_Bank {
    t_TIMERx_registers_s TIM2;
    t_TIMERx_registers_s TIM3;
    t_TIMERx_registers_s TIM4;
    t_TIMERx_registers_s TIM5;
}t_TIMER_Bank_s;
/* Public functions prototypes */

void TIMER_init(t_TIMERx_registers_s *io_TIMx, uint32_t i_prescaler, uint32_t i_auto_reload);
void TIMER_start(t_TIMERx_registers_s *io_TIMx);
void TIMER_reset(t_TIMERx_registers_s *io_TIMx);
uint32_t TIMER_get_value(t_TIMERx_registers_s *io_TIMx);
int32_t TIMER_compute_prescaler(uint32_t i_period_us, uint32_t *o_prescaler);

#endif /* INC_RCC_H_ */
