/*
 * interrupt.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */
#include "interrupt.h"

/* Local Types */

/* Public functions */
/**
 * @brief RCC_enable_eth_clock
 * 
 * - Enable required interrupt in NVIC register 
 * 
 * @param [in,out] io_NVIC_drv : pointer to NVIC registers
 * @param [in] i_interrupt_id : GPIO bank required to be set 
 * 
 * @return status, 0 if i_interrupt_id is valid -1 otherwise 
 * 
 **/
int32_t NVIC_enable_interrupt(t_NVIC_registers_s *io_NVIC_drv, enum_E_INTERRUPT_ID i_interrupt_id)
{
    uint32_t word_index = i_interrupt_id / D_LENGTH_32; 
    uint32_t bit_position = i_interrupt_id % D_LENGTH_32; 
    int status = E_STATUS_OK;
    if (i_interrupt_id > D_MAX_INTERRUPT_NUMBER) {       
        status = E_STATUS_ERROR; 
    }
    

    if (status == E_STATUS_OK) { 
        io_NVIC_drv->ISER[word_index] = (E_BIT_ENABLE << bit_position); 
    }
    return status;
}