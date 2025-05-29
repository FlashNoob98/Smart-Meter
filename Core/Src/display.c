#include <my_structures.h>
#include <timers.h>
#include <display.h>

//Definizione collegamenti PIN display
#define RS (GPIOD->ODR0) //RS specifica comando o carattere
#define E (GPIOD->ODR1) //pulse per leggere il bus dati
#define D4 (GPIOD->ODR2)
#define D5 (GPIOD->ODR3)
#define D6 (GPIOD->ODR4)
#define D7 (GPIOD->ODR5)
#define BL (GPIOD->ODR6) //backlight pin

void send_to_lcd (char data, int rs){
	//Dati sul bus
	//D7 = ((data>>3)&(0x01));
	//D6 = ((data>>2)&(0x01));
	//D5 = ((data>>1)&(0x01));
	//D4 = ((data>>0)&(0x01));
	GPIOD->ODR &= (0x40); // Azzera bit dati, maschera 1000000 (mantiene stato BL)
	GPIOD->ODR |= ((data&(0xF))<<2); //Scrivi dato nell'ODR

	RS = rs; //Comando o carattere?
	//Impulsa E
	//E = 0;
	delay_us(1);
	E = 1;
	delay_us(1);
	E = 0;
	delay_us(20); //Attendi per il prossimo carattere/comando
};

void lcd_send_cmd (char cmd){
    char datatosend;
    //Invia bit più significativi
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);  // RS=0 per inviare comandi
    //delay_us(5);

    // Invia bit meno significativi
    datatosend = ((cmd)&0x0f);
    send_to_lcd(datatosend, 0);
   // delay_us(200); //Attendi 4.1ms tra un comando e l'altro
}

void lcd_send_data (char data){
    char datatosend;
    //Invia bit più significativi
    datatosend = ((data>>4)&0x0f);
    send_to_lcd(datatosend, 1);  // rs =1 per inviare dati e non comandi
    //delay_us(5);
    // Invia bit meno significativi
    datatosend = ((data)&0x0f);
    send_to_lcd(datatosend, 1);
}

void init_lcd(){
	GPIOD->MODER |= 0x555; //Da PD0 a PD5 in Write mode
	GPIOD->MODER6 = 1; //Backlight pin output mode

    // 4 bit initialisation
    delay_ms(200);  // wait for >20ms attendi avvio del display
    //this is according to the Hitachi HD44780 datasheet
    // figure 24, pg 46

    //comando da inviare tre volte per inizializzazione (vedi datasheet hitachi)
    send_to_lcd(0x03,0);
    delay_us(4500);
    send_to_lcd(0x03,0);
    delay_us(4500);
    send_to_lcd(0x03,0);
    delay_us(4500);

    send_to_lcd(0x2,0); // Inizializza display modalità 4 bit
    delay_ms(500);

    //Configurazione display
    lcd_send_cmd(0x28); // Function set Display 2 linee
    lcd_send_cmd(0x0C); //Display on- cursor off - blink OFF;
    lcd_send_cmd(0x6); //Entry mode set - shift and increment
    lcd_send_cmd(0x01); // Clear display
    lcd_clear(); // Clear display
}


void lcd_put_cur(int row, int col){ //Sposta cursore sul display
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

void lcd_clear (void){
	lcd_send_cmd(0x01); //Svuota display
}

void lcd_send_string (char *str){
	while (*str) lcd_send_data(*str++); //Scorri tutta la stringa e passa un carattere alla volta
}

void lcd_bl_on(void){
	lcd_send_cmd(0x0C); //Attiva LCD
	BL = 1; //Attiva retroilluminazione
}

void lcd_bl_off(void){
	lcd_send_cmd(0x08); //Disattiva LCD
	BL = 0; //Disattiva retroilluminazione
}

void lcd_hello_world(void){
	lcd_put_cur(0, 0);
	lcd_send_string("Ing. Elettrica UniNa");
	lcd_put_cur(1, 0);
	lcd_send_string("Corso Smart Metering");
}

