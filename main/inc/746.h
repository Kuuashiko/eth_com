/* general header
 *
 * 746.h 
 * Created on: 4 mars 2026
 *      Author: milko
  */

#ifndef INC_746_H_
#define INC_746_H_

/* Librairies */
#include "memory.h"


/* header customs */
#include "timer.h"
#include "boot.h"

/* command data structure*/
typedef struct command {
    uint32_t nb_msg;
    uint32_t delay;
    uint32_t stop;
    }t_COMMAND_s;

typedef struct data {
    uint32_t data;
    uint32_t cnt;
}t_DATA_s;

#endif /* INC_746_H_ */