#include <my_structures.h>

#ifndef INC_timers_H_
#define INC_timers_H_

void init_timers(void);

void delay_us(int);

void delay_ms(int);

char check_ten_sec();

char check_one_sec();

#endif /* INC_timers_H_ */
