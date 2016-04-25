#ifndef SPI_setup
#define SPI_setup

#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

#define CS LATBbits.LATB7       // Chip Select (Pin-->B7)

unsigned char spi_io(unsigned char o);

void initSPI();

void setOutputVoltage(char output, unsigned char voltage);


#endif