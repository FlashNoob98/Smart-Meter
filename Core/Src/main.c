#include <my_structures.h>
#include <math.h>
#include <display.h>
#include <timers.h>
#include <usart.h>
#include <stdio.h>


//#define PI 3.14159265358

//#define GPIOAEN (1<<17)
//#define GPIOEEN (1<<21)
//#define LED_BLU (1<<8)

#define Input 0	//0b00
#define Output 1	//0b01
#define Alternate 2	//0b10
#define Analog 3	//0b11

unsigned char animazione_led(unsigned char);

void init_ADC(ADC_Type *,int);

void esegui_misura(unsigned int *misura, unsigned short *tensione, unsigned short *corrente, float *rms_V, float *rms_I, float *P_A, float *S, float *Q);

void invia_valore(unsigned short, char);
float mean(unsigned short*); //Definisci media

float rms(unsigned short*);

//static float misura;
float potenza_attiva(unsigned short *,unsigned short *);

void misura_a_display(float rms_V, float rms_I, float P_A, float Q, float S,float Energy,unsigned int secondi);

void invia_uart(unsigned short *tensione,unsigned short *corrente, float rms_V, float rms_I, float P_A, float Q,float S);

#define NCampioni 400
#define Gain_V 0.413560
#define Gain_I 0.030623

int main(void){
	unsigned char clear = 0;
	unsigned int misura[NCampioni];
	unsigned short tensione[NCampioni];
	unsigned short corrente[NCampioni];
	float rms_V = 0;
	float rms_I = 0;
    float P_A=0;
    float Q=0;
    float S=0;
    float Energy=0;
    unsigned int secondix10=0;
    unsigned int secondi = 0; // Overflow dopo 136 anni


	//Abilita il clock per GPIOA e GPIOE
	//RCC->AHBENR|=GPIOAEN|GPIOEEN; //Enable GPIOE e GPIOA
	RCC->GPIOAEN = 1; //EnableGPIOA
	RCC->GPIODEN = 1; //Enable GPIOD

	init_timers(); // Inizializza timer 2-3-4

	RCC->GPIOCEN = 1; //Enable GPIOC
	RCC->USART1EN=1; //Enable USART1
	GPIOC->MODER4 = Alternate; //USART1 TX
	GPIOC->MODER5 = Alternate; //USART1 RX
	GPIOC->AFRLAFR4 = 0b0111; //Usart Alternate function FA7
	GPIOC->AFRLAFR5 = 0b0111; //Usart function FA7

	USART1->BRR = 833;//Definisci Baudrate USART ovvero 9600 bps con fck 8MHz
	USART1->UE=1; //UE = 1 abilita Usart 1

	GPIOA->MODER4 = Analog; //DAC metti pin 4 in modalità analogica

	GPIOA->MODER1 = Analog; //Modalià analogica PA1 (ADC1 channel 2)
	GPIOA->MODER5 = Analog; //Abilita modalità analogica su pin PA5 (ADC2)

	RCC->DAC1EN=1; //Abilita il DAC
	DAC1->DACC1DHRR1 = 2048; //Valore iniziale
	DAC1->EN1=1; //EN1 Abilita canale 1 Dac 1
	DAC1->BOFF1=1; //Disabilitazione buffer (carico alta impedenza)

	RCC->ADC12EN = 1; //Abilita ADC12 nell'RCC
	ADC12->CKMODE = 0b01; //CKMODE 01 syncronous clock mode
	ADC12->DUAL = 0b00110; //Modalità sincrona degli ADC



	//Abilito i timer
	RCC->GPIOEEN = 1; //Enable GPIOE
	//GPIOE->MODER8 = Output;//Output MODE Led 8
	GPIOE->MODER = 0x55550000; //led output da 8 a 15
	//RCC->TIM2EN=1; //enable timer2

	init_lcd();
	delay_ms(200);
	lcd_clear(); // Pulisci display
	delay_ms(500);

	lcd_hello_world();

	delay_ms(2000); //Attendi 2 secondi..
	//unsigned int y[NCampioni];
	//float x = 0.0;
	//float dx = (float)(2*M_PI/NCampioni);

	//for (int i=0; i<NCampioni; i++){
		//y[i] = (unsigned int)(2048+(2047*sinf(x)));
		//y[i] = 4094;
		//x = x + dx;
		//DAC1->DACC1DHRR1 = y[i];
	//}//END FOR

	// Attendi 10 us - superfluo ho i wait del display
//	while(TIM4->UIF){ //Verifica quando avviene l'overflow (500ms)
//		TIM4->UIF = 0;
//	}

	init_ADC(ADC1,2); //Inizializza e calibra ADC1 canale 2
	init_ADC(ADC2,2); //Inizializza e calibra ADC2 canale 2

	USART1->TE=1; //Abilita trasmissione USART
	USART1->RE=1; //Abilita ricezione
    //Fine setup

	//TIM4->ARR=1125;
	//TIM4->ARR=1599; //Arr 100 campioni per periodo 5kHz (5.01 reale)
	TIM4->ARR=799; //ARR 200 campioni (10kHz)
	//TIM4->ARR=399; //ARR con 400 campioni (20kHz)
	TIM4->CEN=1;


	while(1){	//Main loop

		secondi += check_one_sec(); //Aggiungi un secondo
		secondix10 += check_ten_sec(); //Aggiungi 10 secondi

		esegui_misura(misura,tensione,corrente, &rms_V, &rms_I, &P_A, &S, &Q);

		if(secondix10){
			Energy += P_A*10/3600/1000; //Accumula energia
		}

		clear = animazione_led(clear);

		//usart_read();

		misura_a_display(rms_V,rms_I,P_A,Q,S,Energy,secondi);

		invia_uart(tensione,corrente,rms_V,rms_I,P_A,Q,S);


	}//end while
}//END MAIN

unsigned char animazione_led(unsigned char clear){

	LED_8 = 1; //Accendi LED 8
	//while(!USER_BTN){
		//GPIOE->ODR = (GPIOE->ODR)+(1<<8); Messo qui mostra una combinazione "casuale" ogni volta che trattieni il tasto
	//if(TIM4->UIF){ //Verifica quando avviene l'overflow
		if (clear){
			GPIOE->ODR|=0x0080; //Riparti dal led 7 (Solo animazione orologio
			GPIOE->ODR=0; //Spegni tutto (Entrambe le animazioni o solo accumulo)
			clear = 0;
		//}
		//TIM4->UIF = 0; //Reimposta UIF ovvero accetta evento di overflow
		//LED_8 ^= 1; //Commuta LED 8
		GPIOE->ODR = ((GPIOE->ODR)<<1); //ANIMAZIONE "orologio"
		GPIOE->ODR = (GPIOE->ODR)+(1<<8); //ANIMAZIONE "accumulo binario"
		if (((GPIOE->ODR)==(0xff00))||((GPIOE->ODR)==(0x0000))){ //Quando termini i LED riparti dal numero 8
			clear = 1;
		}//Durante la misura
	};
	return clear;
}

void init_ADC(ADC_Type *ADC, int channel){
	ADC->ADVREGEN = 0b00;//Attiva regolatore di tensione fase intermedia
	ADC->ADVREGEN = 0b01;//Attiva regolatore di tensione accensione
	delay_us(20);

	ADC->DIFSEL=(0<<channel); //Single ended canale 1
	//ADC2->DIFSEL=(0<<1); //Imposta in single ended il secondo canale dell ADC2

	//Calibrazione
	ADC->ADEN=0; //Spegni ADC (superfluo la prima volta)
	ADC->ADCALDIF=0;//Imposta calibrazione single ended
	ADC->ADCAL=1; //Avvia
	while (ADC->ADCAL!=0); //Attendi termine calibrazione

	//Abilitazione ADC
	ADC->ADEN=1; //Abilita ADC
	while (ADC->ADRDY!=1); //Attendi commutazione Ready
	ADC->ADRDY=0; //Riabbassa bit ready (per eventuali acquisizioni successive)

	//Definizione sequenza di acquisizione
	ADC->L=0; //Lunghezza azquisizione = 1(-1), un solo canale
	ADC->SQ1=channel; //Canale 1 nella posizione di sequenza 1

	//Impostare il tempo di sampling (sul canale 2)
	//ADC2->SMP2 = 7; // (0b111) 601.5 volte il clock dell'ADC
	//ADC->SMP2 = 2;
	if (channel < 10) {
		ADC->SMPR1 = (6<<((channel)*3));
	}
	else {
		ADC->SMPR2 = (6<<((channel-10)*3));
	}

}


void esegui_misura(unsigned int *misura, unsigned short *tensione, unsigned short *corrente, float *rms_V, float *rms_I, float *P_A, float *S, float *Q){
	//unsigned int misura[]=0;
	for (int i=0; i<NCampioni;i++){ //Acquisisci campioni
		//DAC1->DACC1DHRR1 = y[i];
		while(TIM4->UIF==0);
		ADC1->ADSTART=1; //Inizia conversione (è il master ad avviare la conversione)
		TIM4->UIF=0;
		while (ADC1->EOC!=1); //Attendi fine conversione (sempre del master)
		misura[i] = ADC12->CDR;
	}
	for (int i=0; i<NCampioni;i++){ //Invia dati (da mettere in un if con lettura RX)
		tensione[i] = misura[i];  // channel on master
		corrente[i] = (misura[i]>>16); // channel on slave
	}
	*rms_V = rms(tensione)*Gain_V; //Calcola rms tensione
	*rms_I = rms(corrente)*Gain_I;
	*P_A=potenza_attiva(tensione,corrente);
	*S = (*rms_V)*(*rms_I); //Potenza apparente
	*Q = (*S)-(*P_A); //Potenza reattiva
}

void invia_valore(unsigned short valore, char A){
	char a;
	char b;
	a = valore;
	b = (valore>>8);
	//usart_send(0xFF);
	usart_send(0xFF);
	usart_send(A);
	//usart_send(preambolo);
	usart_send(a);
	usart_send(b);
}

float mean(unsigned short *valori){
	float somma = 0;
	for (int i = 0; i<NCampioni; i++){
		somma += valori[i]; //Somma dei valori
	}
	return (somma/NCampioni); //Media
}

float rms(unsigned short *valori){
	float media = mean(valori); //Calcola media
	float quadrati=0; //Inizializza RMS
	for (int i = 0; i<NCampioni; i++){
		quadrati += pow(valori[i]-media,2); //Calcolo dei quadrati
	}
	return sqrtf(quadrati/NCampioni); //Ritorna radice quadrata
}

float potenza_attiva(unsigned short *tensione,unsigned short *corrente){
	float media_v = mean(tensione);
	float media_i = mean(corrente);
	float v_0[NCampioni];
	float i_0[NCampioni];
	float P_ist = 0.0;
	for (int i = 0; i<NCampioni; i++){
			v_0[i] = (tensione[i]-media_v)*Gain_V; //Calcolo media
			i_0[i] = (corrente[i]-media_i)*Gain_I;

			P_ist += v_0[i]*i_0[i];
		}
	   return P_ist/NCampioni;
}

void misura_a_display(float rms_V, float rms_I, float P_A, float Q, float S,float Energy,unsigned int secondi){
	char buffer[32];
	lcd_clear();
	lcd_put_cur(1,0);
	snprintf(buffer,sizeof(buffer),"P:%3.1fW Q:%3.1fVar",P_A,Q);
	lcd_send_string(buffer);
	lcd_put_cur(2,0);
	snprintf(buffer,sizeof(buffer),"S:%3.1fVA E:%3.1fVar",S,Energy);
	lcd_send_string(buffer);
	lcd_put_cur(3,0);
	snprintf(buffer,sizeof(buffer),"Uptime: %02dG %02d:%02d:%02d",(int)(secondi/86400),(int)(secondi%86400/3600),(int)((secondi%3600)/60),(int)(secondi%60));
	lcd_send_string(buffer);
}

void invia_uart(unsigned short *tensione,unsigned short *corrente, float rms_V, float rms_I, float P_A, float Q,float S){
	for (int i=0; i<NCampioni;i++){
		invia_valore(round((tensione[i])*Gain_V),'A'); //Invia campioni qui
		invia_valore(round((corrente[i])*Gain_I),'B');
	}
	invia_valore((unsigned)rms_V,'C');
	invia_valore((unsigned)rms_I,'D');
	invia_valore((unsigned)P_A,'E');
	invia_valore((unsigned)Q,'F');
	invia_valore((unsigned)S,'G');

}


