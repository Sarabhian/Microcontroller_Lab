#include <SST89X5XXRD2.H>
                  
#define LCDPORT P1

sbit RS = P2^0;
sbit RW = P2^1;
sbit E = P2^2;

// 
 // initialisation of variables
unsigned char d[] = {"DIGITAL CLOCK"};
unsigned char c[] = {":"};
unsigned char msb, lsb;
unsigned int i, j, k, l;

//declaring functions
void LCD_data (unsigned char);  // // loading data in LCD
void LCD_cmd (unsigned char);  		// for LCD to go in command mode
void enable (void);			// enable pin
void LCD_init (void);   // initialising LCD
void delay (unsigned int);  // adds delay
int msb_lsb(unsigned int ); // finds msb and lsb of number

void SerialInitialize(void);
void SendByteSerially(unsigned char);    
void port_init(void);


sbit start = P2^3;
sbit ending = P2^4;

void main()
{
	
	  port_init();
    SerialInitialize();    

    EA = 1;
    ES = 1;

		if( start == 1 )
		{
		LCD_init(); //INITIALIZATION OF LCD
	
		while(1)
		{	
		LCD_cmd(0x82); // coursor line 1 position 2
		
		for(l=0; l<13; l++) // print "DIGITAL CLOCK" on display
			{
				LCD_data(d[l]);
			}
		
		for(i=0; i<60; i++)
		{
			if(ending == 1) break;
			// printing for hour
			LCD_cmd(0xC3); // Jump cursor to second line position 3
			msb, lsb = msb_lsb(i);
			LCD_data(msb + 0x30);
			LCD_data(lsb + 0x30);
			LCD_data(c[0]);
			
			for(j=0; j<60; j++)
			{
				if(ending == 1) break;
				// printing for minutes
				LCD_cmd(0xC6); // Jump cursor to second line position 6
				msb, lsb = msb_lsb(j);
				LCD_data(msb + 0x30);
				LCD_data(lsb + 0x30);
				LCD_data(c[0]);
				
				for(k=0; k<60; k++)
				{
					if(ending == 1) break;
					// printing for seconds
					LCD_cmd(0xC9); // Jump cursor to second line position 9
					msb, lsb = msb_lsb(k);
					LCD_data(msb + 0x30);
					LCD_data(lsb + 0x30);
				}
			}
		}
	}
}
    
}


void delay (unsigned int ms)
{
unsigned int i,j;
for(j=0;j<ms;j++)
   {
   for(i=0;i<=1275;i++);
   }
}	
	
void LCD_init (void)
	{
 LCD_cmd(0x38);  //5x7 matrix of cursor
 LCD_cmd(0x0E);  //cursor blinking commnad curson ON
 LCD_cmd(0x06);  //Auto increment right 
 LCD_cmd(0x01);  //clear screen command 
}

void LCD_data (unsigned char value)
{
 RS=1;   // Register select in data mode
 RW=0;     // Writing mode
 LCDPORT=value;       // writing value to port P1
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
 E=0;       // we are creating a pulse here // helping to onn off display
 E=1;
 E=0;
}

int msb_lsb(unsigned int val) 
{
	lsb = val % 10;
	msb = val / 10;
	return msb, lsb;
}

void port_init(void)   //initialize cct
{
    P0 = 0x00; //not used
    P1 = 0x00; //Used for Appliances
    P2 = 0x00; //not used
    P3 = 0x03; //used for serial  P3.0 and P3.1 = 1

}

void SerialInitialize(void)                   // INITIALIZE SERIAL PORT
{
    TMOD = 0x20;                           // Timer 1 IN MODE 2 -AUTO RELOAD TO GENERATE BAUD RATE
    SCON = 0x50;                           // SERIAL MODE 1, 8-DATA BIT 1-START BIT, 1-STOP BIT, REN ENABLED
    TH1 = 0xFD;                       // LOAD BAUDRATE TO TIMER REGISTER
    TR1 = 1;                               // START TIMER
}

void SendByteSerially(unsigned char serialdata)
{
    SBUF = serialdata;                        // LOAD DATA TO SERIAL BUFFER REGISTER
    while(TI == 0);                            // WAIT UNTIL TRANSMISSION TO COMPLETE
    TI = 0;                                    // CLEAR TRANSMISSION INTERRUPT FLAG
}

void serial_ISR (void) interrupt 4     // Timer Interrupt 1  TF1
{
    //receive character
    char chr;
    if(RI == 1)
    {
        chr = SBUF;
        RI = 0;
    }

    P0 = ~P0;    //Show the data has been updated

    switch(chr)
    {
     case 'S':  start = 1; ending = 0; SendByteSerially('S');  break;
     case 'E':  ending = 1; start = 0; SendByteSerially('E');  break;
     //case 'P':  pause = 1; SendByteSerially('P');  break;
     //case 'C':  cont = 1; SendByteSerially('C');  break;

     default: ;    break;     //do nothing
    }

    RI = 0;
}