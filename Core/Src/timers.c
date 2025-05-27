#include <my_structures.h>

void delay_us(unsigned short us){
	TIM3->CEN=0;
	TIM3->CNT = 0;//resetta timer 2
	TIM3->ARR = us;
	TIM3->CEN=1;
	//TIM3->CEN=1;
	//TIM3->UIF = 0;
	while((TIM3->UIF==0));//Verifica quando avviene l'overflow (500us)
	TIM3->UIF=0;
	//TIM3->CEN=0;
}

void delay_ms(unsigned int ms){
	TIM2->CEN=0;
	TIM2->CNT = 0;//resetta timer 2
	TIM2->ARR = ms;
	TIM2->CEN=1;
	//TIM2->CEN=1;
	//TIM2->UIF = 0;
	while((TIM2->UIF==0)); //Verifica quando avviene l'overflow (500us)
	TIM2->UIF=0;
	//TIM2->CEN=0;

}


void init_timers(){
	RCC->TIM2EN = 1; //enable timer 2
	RCC->TIM3EN = 1; //Enable timer 3
	RCC->TIM4EN = 1; //Enable timer 4

	//TIM4->PSC = 63;
	//TIM4->ARR=62500;
	//TIM4->CEN=1;
	TIM2->PSC=7999; // 8 MHz to 1 khz
	TIM3->PSC=7; // 8 MHz to 1MHz -> us timer

	TIM4->PSC=0; // Timer per ADC
	//TIM2->CEN=1;
	//TIM3->CEN=1;
	TIM4->CEN=1;
	//TIM2->PSC=7999; // 8 MHz to 1Khz
	//TIM2->CEN = 1;
	//TIM6->ARR = (unsigned int) 62500; //500ms ovvero 4000000 count
	//TIM6->PSC = (unsigned int) 63;
	delay_us(2);
	delay_ms(2);
}


