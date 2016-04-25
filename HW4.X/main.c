#include"PIC_setup.h"       //Setup stuff

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
    LATAbits.LATA4 = 1; //Set A4 as high to begin with
    
    __builtin_enable_interrupts();
    
    _CP0_SET_COUNT(0);
    while(1) {
                
        while(PORTBbits.RB4 == 0) {//Chill when button is pressed
            LATAbits.LATA4 = 0;
        }
                
        if (_CP0_GET_COUNT()>24000){ //Toggle at 1000 Hz
        LATAbits.LATA4 = !LATAbits.LATA4; //toggle
            _CP0_SET_COUNT(0);
        }
	    // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
		// remember the core timer runs at half the CPU speed
    }
    
    
}