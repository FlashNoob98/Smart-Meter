#include <my_structures.h>
#include <math.h>
#include <display.h>
#include <timers.h>
#include <usart.h>
#include <stdio.h>

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

float potenza_attiva(unsigned short *,unsigned short *);

void misura_a_display(float rms_V, float rms_I, float P_A, float Q, float S,float Energy,unsigned int secondi);

void invia_uart(unsigned short *tensione,unsigned short *corrente, float rms_V, float rms_I, float P_A, float Q,float S,float Energy);

#define NCampioni 400 //Campioni da acquisire ad ogni loop
#define Gain_V 0.555431 //Guadagno trasduttore di tensione (RMS)
//#define Gain_I 0.030623
#define Gain_I 0.017340//Guadagno trasduttore corrente (RMS)
#define display_time 24000 //Secondi accensione display

int main(void){
	*SCB |= CP11|CP10;
	unsigned char clear = 0; //variabile per azzerare animazione LED
	unsigned int misura[NCampioni]; //Array campioni acquisiti
	unsigned short tensione[NCampioni]; //array campioni tensione
	unsigned short corrente[NCampioni]; //array campioni corrente
	float rms_V = 0;
	float rms_I = 0;
    float P_A=0; //Potenza attiva misurata
    float Q=0; //Potenza reattiva
    float S=0; //Potenza apparente
    float Energy=0; //Energia assorbita
    unsigned int secondix10=0; //Conteggio overflow 10 secondi (superfluo?)
    unsigned int secondi = 0; // Overflow dopo 136 anni
    unsigned short stato_display=1; //Avvia display acceso
    unsigned int delay_display=0; //Variabile per contare quando è stato acceso il display

	//Abilita il clock per GPIOA e GPIOE
	RCC->GPIOAEN = 1; //EnableGPIOA
	RCC->GPIOCEN = 1; //Enable GPIOC
	RCC->GPIODEN = 1; //Enable GPIOD

	init_timers(); // Inizializza timer 2-3-4-6-7

	//Abilitazione UART USB
	RCC->USART1EN=1; //Enable USART1
	GPIOC->MODER4 = Alternate; //USART1 TX
	GPIOC->MODER5 = Alternate; //USART1 RX
	GPIOC->AFRLAFR4 = 0b0111; //Usart Alternate function FA7
	GPIOC->AFRLAFR5 = 0b0111; //Usart function FA7
	//USART1->BRR = 833;//Definisci Baudrate USART ovvero 9600 bps con fck 8MHz
	//USART1->BRR = 417; // UART A 19200 baud
	USART1->BRR = 208; // UART a 38400 baud
	USART1->BRR = 139; // UART a 57600 baud
	USART1->UE=1; //UE = 1 abilita Usart 1
	USART1->TE=1; //Abilita trasmissione USART
	USART1->RE=1; //Abilita ricezione


	//Configurazione ADC
	GPIOA->MODER1 = Analog; //Modalià analogica PA1 (ADC1 channel 2)
	GPIOA->MODER5 = Analog; //Abilita modalità analogica su pin PA5 (ADC2)
	RCC->ADC12EN = 1; //Abilita ADC12 nell'RCC
	ADC12->CKMODE = 0b01; //CKMODE 01 syncronous clock mode
	ADC12->DUAL = 0b00110; //Modalità sincrona degli ADC


	//Abilita LED per animazione
	RCC->GPIOEEN = 1; //Enable GPIOE
	GPIOE->MODER = 0x55550000; //led output da 8 a 15

	init_lcd(); //Inizializza LCD
	delay_ms(200);
	lcd_clear(); // Pulisci display
	lcd_bl_on(); //Accendi LCD
	delay_ms(500);
	lcd_hello_world(); //Schermata benvenuto
	delay_ms(2000); //Attendi 2 secondi..


	init_ADC(ADC1,2); //Inizializza e calibra ADC1 canale 2 (PA1)
	init_ADC(ADC2,2); //Inizializza e calibra ADC2 canale 2 (PA5)

	// Configurazione ARR per frequenza di campionamento ADC
	//TIM4->ARR=1125;
	//TIM4->ARR=1599; //Arr 100 campioni per periodo 5kHz (5.01 reale)
	TIM4->ARR=799; //ARR 200 campioni (10kHz)
	//TIM4->ARR=399; //ARR con 400 campioni (20kHz)
	TIM4->CEN=1;

	lcd_clear(); //Svuota display
	//Fine setup

	while(1){	//Main loop

		esegui_misura(misura,tensione,corrente, &rms_V, &rms_I, &P_A, &S, &Q); //Esegui le misure

		if(check_ten_sec()){ //Se sono passati 10 secondi
			secondix10 += 1; //Aggiungi 10 secondi (superfluo?)
			Energy += P_A*10/3600; //Accumula energia
		}

		if(USER_BTN){ //polling del tasto user per accendere LCD
			stato_display=1; //Imposta variabile stato LCD
			delay_display=secondi; //Salva il secondo in cui è stato peremuto il tasto
			lcd_bl_on(); //Accendi display
			lcd_clear(); //pulisci display
		}

		if (check_one_sec()){ //è trascorso un secondo?
			secondi += 1; //Aggiungi un secondo
			clear = animazione_led(clear); //Avanza di un led nell'animazione
			if (stato_display){ //Se il display era acceso
				misura_a_display(rms_V,rms_I,P_A,Q,S,Energy,secondi); //Invia misura al display
				if (secondi-delay_display>display_time){ // trascorsi 15 secondi disabilita e spengi display
					stato_display=0; //Imposta lo stato del display
					lcd_bl_off(); //spegni display
				}
			}
		}

		if(usart_read()){ //Polling UART RX
			invia_uart(tensione,corrente,rms_V,rms_I,P_A,Q,S,Energy); //Invia i campioni
		}

	}//end while
}//END MAIN

unsigned char animazione_led(unsigned char clear){
	LED_8 = 1; //Accendi LED 8
	if (clear){ //Verifica se devi azzerare
		GPIOE->ODR|=0x0080; //Riparti dal led 7 (Solo animazione orologio
		GPIOE->ODR=0; //Spegni tutto (Entrambe le animazioni o solo accumulo)
		clear = 0; //Resetta variabile di clear
	}
	GPIOE->ODR = ((GPIOE->ODR)<<1); //ANIMAZIONE "orologio" (shift a sinistra)
	GPIOE->ODR = (GPIOE->ODR)+(1<<8); //ANIMAZIONE "accumulo binario" (aggiungi 1)
	if (((GPIOE->ODR)==(0xff00))||((GPIOE->ODR)==(0x0000))){ //Quando termini i LED (tutti accesi o tutti spenti)
		clear = 1;
	}
	return clear;
}

void init_ADC(ADC_Type *ADC, int channel){
	ADC->ADVREGEN = 0b00;//Attiva regolatore di tensione fase intermedia
	ADC->ADVREGEN = 0b01;//Attiva regolatore di tensione accensione
	delay_us(20);

	ADC->DIFSEL=(0<<channel); //Single ended canale x

	//Calibrazione
	ADC->ADEN=0; //Spegni ADC (superfluo)
	ADC->ADCALDIF=0;//Imposta calibrazione single ended
	ADC->ADCAL=1; //Avvia Calibrazione
	while (ADC->ADCAL!=0); //Attendi termine calibrazione

	//Abilitazione ADC
	ADC->ADEN=1; //Abilita ADC
	while (ADC->ADRDY!=1); //Attendi commutazione Ready
	ADC->ADRDY=0; //Riabbassa bit ready (per eventuali acquisizioni successive)

	//Definizione sequenza di acquisizione
	ADC->L=0; //Lunghezza azquisizione = 0, un solo canale
	ADC->SQ1=channel; //Canale x nella posizione di sequenza 1

	//Impostare il tempo di sampling (sul canale x)
	//ADC2->SMPx = 7; // (0b111) 601.5 volte il clock dell'ADC
	if (channel < 10) { //Se il canale è minore di 10 sei nel primo registro
		ADC->SMPR1 = (6<<((channel)*3)); //Shifta di 3 moltiplicato il numero del canale
	}
	else { //Altrimenti nel secondo
		ADC->SMPR2 = (6<<((channel-10)*3)); //Shifta di 3 moltiplicato il numero del canale (- 10)
	}
}


void esegui_misura(unsigned int *misura, unsigned short *tensione, unsigned short *corrente, float *rms_V, float *rms_I, float *P_A, float *S, float *Q){
	for (int i=0; i<NCampioni;i++){ //Acquisisci campioni
		while(TIM4->UIF==0); //Attendi overflow timer per campionamento a frequenza costante
		ADC1->ADSTART=1; //Inizia conversione (è il master ad avviare la conversione)
		TIM4->UIF=0; //Abbassa bit overflow timer 4
		while (ADC1->EOC==0); //Attendi fine conversione (sempre del master)
		misura[i] = ADC12->CDR; //Salva i dati dal common data register (entrambi gli ADC)
	}
	for (int i=0; i<NCampioni;i++){ //Separa i dati misurati, in un altro for per non interferire con il campionamento
		tensione[i] = misura[i];  // channel on master
		corrente[i] = (misura[i]>>16); // channel on slave
	}
	*rms_V = rms(tensione)*Gain_V; //Calcola rms tensione
	*rms_I = rms(corrente)*Gain_I; //RMS corrente
	*P_A=potenza_attiva(tensione,corrente); //Potenza attiva
	*S = (*rms_V)*(*rms_I); //Potenza apparente
	*Q = (*S)-(*P_A); //Potenza reattiva
}

void invia_valore(unsigned short valore, char A){
	char a;
	char b;
	a = valore; //Primi 8 bit (meno significativi)
	b = (valore>>8); // 8 bit più significativi
	usart_send(0xFF); //Carattere di sincronizzazione (255)
	usart_send(A); //Header
	usart_send(a); //Invia primi 8 bit
	usart_send(b); //Invia successivi 8 bit
}

float mean(unsigned short *valori){ //Funzione media
	float somma = 0;
	for (int i = 0; i<NCampioni; i++){
		somma += valori[i]; //Somma dei valori
	}
	return (somma/NCampioni); //Media
}

float rms(unsigned short *valori){ //Funzione rms
	float media = mean(valori); //Ottieni media
	float quadrati=0; //Inizializza RMS
	for (int i = 0; i<NCampioni; i++){
		float diff = (valori[i]-media);
		quadrati += diff*diff; //Calcolo dei quadrati
	}
	return sqrtf(quadrati/NCampioni); //Ritorna radice quadrata
}

float potenza_attiva(unsigned short *tensione,unsigned short *corrente){ //Calcolo potenza attiva
	float media_v = mean(tensione);
	float media_i = mean(corrente);
	float v_0[NCampioni];
	float i_0[NCampioni];
	float P_ist = 0.0;
	for (int i = 0; i<NCampioni; i++){
			v_0[i] = (tensione[i]-media_v)*Gain_V; //Calcolo media
			i_0[i] = (-corrente[i]-media_i)*Gain_I;
			P_ist += v_0[i]*i_0[i];
		}
	   return (P_ist/NCampioni);
}

void misura_a_display(float rms_V, float rms_I, float P_A, float Q, float S,float Energy,unsigned int secondi){
	char buffer[32]; //Inizializza un buffer per costruire la stringa

	lcd_put_cur(0,0);
	snprintf(buffer,sizeof(buffer),"V:%3.1fV",rms_V); //costruisci potenza attiva
	lcd_send_string(buffer); //Invia
	lcd_put_cur(0,10);
	snprintf(buffer,sizeof(buffer),"I:%3.1fA",rms_I); //costruisci potenza attiva
	lcd_send_string(buffer); //Invia

	lcd_put_cur(1,0); //Cursore seconda riga prima colonna
	snprintf(buffer,sizeof(buffer),"P:%3.1fW",P_A); //costruisci potenza attiva
	lcd_send_string(buffer); //Invia
	lcd_put_cur(1,10); //Seconda riga decima colonnta
	snprintf(buffer,sizeof(buffer),"Q:%3.1fVar",Q); //Potenza reattiva
	lcd_send_string(buffer); //Invia
	lcd_put_cur(0,20); //Display 4x20, in posizione 20 si trasla di due righe, dunque terza riga, (due rispetto alla prima) prima colonna
	snprintf(buffer,sizeof(buffer),"S:%3.1fVA",S); //Potenza apparente
	lcd_send_string(buffer); //Invia
	lcd_put_cur(0,31); // terza riga undicesima colonna
	snprintf(buffer,sizeof(buffer),"E:%3.1fWh",Energy); //Enrgia
	lcd_send_string(buffer); //Invia
	lcd_put_cur(1,20); //Ultima riga prima colonna (riga 2 più 2)
	snprintf(buffer,sizeof(buffer),"Uptime: %02dG %02d:%02d:%02d",(int)(secondi/86400),(int)(secondi%86400/3600),(int)((secondi%3600)/60),(int)(secondi%60)); //Calcolo uptime
	lcd_send_string(buffer); //Invia
}

void invia_uart(unsigned short *tensione,unsigned short *corrente, float rms_V, float rms_I, float P_A, float Q,float S,float Energy){
	for (int i=0; i<NCampioni;i++){
		invia_valore(round((tensione[i])),'A'); //Invia campione tensione
		invia_valore(round((corrente[i])),'B'); //Invia campione corrente
	}
	// Invia le altre misure con i rispettivi header
	invia_valore((unsigned)rms_V,'C');
	invia_valore((unsigned)rms_I,'D');
	invia_valore((unsigned)P_A,'E');
	invia_valore((unsigned)Q,'F');
	invia_valore((unsigned)S,'G');
	invia_valore((unsigned)Energy,'H');

}


