#include "imu.h"
#include "i2c_setup.h"

void init_IMU()
{
    
    //**********I2C COMMS SETUP**********************
    i2c_master_setup();     
    //unsigned char I2C_setup; 
        
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
      
    //***********ACCEL SETUP*************************
    unsigned char setup = 0x80;
    i2c_write(IMU_ADD, CTRL1_XL, setup);   
    //***********************************************
    
    //***********GYRO SETUP*************************
    setup = 0b10000000;
    i2c_write(IMU_ADD, CTRL2_G, setup);   
    //***********************************************       
}


void read_IMU(short * data)
{
    unsigned char imu_raw_data[14], i;
    i2c_read(IMU_ADD, OUT_TEMP_L, imu_raw_data, 14);//Read first from temp and store all data    
    
    for(i=0; i<14; i+=2)
        {
           data[i/2] = ((imu_raw_data[i+1] << 8) | imu_raw_data[i]);
        }
}