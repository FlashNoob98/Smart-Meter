#include <my_structures.h>

void usart_send(unsigned int data){
				while((USART1->TXE)==0); //Attendi  BIT TXE
				USART1->TDR = data;
}

char usart_read(){
	while((USART1->RXNE==0));
	return USART1->RDR;
}
