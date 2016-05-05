#include"PIC_setup.h"       //Setup stuff
#include"i2c_setup.h"       //Setup the I2C comms
#include"init_PWM.h"        //Setup PWM stuff
#include <math.h>

#define IMU_ADD 0b1101010 //Address of the IMU (LSB tied low)

//Registers
#define WHO_AM_I 0x0F
#define CTRL1_XL 0x10 //Acceleromter activation
#define CTRL2_G 0x11 //Gryoscope activation

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
    __builtin_enable_interrupts();
    
    init_PWM();
    
    //**********I2C COMMS SETUP**********************
    i2c_master_setup();     
    unsigned char I2C_setup; 
    
    unsigned char who_am_i[1];
    i2c_read(IMU_ADD, WHO_AM_I, who_am_i, 1);
    if(who_am_i[0] == 0b01101001) //WHO_AM_I is what it should be
    {
        //Turn On LED
        LATAbits.LATA4 = 1;
    }
    else
    {   
        //Turn Off LED
        LATAbits.LATA4 = 0;
    }
    //***********************************************
        
    
    _CP0_SET_COUNT(0);
    while(1) {
              
        

        
    }
    
    
}