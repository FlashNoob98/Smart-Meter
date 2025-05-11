#include <my_structures.h>

#define GPIOD ((GPIO_Type*) 0x48000C00) //Indirizzo base GPIOD (Display 0-7)

#define TIM6 ((TIMER_Type*) 0x40001000) //Indirizzo base timer 6


#define RS (GPIOD->ODR0)
#define E (GPIOD->ODR1)
#define D4 (GPIOD->ODR2)
#define D5 (GPIOD->ODR3)
#define D6 (GPIOD->ODR4)
#define D7 (GPIOD->ODR5)

void delay_us(int us){

	TIM6->PSC=7; // 8 MHz to 1Mhz
	TIM6->ARR = us;
	TIM6->CNT = 0;//resetta timer 6
	TIM6->UIF = 0;
	while((TIM6->UIF)==0);//Verifica quando avviene l'overflow (500us)
	TIM6->UIF=0;
}

void delay_ms(int ms){
	TIM6->PSC=69; // 8 MHz to 1Khz
	TIM6->ARR = ms;
	TIM6->CNT = 0;//resetta timer 6
	TIM6->UIF = 0;
	while(TIM6->UIF==0);//Verifica quando avviene l'overflow (500us)
	TIM6->UIF=0;
}



void send_to_lcd (char data, int rs)
{
	D7=0;
	D6=0;
	D5=0;
	D4=0;
	delay_us(20);
	RS = rs;
	delay_us(20);
	E = 1;
	delay_us(10);
	D7 = ((data>>3)&(0x01));
	D6 = ((data>>2)&(0x01));
	D5 = ((data>>1)&(0x01));
	D4 = ((data>>0)&(0x01));
	delay_us(10);
	E = 0;
	//delay_us(20);
	//Delay 20 us
};

void lcd_send_cmd (char cmd)
{
    char datatosend;
    /* send upper nibble first */
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);  // RS must be while sending command
    /* send Lower Nibble */
    //delay_us(1);
    datatosend = ((cmd)&0x0f);
    send_to_lcd(datatosend, 0);
}

void lcd_send_data (char data)
{
    char datatosend;
    /* send higher nibble */
    datatosend = ((data>>4)&0x0f);
    send_to_lcd(datatosend, 1);  // rs =1 for sending data
    /* send Lower nibble */
    //delay_us(1);
    datatosend = ((data)&0x0f);
    send_to_lcd(datatosend, 1);
    delay_us(1);
}

void init_lcd(){
	GPIOD->MODER |= 0x555; //Da PD0 a PD5 in Write mode

    // 4 bit initialisation
    delay_ms(20);  // wait for >20ms attendi avvio del display

    send_to_lcd(0x2,0); // Inizializza display modalità 4 bit

    lcd_send_cmd(0x28); // Function set Display 2 linee
    delay_us(1000);
    lcd_send_cmd(0x0C); //Display on- cursor off - blink OFF;
    delay_us(1000);
    lcd_send_cmd(0x6); //Entry mode set - shift and increment
    //lcd_send_cmd(0x01); // Clear display

    delay_us(20);
    //lcd_send_cmd(0x05);

}


void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd (col);
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	delay_us(2);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}


