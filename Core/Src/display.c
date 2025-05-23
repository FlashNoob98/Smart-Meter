#include <my_structures.h>
#include <timers.h>

#define RS (GPIOD->ODR0)
#define E (GPIOD->ODR1)
#define D4 (GPIOD->ODR2)
#define D5 (GPIOD->ODR3)
#define D6 (GPIOD->ODR4)
#define D7 (GPIOD->ODR5)
#define BL (GPIOD->ODR6) //backlight pin

void send_to_lcd (char data, int rs)
{
	D7=0;
	D6=0;
	D5=0;
	D4=0;
	//delay_us(50);
	RS = rs;
	//delay_us(50);
	E = 1;
	//delay_us(200);
	D7 = ((data>>3)&(0x01));
	D6 = ((data>>2)&(0x01));
	D5 = ((data>>1)&(0x01));
	D4 = ((data>>0)&(0x01));
	delay_us(2);
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
   // delay_ms(20);
    /* send Lower Nibble */
   // delay_us(10);
    datatosend = ((cmd)&0x0f);
    send_to_lcd(datatosend, 0);
    delay_ms(1);

}

void lcd_send_data (char data)
{
    char datatosend;
    /* send higher nibble */
    datatosend = ((data>>4)&0x0f);
    send_to_lcd(datatosend, 1);  // rs =1 for sending data
    /* send Lower nibble */
    //delay_us(10);
    datatosend = ((data)&0x0f);
    send_to_lcd(datatosend, 1);
    delay_us(50);
}

void init_lcd(){
	GPIOD->MODER |= 0x555; //Da PD0 a PD5 in Write mode
	GPIOD->MODER6 = 1; //Backlight pin output mode

    // 4 bit initialisation
    delay_ms(40);  // wait for >20ms attendi avvio del display
    send_to_lcd(0x2,0); // Inizializza display modalità 4 bit
    //delay_ms(50);

   // delay_ms(20);
    //lcd_send_cmd(0x01); // Clear display
    lcd_send_cmd(0x28); // Function set Display 2 linee
   // delay_ms(20);
    lcd_send_cmd(0x0C); //Display on- cursor off - blink OFF;
  //  delay_ms(20);
    lcd_send_cmd(0x6); //Entry mode set - shift and increment
  //  delay_ms(20);
    lcd_send_cmd(0x01); // Clear display
   // lcd_clear();
  //  delay_ms(20);

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
    delay_ms(20);
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	delay_ms(1);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_bl_on(void){
	BL = 1;
}

void lcd_bl_off(void){
	BL = 0;
}

void lcd_hello_world(void){

	lcd_put_cur(0, 0);
	lcd_send_string("Hello world");
	lcd_put_cur(1, 0);
	lcd_send_string("Ciao a tutti");
	lcd_put_cur(0,20);
	lcd_send_string("Ciao 2");
	lcd_put_cur(1,20);
	lcd_send_string("Ciao 3");

}

