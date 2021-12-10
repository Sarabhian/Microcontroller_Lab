// this code prints DIGITAL CLOCK in (HRs:MM:SS), 
#include <SST89X5XXRD2.H>
// pin configurations 
 #define LCDPORT P1 // declaring p1 as LCDPORT ( assigning newe variable )
 sbit RS = P2^0;
 sbit RW= P2^1;
 sbit E= P2^2;

 
 // initializing variables 
unsigned char e[]={"DIGITAL CLOCK"};
unsigned char coln[] = {":"};
unsigned char serialdata, A,k,l ,m , lsb,msb;

// function declarations 
 void LCD_data( unsigned char ); 
 void LCD_cmd(unsigned char);
 void enable(void);
 void LCD_init(void);
 void delay(unsigned int );
 int msb_lsb(int k);
char recieveByteSerially();

// main funcction  
 void main(void)
 { 
	
   while(1){
		B=recieveByteSerially();
		start : //start the code 
		 LCD_init();
			if(B=='s' || B=='S')
			{ 
				B=='b' ;
				goto start ;
			
			}
			LCD_cmd(0x82);           //displays digital clock TITLE
			for(k=0;k<=13;k++)
	   { 
			 
		   LCD_data(e[k]);
		
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
				 
					for( m=0 ; m<60 ; )
					{ 
							
							continues :	
							
							m++;
						  pause :
							if( B=='b')
								 B=recieveByteSerially();
						  LCD_cmd(0xc9);
							msb , lsb =msb_lsb(m);
							LCD_data(msb+ 0x30);
							LCD_data(lsb +0x30);
							if(B=='s' || B=='S')
								goto start ;
							if(B=='p' || B=='P'){
								B='b';
								goto pause ;}
							if(B=='C' || B=='c' && m<60 )
								goto continues ;
							if(B=='e' || B=='E')
								goto stop ; 
							
					}
				}
		  }	
		}
	
	stop : 
	;
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
	// 7. serial transmit 
	void SendByteSerially(unsigned char serialdata)
{
    SBUF = serialdata;                        // LOAD DATA TO SERIAL BUFFER REGISTER
    while(TI == 0);                            // WAIT UNTIL TRANSMISSION TO COMPLETE
    TI = 0;                                    // CLEAR TRANSMISSION INTERRUPT FLAG
}
// 8. receive by serially
char recieveByteSerially() 
	{ 
		TMOD=0x20 ; // Timer 1 Mode 2 
		SCON=0x50;  // REN enable ,mode 1
		TH1= -3; //baud rate= 9600
		TR1=1; //start timer 
		while(RI==0);
		A=SBUF;
		RI=0; 
		while(TF==0);
		TL=0;
    return A ;
		
}
	

	
