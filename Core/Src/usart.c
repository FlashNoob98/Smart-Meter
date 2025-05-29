#include <my_structures.h>

void usart_send(unsigned int data){
		while((USART1->TXE)==0); //Attendi  BIT TXE
		USART1->TDR = data;
}

char usart_read(){
	if((USART1->RXNE==1)){
		return USART1->RDR;
	} else return 0;
}
