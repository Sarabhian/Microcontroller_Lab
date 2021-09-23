#include <SST89X5XXRD2.H>

// port declaration
sbit s1= P2^0;   

// function declarations 
void delay(unsigned int);

// main function 
void main(void) 
{
	while(1)
	{
		P1 =0xFE ;
		delay(10000);
		P1 =0xFF;
		delay(10000);
	}
}
//function definations 
 
// 1. delay function 
void delay(unsigned int ms)  // delay in micro second function 
	{
		unsigned int i;
		for(  i=0; i<=ms; i++);
	  
	}
