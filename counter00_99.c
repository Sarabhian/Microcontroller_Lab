#include <SST89X5XXRD2.H>
// port declaration
sbit s1= P2^0; //MSB 
sbit s2= P2^1; //LSB 

// initializing variables 
unsigned char x[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98}; // values of a,b,c,d,e,f,g of 7-seg display 
unsigned int m , msb ,lsb ; 
// function declarations 
void delay(unsigned int);
void blank(void);

// main function 
void main(void) 
{ 
		P1=0x00; P2=0x00;
		while(1)
		{
			for(m=0 ; m<=100 ;m++)
			{
				msb= m/10;
				lsb= m%10;
				
				s1=1;
				P1=x[lsb];
				delay(500);
				blank();
				
				s2=1;
				P1=x[msb];
				delay(500);
				blank();
			}
		}
}

//function definations 
 
// 1. delay function 
void delay(unsigned int ms)  // delay in micro second function 
	{
		unsigned int i,j;
		for(  i=0; i<=ms; i++)
			{
				for (j=0;j<10;j++);
			}
	  
	}
	
// 2. blank function 
 void blank(void)
 {
	 s1=0;s2=0;
 }			
		
