/*
 * main.c
 *
 *  Created on: 4 mars 2026
 *      Author: milko
 */

#include "746.h"




int main()
{
    t_TIMER_Bank_s *TIMER_Bank = (t_TIMER_Bank_s *)D_TIMER_ADDR;
    t_ETH_regs_s *ETH_map = (t_ETH_regs_s *)D_ETH_ADDR;
    t_COMMAND_s command;
    t_DATA_s data_to_send;
    data_to_send.data = M_Swap32(D_PING_HEX_VALUE); /* "PING" in ASCII */
    uint32_t time_send = 0, prescaler =0;

    boot();

    ETH_set_payload((uint8_t*)&data_to_send ,sizeof(t_DATA_s));
    ETH_set_frame_length(sizeof(t_DATA_s)); /* Set the frame length in the Ethernet header and TDES1 */
    memset(&command, 0x00, sizeof(t_COMMAND_s));
    

    while (1)
    {
        if (ETH_get_receive_flag() == 1)
        {
            ETH_get_payload((uint8_t*)&command,sizeof(t_COMMAND_s));
            uint32_t cnt_msg = 0, valid_delay=0;

            valid_delay = TIMER_compute_prescaler(command.delay, &prescaler); /* Compute the prescaler value for the specified delay */
            if (valid_delay == E_STATUS_ERROR)
            {
                cnt_msg=D_MAX_UINT32; // put cnt_msg to max int32 to avois send message because of wrong input delay
            }
            TIMER_init(&TIMER_Bank->TIM2, prescaler, D_MAX_UINT32); /* Initialize timer to count by ms*/
            TIMER_start(&TIMER_Bank->TIM2); /* Start timer */
            while ((cnt_msg) < command.nb_msg)
            { 
                if (ETH_get_receive_flag() == 1) /* Check if a new frame has been received during the delay */
                {
                    ETH_get_payload((uint8_t*)&command,sizeof(t_COMMAND_s));
                    if (command.stop == 1)
                    {
                        break; /* Stop sending frames if the stop flag is set */
                    }
                }
                if ((TIMER_get_value(&TIMER_Bank->TIM2) - time_send) >= D_PERIOD_TICKS)  /* Check if the frame has been sent and if 100 ticks has passed delay of 100 ticks depends on frame input*/
                {
                    data_to_send.cnt = M_Swap32(cnt_msg);
                    ETH_set_own_DMA_TX_DESC(); /* Tell DMA that frame is ready to send */
                    ETH_set_payload((uint8_t*)&data_to_send,sizeof(t_DATA_s));
                	time_send = TIMER_get_value(&TIMER_Bank->TIM2);  /* Get the current timer count */
                	cnt_msg++;
                   	ETH_send_frame(&ETH_map->DMA);
                }
            }
            TIMER_reset(&TIMER_Bank->TIM2); // Reset Timer
        }
    }

    
    return 0;
}
