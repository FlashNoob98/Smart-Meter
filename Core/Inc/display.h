#include <my_structures.h>

#ifndef INC_display_H_
#define INC_fisplay_H_

void lcd_clear (void);

void init_lcd (void);   // initialize lcd

void lcd_send_cmd (char);  // send command to the lcd

void lcd_send_data (char);  // send data to the lcd

void lcd_send_string (char *);  // send string to the lcd

void lcd_put_cur(int, int);  // put cursor at the entered position row (0 or 1), col (0-15);

void lcd_hello_world(void);

void lcd_bl_on(void);

void lcd_bl_off(void);

#endif /* INC_display_H_ */
