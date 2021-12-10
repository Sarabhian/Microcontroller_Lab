#include <SST89X5XXRD2.H>
unsigned char B;
void main (void)
{
	TMOD=0x20 ; // Timer 1 Mode 2  0010 0000
	SCON=0x50;  // REN enable ,mode 1  
	
	TH1= -3; //baud rate= 9600
	TR1=1; //start timer 
	
	
}
void sendSerially(unsigned char B)
{
	while(1)
	{
		SBUF=B; //placing the input value 
		while(TI==0); // waiting till stop bit it 1 
		TI=0;
		 
	}
}