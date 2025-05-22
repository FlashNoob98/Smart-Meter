#include <my_structures.h>

void delay_us(int us){
	if (us>1){
	TIM3->ARR = us-1;
	}
	else {
		TIM3->ARR=1;
	}
	TIM3->UIF=0;
	TIM3->CNT=0;
	TIM3->CEN=1;
	//TIM3->UIF = 0;
	while((TIM3->UIF)==0);//Verifica quando avviene l'overflow (500us)
	TIM3->UIF=0;
	TIM3->CEN=0;
}

void delay_ms(int ms){
	if (ms>1){
		TIM2->ARR = ms-1;
	}
	else{
		TIM2->ARR=1;
	}
	TIM2->CNT = 0;//resetta timer 6
	TIM2->UIF=0;
	TIM2->CEN=1;
	//TIM2->UIF = 0;
	while((TIM2->UIF)==0); //Verifica quando avviene l'overflow (500us)
	TIM2->UIF=0;
	TIM2->CEN=0;

}


void delay_us2(int us){
	TIM2->ARR=8*us;
	TIM2->CEN=1;
	while((TIM2->UIF)==0); //Verifica quando avviene l'overflow (500us)
	TIM2->UIF=0;
	//TIM2->CEN=0;
	TIM2->CNT=0;
}

void init_timers(){
	RCC->TIM2EN = 1; //enable timer 6
	RCC->TIM3EN = 1; //Enable timer 3
	RCC->TIM4EN=1; //Enable timer 4

	//TIM4->PSC = 63;
	//TIM4->ARR=62500;
	//TIM4->CEN=1;

	TIM3->PSC=0; // 8 MHz to 100khz
	TIM4->PSC=0;
	//TIM2->PSC=7999; // 8 MHz to 1Khz
	//TIM2->CEN = 1;
	//TIM6->ARR = (unsigned int) 62500; //500ms ovvero 4000000 count
	//TIM6->PSC = (unsigned int) 63;
	delay_us(1);
	delay_ms(1);
}


