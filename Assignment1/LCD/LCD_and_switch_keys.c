#include <SST89X5XXRD2.H>

/* this code prints DIGITAL CLOCK in (HRs:MM:SS), and different character strings using different key inputs from user */

// pin configurations 
 #define LCDPORT P1 // declaring p1 as LCDPORT ( assigning newe variable )
 sbit RS = P2^0;
 sbit RW= P2^1;
 sbit E= P2^2;
 sbit key1=P3^0;
 sbit  key2 =P3^1;
 sbit key3 = P3^2;
 
// initializing variables 
unsigned char d[]={"Embedded Lab"};
unsigned char c[]={"hello world"};
unsigned char e[]={"DIGITAL CLOCK"};
unsigned char coln[] = {":"};
unsigned char k,l ,m , lsb,msb;
unsigned int x,y ;

// function declarations 
 void LCD_data( unsigned char ); 
 void LCD_cmd(unsigned char);
 void enable(void);
 void LCD_init(void);
 void delay(unsigned int );
 int msb_lsb(int k);
// main funcction  
 void main(void)
 {
	label :
   LCD_init();
	 while(1)
	 { 
		 if (key3==0)
				goto label ;
		 else {}
															// Q6.  display  "Embedded Lab" 
		 if( key1 ==1 && key2==1)
			{
				LCD_cmd(0x82);
				for(k=0;k<=12;k++)
				{
					LCD_data(d[k]);
					if (key3==0)
								goto label ;
				}
			}
															// Q8. Display interfacing using switch keys 
		 else if (key1==0 && key2==1)
			{ 
				LCD_init();
				LCD_cmd(0x82);
				for(k=0;k<=4;k++)
				{
							LCD_data(c[k]);
							if (key3==0)
								goto label ;
				}
			}
		 else if( key2==0 && key1==1) 
			{	
				LCD_init();
				LCD_cmd(0x82);
				for(k=5;k<=10;k++)
				{
							LCD_data(c[k]);
							if (key3==0)
								goto label ;
				}
			}
															// Q7. DIGITAL CLOCK
		 else
			{ 
				LCD_cmd(0x82);
				for(k=0;k<=13;k++)
				{
					LCD_data(e[k]);
					if (key3==0)
								goto label ;
				}
				for( k=0 ; k<60 ;k++)
				{ 
					LCD_cmd(0xc3); 
					msb , lsb =msb_lsb(k);
					LCD_data(msb+ 0x30);
					LCD_data(lsb +0x30);
					LCD_data(coln[0]);
			 
					for( l=0; l<60 ;l++)
					{ 
						LCD_cmd(0xc6);
						msb , lsb =msb_lsb(l);
						LCD_data(msb+ 0x30);
						LCD_data(lsb +0x30);
						LCD_data(coln[0]);
				 
						for( m=0 ; m<60 ; m++)
						{
							LCD_cmd(0xc9);
							msb , lsb =msb_lsb(m);
							LCD_data(msb+ 0x30);
							LCD_data(lsb +0x30);
							if (key3==0)
								goto label ;
						}
					}
				}
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
	// 6. msb_lsb()
	int msb_lsb(int a)
	{
		msb = a/10;
		lsb = a%10;
		return msb ,lsb ;
	}
/* user guide for using keys 
	as it is cathode driven switch module , port value for on state =0 , off state =1
	
	key3= on (port value =0)  ... used for clear LCD screen and to break the loop 
	key3= off (port value =1) ... LCD is enabled to write ,
	
	key3 = key2 = key1 = off (port value =1) ... displays "EMBEDDED LAB" 
	key3=key2= off , key1= on ... displays "HELLO"
	key3=key1= off , key2= on  ... displays "world"
	key3=off , key1=key2=on  ....  displays "DIGITAL CLOCK" 
	key1=key2=key3= on state = all 3 ports grounded  ... nothing will be shown 
       	
	*/
 
