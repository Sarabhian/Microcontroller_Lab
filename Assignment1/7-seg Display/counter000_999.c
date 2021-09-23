#include <SST89X5XXRD2.H>
// port declaration
sbit s1= P2^0;   
sbit s2= P2^1; 
sbit s3= P2^2;    
// initializing variables 
unsigned char x[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98}; // values of a,b,c,d,e,f,g of 7-seg display 
unsigned int m , d0, d1, d2 ;  // d0 = unit place , d1= tens place , d2= hundreds place 
// function declarations 
void delay(unsigned int);
void delay_ms(unsigned int);
void blank(void);

// main function 
void main(void) 
{ 
		P1=0x00; P2=0x00;
		while(1)
		{
			for(m=0 ; m<1000 ;m++)
			{ 
				d0= m%10 ;
				d1= (m%100)/10; 
				d2= (m%1000)/100 ;
				
				s1=1;
				P1=x[d0];
				delay(2000);
				blank();
				
				s2=1;
				P1=x[d1];
				delay(2000);
				blank();
			
				
				s3=1;
				P1=x[d2];
				delay(2000);
				blank();
			
				
				//delay_ms(10);
			}
		}
}

//function definations 
 
// 1. delay function 
void delay(unsigned int ms)  // delay in micro second function 
	{
		unsigned int i;
		for(  i=0; i<=ms; i++);
	  
	}
	
// 2. blank function 
 void blank(void)
 {
	 s1=0;s2=0;s3=0;
 }			
// 3. delay_ms()  
void delay_ms(unsigned int ms)  // delay in micro second function 
	{
		unsigned int i,j;
		for(  i=0; i<=ms; i++)
		{
			for( j=0 ; j< 1000; j++);
		}
	  
	} 
