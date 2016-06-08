#include"init_PWM.h"


void init_PWM(void){
    //Open pins for OC1 and OC2
    RPA0Rbits.RPA0R = 0b0101; //Set A0 as OC1 (PIN 2)
    RPB8Rbits.RPB8R = 0b0101; //Set B8 as OC2 (PIN 17)
    
    //***************TIMER 2************************
    T2CONbits.TCKPS = 4; //Prescaler N=16
    // period = (PR2+1) * N * 20.8 ns
    PR2 = 2999;//With prescaler of 16 give a 1 kHz signal
    TMR2 = 0;                       //reset the timer  
    T2CONbits.ON = 1;               //Turn on the timer
    //**********************************************
    
    //*************PHASE DIRECTIONS******************
    TRISBbits.TRISB15 = 0;//set  as output
    LATBbits.LATB15 = 1; //Set  as LOW to begin with  
    TRISBbits.TRISB13 = 0;//set A4 as output
    LATBbits.LATB13 = 1; //Set A4 as LOW to begin with  
    //TRISBbits.TRISB4 = 0;//set  as output
    //LATBbits.LATB4 = 0; //Set  as LOW to begin with 
    //***********************************************
    
    
	//OC1
	OC1CONbits.OCM = 0b110;  	//PWM mode without fault pin; other OC1CON bits are defaults
	OC1RS = 0;             	//0% duty Cycle
	OC1R = 0;              	//0% duty Cycle
	OC1CONbits.OCTSEL = 0;  	//Use timer 2
	OC1CONbits.ON = 1;       	// turn on OC1
    
    //OC2
	OC2CONbits.OCM = 0b110;  	//PWM mode without fault pin; other OC2CON bits are defaults
	OC2RS = 0;             	//0% duty Cycle
	OC2R = 0;              	//0% duty Cycle
    OC2CONbits.OCTSEL = 0;  	//Use timer 2
	OC2CONbits.ON = 1;       	// turn on OC2
}