#include <SST89X5XXRD2.H>

#define LCDPORT P1
sbit RS = P2^0;
sbit RW = P2^1;
sbit E = P2^2;
unsigned char A;
unsigned char d,k;
void LCD_data (unsigned char);
void LCD_cmd (unsigned char);
void enable (void);
void LCD_init (void); 

void delay (unsigned int);
void main (void)

{
 LCD_init(); //INITIALIZATION OF LCD
	 LCD_cmd(0x80);
while(1)
{

	TMOD=0x20;
   TH1=0xFD; 
   SCON=0x50; 
   TR1=1;
		while(RI==0);
	 d++;
		A=SBUF;
		RI=0;
	LCD_data(A); 
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
void LCD_init (void)
{
 LCD_cmd(0x38); //5x7 matrix of cursor
 LCD_cmd(0x0E); //cursor blinking commnad curson ON
 LCD_cmd(0x06); //Auto increment right 
 LCD_cmd(0x01); //clear screen command 
 }
void LCD_data (unsigned char value)
{
RS=1;
RW=0;
LCDPORT=value;
enable();
delay(5);
}
void LCD_cmd (unsigned char command)
{
RS=0;
RW=0;
LCDPORT=command;
enable();
delay(5);
}
void enable (void)
{
E=0;
E=1;
E=0;
}