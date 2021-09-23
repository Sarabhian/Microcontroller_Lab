#include <SST89X5XXRD2.H>

/* this code prints DIGITAL CLOCK in (HRs:MM:SS), and different character strings using different key inputs from user */

// pin configurations 
 #define LCDPORT P1 // declaring p1 as LCDPORT ( assigning newe variable )
 sbit RS = P2^0;
 sbit RW= P2^1;
 sbit E= P2^2;
 
 // initializing variables 
unsigned char d[]={"Embedded Lab"};
unsigned char k,l ,m , lsb,msb;

// function declarations 
 void LCD_data( unsigned char ); 
 void LCD_cmd(unsigned char);
 void enable(void);
 void LCD_init(void);
 void delay(unsigned int );

// main funcction  
 void main(void)
 {
	 LCD_init();
	 while(1)
	 { LCD_cmd(0x82);
		 for(k=0;k<=12;k++)
				{
					LCD_data(d[k]);
				}
	 }
 }
 
 //function definations 
 
 // 1. delay function 
  void delay(unsigned int ms)
  {
		unsigned int i,j;
		for(j=0;j<ms;j++)
		  for(i=0;i<10000;i++);
	}
 // 2. LCD_init functon ... used for initializing LCD commands 
	void LCD_init(void)
	{
		LCD_cmd(0x38);  //5x7 matrix of cursor
		LCD_cmd(0x0E);  // cursor blinking ON
		LCD_cmd(0x06); // cursor Auto increament to right
		LCD_cmd(0x01); // clrear screen 
	}
	// 3. LCD_data  ... data mode --> RS=1 , LCD is currently output device so R/W= 0 (i.e. here  RW=0)
	void LCD_data(unsigned char value)
	{
		RS=1; RW=0;
		LCDPORT= value;
		enable();
		delay(5);
	}
	// 4. LCD_cmd  ... command mode --> RS=0 , RW=0
	void LCD_cmd(unsigned char command  )
	{
	  RS=0;RW=0;
		LCDPORT=command;
		enable();
		delay(5);
	}
	//5. enable ... used to generste pulse 
	void enable(void)
	{
		E=0;E=1;E=0;
	}
 
