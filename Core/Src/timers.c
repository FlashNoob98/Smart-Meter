#include <my_structures.h>

void delay_us(unsigned short us){
	TIM3->CEN=0; //Spegni timer
	TIM3->CNT = 0;//resetta timer 3
	TIM3->ARR = us; //Imposta ARR pari al valore da aspettare in us
	TIM3->CEN=1; //Avvia timer
	while((TIM3->UIF==0));//Verifica quando avviene l'overflow
	TIM3->UIF=0;
}

void delay_ms(unsigned int ms){
	TIM2->CEN=0; //Spegni timer
	TIM2->CNT = 0;//resetta timer 2
	TIM2->ARR = ms;
	TIM2->CEN=1;
	while((TIM2->UIF==0)); //Verifica quando avviene l'overflow (500us)
	TIM2->UIF=0;
}

char check_ten_sec(){
	if (TIM6->UIF){
		TIM6->UIF=0;
		return 1;
	} else
		return 0;
}

char check_one_sec(){
	if(TIM7->UIF){
		TIM7->UIF=0;
		return 1;
	} else
		return 0;
}

void init_timers(){
	RCC->TIM2EN = 1; //enable timer 2
	RCC->TIM3EN = 1; //Enable timer 3
	RCC->TIM4EN = 1; //Enable timer 4
	RCC->TIM6EN = 1; //Enable timer 6
	RCC->TIM7EN = 1; //Enable timer 7

	//Timer 10 secondi
	TIM6->PSC=1223; //6535 Hz timer
	TIM6->ARR=65358; //10 s
	TIM6->CEN=1; //Avvia timer

	//Timer 1 secondo
	TIM7->PSC=127; //62500 Hz
	TIM7->ARR=62499; //1 secondo
	TIM7->CEN=1; //Avvia timer

	TIM2->PSC=7999; // 8 MHz to 1 khz timer ms

	TIM3->PSC=7; // 8 MHz to 1MHz -> timer us

	TIM4->CEN=1; //Avvia timer 4 (ADC)

}


