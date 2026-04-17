/*
 * timer.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#include "timer.h"

/** 
* @brief TIMER_init                                
* 
* Initialize timer :                                  
*                                                      
* Init timer with prescaler value, auto_reload value
* 
* @param[in,out] io_TIMx    : pointer to the required timer
* @param[in] i_prescaler    : prescaler value to modify the timer frequency
* @param[in] i_auto_reload  : value max of the timer to start again from beginning                                                                                          
*                                                      
* @return void                         
**/ 
void TIMER_init(t_TIMERx_registers_s *TIMx, uint32_t i_prescaler, uint32_t i_auto_reload)
{
    TIMx->PSC = i_prescaler; /* Set the prescaler value */
    TIMx->ARR = i_auto_reload; /* Set the auto-reload value */
    TIMx->EGR = D_BIT_UG;    /* Apply parameters*/
}


/** 
* @brief TIMER_start                                
* 
* Start timer :                                  
*                                                      
* Start the timer given in input by writing CEN bit in the given timer in input
* @warning Timer must have been set with TIMER_init before call 
* 
* @param[in,out] io_TIMx : pointer to the required timer
*                                                                                           
*                                                      
* @return void                         
**/ 
void TIMER_start(t_TIMERx_registers_s *io_TIMx)
{
    io_TIMx->CR1 |= D_CEN_BIT; /* Set the CEN bit to start the timer */
}


/** 
* @brief TIMER_get_value                                
* 
* Get value :                                  
*                                                      
* Get the current count of timer x
* 
* 
* @param[in,out] io_TIMx : pointer to the required timer
*                                                                                           
*                                                      
* @return counter : current value of timer counter                                
**/ 
uint32_t TIMER_get_value(t_TIMERx_registers_s *io_TIMx)
{
    return io_TIMx->CNT;
}

/** 
* @brief TIMER_reset                                
* 
* Stop timer :                                  
*                                                      
* Stop the timer given in input by writing CEN bit in the given timer in input, reset psc and counter values
* 
* 
* @param[in,out] io_TIMx : pointer to the required timer
*                                                                                           
*                                                      
* @return status : 0 if successfully, -1 if the input period is < 100 us  because clock is unstable                                
**/ 
void TIMER_reset(t_TIMERx_registers_s *io_TIMx)
{
    io_TIMx->PSC = D_RESET_VALUE; /* Reset prescaler */
    io_TIMx->CR1 &= ~D_CEN_BIT; /* reset the CEN bit to stop the timer */
    io_TIMx->CNT = D_RESET_VALUE; /* Reset timer count */
}


/** 
* @brief TIMER_compute_prescaler                                 
* 
* Compute prescaler value :                                  
*                                                      
* - Compute the prescaler value for the timer to have 100 ticks per desired period (D_PERIOD_TICKS) in microseconds
* - The timer clock frequency is 16 MHz, and the timer frequency is clock_freq / (prescaler + 1),
* so the prescaler is ((clock_freq * i_period_us) / (D_PERIOD_TICKS) ) - 1U. 
* - If the input period is higher than 100 ms, the prescaler is set to the value for which 1 tick = 1 ms, so the prescaler is
* ((clock_freq * D_100_MS) / (D_PERIOD_TICKS) ) - 1U and the user period input is used as reference to compute the tick period in ms.
* 
* @param[in] i_period_us : period in frame sent by the user in microseconds
* @param[out] o_prescaler : pointer to the computed prescaler value
*                                                                                           
*                                                      
* @return status : 0 if successfully, -1 if the input period is < 100 us  because clock is unstable                            
**/ 
int32_t TIMER_compute_prescaler(uint32_t i_period_us, uint32_t *o_prescaler)
{
    int32_t status = E_STATUS_OK;

    if (i_period_us < D_PERIOD_TICKS_MS)
    {
        *o_prescaler = D_RESET_VALUE; /* Set prescaler to 0 an return an error */
        status = E_STATUS_ERROR; /* Invalid period */
    }
    
    else if (i_period_us <= D_100_MS)
    {
        *o_prescaler = ( (D_TIMER_CLOCK_FREQ * i_period_us) / D_PERIOD_TICKS_US ) - 1U;
    }

    else
    {
        *o_prescaler = ( (D_TIMER_CLOCK_FREQ * D_100_MS) / D_PERIOD_TICKS_MS ) - 1U;
    }

    return status;
}

/**
 * @brief Timer_get_tick_period 
 * 
 * - Get the period in ticks to be used, user input converted in ms if period > 100 ms, 100 ticks otherwise
 * 
 * @param[in] i_period_us : period in frame sent by the user in microseconds
 * @param[out] o_tick_period : pointer to the computed tick period value 
 * 
 * @return void
 */
void TIMER_get_tick_period(uint32_t i_period_us, uint32_t *o_tick_period)
{
        if (i_period_us > D_100_MS)
	    {
	    	*o_tick_period = i_period_us/D_US2MS;
	    }
    
	    else
	    {
	    	*o_tick_period = D_PERIOD_TICKS_US;
	    }
}
