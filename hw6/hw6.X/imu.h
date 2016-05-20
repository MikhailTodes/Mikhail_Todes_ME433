#ifndef _IMU
#define _IMU

#define IMU_ADD 0x6A //Address of the IMU (LSB tied low)

//Registers
#define WHO_AM_I 0x0F
#define CTRL1_XL 0x10 //Linear acceleration sensor control register 1
#define CTRL2_G 0x11 //Angular rate sensor control register 2


#define OUT_TEMP_L 0x20 
#define OUT_TEMP_H 0x21 

#define OUTX_L_G 0x22 
#define OUTX_H_G 0x23 
#define OUTY_L_G 0x24 
#define OUTY_H_G 0x25 
#define OUTZ_L_G 0x26 
#define OUTZ_H_G 0x27 

#define OUTX_L_XL 0x28 
#define OUTX_H_XL 0x29 
#define OUTY_L_XL 0x2A 
#define OUTY_H_XL 0x2B 
#define OUTZ_L_XL 0x2C 
#define OUTZ_H_XL 0x2D

void init_IMU();
void read_IMU(short * data);

#endif