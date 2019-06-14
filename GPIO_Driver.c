#include "GPIO_Driver.h"
long start = 0 ;

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}

void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x0000002;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
//  GPIO_PORTB_CR_R = 0x1F;           
  GPIO_PORTB_AMSEL_R = 0x00;        
  GPIO_PORTB_PCTL_R = 0x00000000;   
  GPIO_PORTB_DIR_R = 0x01;          
  GPIO_PORTB_AFSEL_R = 0x00;        
  GPIO_PORTB_PUR_R = 0x02;          
  GPIO_PORTB_DEN_R = 0x1F;

  GPIO_PORTB_IM_R |=(1<<1);//to choose pin B1
  GPIO_PORTB_IS_R &=~(1<<1); //to select as edge
	GPIO_PORTB_IEV_R&=~(1<<1);//select falling edge
  GPIO_PORTB_IBE_R&=~(1<<1);//work in one edge only
  NVIC_EN0_R |=(1<<1);
  NVIC_PRI0_R &=~(7<<13);
  NVIC_PRI0_R |=(1<<13);		
	
}

void GPIOPortB_Handler (){
	  GPIO_PORTB_ICR_R |= (1 << 1 );
		start = 1 ;			
}	