#include "Timer1_Driver.h"

unsigned short score  = 0 ;
void Timer1A_Handler(){
      TIMER1_ICR_R|=(1<<0);       //clear the flag
			score++;
}

void Timer1_Init(){
	SYSCTL_RCGCTIMER_R = (1<<1);       // Enable and provide a clock to 16/32-bit timer1 in Run mode.
  TIMER1_CTL_R &=~(1<<0);            //Timer1 A is disabled.
	TIMER1_CFG_R = 0x0;                //this value selects the 32-bit timer configuration.
  TIMER1_TAMR_R &= ~(3<<0);	         //to clear bit 0 and bit 1
  TIMER1_TAMR_R |= (2<<0);           //Periodic Timer mode
	TIMER1_TAMR_R &= ~(1<<4);          //Timer1 counts down
	TIMER1_TAILR_R = 80000000;          //"the start value" 1sec/0.0125 usec = 80000000
	
	TIMER1_IMR_R	|= (1<<0);	         //Timer1 A interrupt is Enabled.
	NVIC_EN0_R |=(1<<21);              //Enable timer1 A from its vector table number 
	 NVIC_PRI5_R &= ~(7<<13);          //clear bits 13 14 15 in PRI5 reg.
  NVIC_PRI5_R |= (1<<13);	           //set the priority to 1
	
	TIMER1_CTL_R |=(1<<0);             //Timer1 A is Enabled.
} 