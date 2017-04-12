/*  Name     : main.c
 *  Purpose  : Main file for  a demo project for the implentation of uart communication in AT89S8253 controllers.
               the project  file contains the functions to transmit and receive character and to transmit a string.
							 
 *  Author   : Etiq Technologies
 *  Date     : 03/05/2016 
 *  Revision : None
 */

#include <REG8253.H>

/* uart initialisation function */
void UART_init()
{
	SCON=0x50;            //configure serial control register
	PCON=0x80;            //SMOD bit set
  TMOD=0x20;           //using timer1,8-bit reload mode for baudrate generation
	TH1=0xEF;            //4800 baudrate(16 mhz clock)
	TR1=1;               //start timer

	
	
}

/* function to transmit  a string in uart */

void Uart_write_txt(unsigned char *ptr)
{
	/*Each character in the string is transmitted 
	in aloop until the final character '\0' */
	
	while(*ptr)
	{
		SBUF=*ptr;             // character in transmit buffer
		while(!TI);            //wait until transmission complete
		TI=0;                  //clear the flag
		ptr++;
}
	}

/* function to receive a character in uart */	
unsigned char Uart_read_char()
{
unsigned char character;
while(!RI);               //wait until character received completely
character=SBUF;           //read the character from buffer reg
RI=0;                     //clear the flag
return character;	        //return the received character
}

/* function to transmit a character in uart */
void Uart_write_char(unsigned char character)
{
	SBUF=character;          //load the character to be transmitted in to the buffer reg
	while(!TI);              //wait until transmission complete
	TI=0;                    //clear flag
}

 /* Main function demonstrate each operation in uart
    a charcter is received and transmitted        */
 
void main()
{
	unsigned char received; 	
	UART_init();
	while(1)
	{
		Uart_write_txt("\r\nEnter the character from Keyboard\r\n");  //transmit the string
		received=Uart_read_char();                                    //receive character
		Uart_write_txt("You have entered ");                          //transmit string
		Uart_write_char(received);                                    //transmit the received character.
}

}
