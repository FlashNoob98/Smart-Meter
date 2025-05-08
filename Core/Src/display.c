#include <my_structures.h>

#define GPIOD ((GPIO_Type*) 0x48000C00) //Indirizzo base GPIOD (Display 0-7)

#define TIM6 ((TIMER_Type*) 0x40001000) //Indirizzo base timer 6


#define RS (GPIOD->ODR0)
#define RW (GPIOD->ODR1)
#define E (GPIOD->ODR2)
#define D4 (GPIOD->ODR3)
#define D5 (GPIOD->ODR4)
#define D6 (GPIOD->ODR5)
#define D7 (GPIOD->ODR6)

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
	RW = 0;
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
    datatosend = ((cmd)&0x0f);
    send_to_lcd(datatosend,0);  // RS must be while sending command
    /* send Lower Nibble */
    //delay_us(1);
    datatosend = ((cmd<<4)&0x0f);
    send_to_lcd(datatosend, 0);
}

void lcd_send_data (char data)
{
    char datatosend;
    /* send higher nibble */
    datatosend = ((data)&0x0f);
    send_to_lcd(datatosend, 1);  // rs =1 for sending data
    /* send Lower nibble */
    //delay_us(1);
    datatosend = ((data<<4)&0x0f);
    send_to_lcd(datatosend, 1);
    delay_us(1);
}

void init_lcd(){
	GPIOD->MODER = 0x5555; //Da PD0 a PD8 in Write mode

    // 4 bit initialisation
    delay_ms(15);  // wait for >15ms

    lcd_send_cmd(0x03); // Initialize 8bit mode
    delay_us(10);
    lcd_send_cmd(0x03); //boh
    delay_us(1000);
    lcd_send_cmd(0x03); //boh
     delay_us(1000);
    lcd_send_cmd(0x22); // 4 bit mode
    delay_us(1000);
    lcd_send_cmd(0x2C); //4 bit 2 lines
    delay_us(5000);
    lcd_send_cmd(0x0C); //Display on;
    delay_us(5000);
    lcd_send_cmd(0x01); // Clear display
    delay_us(5000);
    lcd_send_cmd(0x02); //Riporta in posizione inziale


    //lcd_send_cmd (0x2C);  // 4bit mode
    delay_us(20);
    //lcd_send_cmd(0x05);
  //  lcd_send_cmd(0x0F);
    //lcd_send_cmd(0x01); //Clear display
    delay_us(50);
  //  lcd_send_cmd (0x30);
    //delay_us(5);
 //   HAL_Delay(5);  // wait for >4.1us
    //lcd_send_cmd (0x30);
    //delay_us(1);
 //   HAL_Delay(1);  // wait for >100us
    //lcd_send_cmd (0x30);
    //delay_us(10);
  //  HAL_Delay(10);
  //  HAL_Delay(10);
    delay_us(10);
  // dislay initialisation
 //   lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)

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


