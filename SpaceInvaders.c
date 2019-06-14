
// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

// Joystick
// -----------------------------------
// VRx connected to PE1
// SW connected to PB1

// Buzzer
// -----------------------------------
// Buzzer pin connected to PB0
#include "Game_Driver.h"
#include "delay_lib.h"
#include "ADC_Driver.h"
#include "Timer1_Driver.h"
#include "Random.h"
#include "TExaS.h"
#include <time.h>
#include <stdlib.h>

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
//void Timer2_Init(unsigned long period);



extern unsigned short score , maxScore ;//extern (To refer to variable score in Timer1_Driver.c)
extern double ADC1_Result; //extern (To refer to variable ADC1_Result in ADC_Driver.c)
extern long start; //extern (To refer to variable start in GPIO_Driver.c)
// long  falling = 68 , r = 0 , r2 = 0 , falling2 = 68 , f = 0  ; 
extern long falling  , r  , r2 , falling2 , findCar1  , findCar2 , direction ;
extern char flag , loss ;


int main(void){
  
	startGame() ;

  while(1){
		
	  if (start == 1 ) {
			
			fixDataValues() ; 
			firstCar() ;
			if ( findCar2 )  sacondCar( ) ;	 
		
		if (ADC1_Result >= 2100 && ADC1_Result < 4000 ) goSlowToRight() ; 
  			 		
		if (ADC1_Result >= 4000  ) goFastToRight() ; 
		 
		if (ADC1_Result >= 100&& ADC1_Result <= 2000 ) goSlowToLeft() ;	

		if (ADC1_Result < 100 ) goFastToLeft() ;		
		
		 fixBorder() ;

     displayImage() ;
			
			carCrash() ;
			
			if ( loss == 3 ) {
				    game_over() ;
				    continue ;
				 }
		
		Delay100ms(60); 
		speed() ;
				 
		Nokia5110_ClearBuffer();	 
	 }
		 
  }
}



// You can use this timer only if you learn how it works
/*void Timer2_Init(unsigned long period){ 
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}
void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
  TimerCount++;
  Semaphore = 1; // trigger
}*/








