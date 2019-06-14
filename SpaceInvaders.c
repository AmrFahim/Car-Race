
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









