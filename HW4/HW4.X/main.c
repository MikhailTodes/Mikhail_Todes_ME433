#include"PIC_setup.h"       //Setup stuff
#include"SPI_setup.h"         //Setup the SPI comms
#include <math.h>

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
    
    
    initSPI();
    unsigned char volts = 0;
    char output = 0;    
    // set the voltage low
    setOutputVoltage(output, volts);
    
    //Create a sin wave
    unsigned char sinwave[1000];
    int i = 0, center = 255/2, A = 255/2;
    for (i = 0; i < 1000; i++){
        sinwave[i] = (unsigned char)center + A * sin( 2 * 3.14 * i / (1000));
    }
    
    // create a triangle wave
    unsigned char triWave[1000];
    i = 0;
    for (i = 0; i < 1000; i++){
        triWave[i] = (unsigned char) 255 * i /1000;
    }
    
    
    _CP0_SET_COUNT(0);
    while(1) {
        
         if(_CP0_GET_COUNT()>24000){ 
            i++;
            setOutputVoltage(0, sinwave[i]);
            setOutputVoltage(1, triWave[i]);
            _CP0_SET_COUNT(0);
         }
        if (i > 1000){i = 0;}

        
    }
    
    
}