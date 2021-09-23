#include <SST89X5XXRD2.H>

// port declaration
sbit s1= P3^0;  

// initializing variables 
unsigned char x ;
unsigned int k,m;

// function declarations 
void delay_ms(unsigned int);

// main function 
void main(void) 
{
	while(1)
	{
		if( s1==1)
		{  
			
			x = 0x01; // 00000001
		for(k =0; k<8; k++)
		{
			P1 = x;
			delay_ms(100);
			x = x<<1; // left shift
		}
		
		x = 0x80; 
		for(k =0; k<8; k++)
		{
			P1 = x;
			delay_ms(100);
			x = x>>1; // right shift
		}
		
		}
		else
		{
			P1=0x55;   // alternate LEDswill blink 	
			delay_ms(100);
			P1=0xAA;  // alternate LEDswill blink
			delay_ms(100);
		}
		
		
	}
}
//function definations 
 
// 1. delay function 
void delay_ms(unsigned int ms)  // delay in micro second function 
	{
		unsigned int j,i;
		for(  i=0; i<=ms; i++)
		{
			for(  j=0; j<=1000; j++);
		}
	  
	}