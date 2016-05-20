#include"PIC_setup.h"       //Setup stuff
#include <math.h>
#include"ILI9163C.h"       //LCD stuff


int main() {

    __builtin_disable_interrupts();
    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;
    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;
    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;    
    //Setup Push button 2 for user input
    //AD1PCFGbits.PCFG2 = 1;
    TRISBbits.TRISB4 = 1; //Set B4 as an input pin          
    //Setup for green test LED
    TRISAbits.TRISA4 = 0;//set A4 as output
    LATAbits.LATA4 = 0; //Set A4 as LOW to begin with    
    
    SPI1_init();
    LCD_init();
        
    __builtin_enable_interrupts();
    
    
    LCD_clearScreen(BLACK);
    
    
    char c[100];
    int number = 1337;
    sprintf(c,"Hello world %d!",number);
    
    LCD_Draw_String(28,32,&c,YELLOW,BLACK);

    
    _CP0_SET_COUNT(0);
    while(1) {
        
          
    }       
}