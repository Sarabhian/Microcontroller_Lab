//for Microcontroller1
#include <SST89X5XXRD2.H>
unsigned char i;
void delay (unsigned int ms);
void main(void)
{
TMOD=0x20;
TH1=0xFD; 
SCON=0x50; 
TR1=1;
while(1)
{
SBUF='A'; 
while(TI==0);
delay(10);
TI=0;
}
}
void delay (unsigned int ms)
{
unsigned int i,j;
for(j=0;j<ms;j++)
{
for(i=0;i<=1000;i++);
}
}