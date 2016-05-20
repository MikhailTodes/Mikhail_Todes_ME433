#include"PIC_setup.h"       //Setup stuff
#include"i2c_setup.h"       //Setup the I2C comms
#include"init_PWM.h"        //Setup PWM stuff
#include"imu.h"             //Setup IMU stuff
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
    LATAbits.LATA4 = 0; //Set A4 as LOW to begin with    
    
        
    init_IMU();
    init_PWM();
    
    __builtin_enable_interrupts();
    
    short imu_data[7];
    
    _CP0_SET_COUNT(0);
    while(1) {
        
        read_IMU(imu_data);
         
        
        //OC1RS = (int)((((float)imu_data[4]*2 + 32767.0)/65535.0)*(3000));
        //OC2RS = (int)((((float)imu_data[5]*2 + 32767.0)/65535.0)*(3000)); 
        
    }       
}