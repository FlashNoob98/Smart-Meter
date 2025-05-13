#include <my_structures.h>

void usart_send(unsigned int data){
				while((USART1->TXE)==0); //Attendi  BIT TXE
				USART1->TDR = data;
}
