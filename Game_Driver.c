#include "Game_Driver.h"
#include "GPIO_Driver.h"
#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include <time.h>
#include <stdlib.h>

const unsigned char car[] ={
 0x42, 0x4D, 0x2A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xB4, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,

};


// hello
extern long start;
char flag=0;
// extern long falling  , r  , r2 , falling2  , f   ;
long  falling = 68 , r = 0 , r2 = 0 , falling2 = 68 , findCar1 = 1 , findCar2 = 0 , direction = 30 , sp ; 
extern unsigned short score;
char i , loss = 0 ;

void startGame(){
	
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Random_Init(1);
	EnableInterrupts();  
  Nokia5110_Init();
	ADC1_INIT();
	PortB_Init();
	PortF_Init();
  Timer1_Init();
  Nokia5110_ClearBuffer();

	
  Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("To start ");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("press the ");
  Nokia5110_SetCursor(1, 3);
  Nokia5110_OutString("Button");
  Nokia5110_SetCursor(2, 4);
}


void fixDataValues() {
					
		     if( flag== 1 ){ 
					 falling = 68;
					 score=0;
						loss=0; 
					 flag = 0;
					 findCar2 = 0 ;
			    }			 
			
}

void firstCar(){
	
				if ( score >= 5 ) findCar2 = 1 ;
	
				if ( falling >= 68 ){
				falling = 0 ;
	     r = rand() % 48 ;
					if ( r < 14 )
					r += 14 ;
				}
}

void sacondCar( ) {
					
				if ( falling2 >= 68){
				    falling2 = 0 ;
						r2 = rand() % 48 ;
					if ( r2 < 14 ) r2 += 14 ;
				}
				if ( abs(falling - falling2) <= 20 || abs( r - r2) < 14 ) findCar2 = 0 ;  

}


void goSlowToRight(){ direction-- ; } 
void goSlowToLeft() { direction++ ; } 
void goFastToRight(){ direction -=5 ; }
void goFastToLeft() { direction += 5 ; } 

void fixBorder () {
	if ( direction <= 14 ) 
		     direction = 14 ;			 
	  if ( direction >= 48 ) 
		     direction = 48 ;
}





long Check(long X , long x , long y ) {
	 long x1 = X - 12 , y1 = 84 , x2 = X , y2 = 66 ;
	
	 long x3 = x - 12 , y3 = y + 18 , x4 = x , y4 = y ;
		 
    if (x2 <  x3 || x4 < x1) 
		return 0; 

	if (y2 > y3 || y4 > y1) 
		return 0; 

	return 1 ;

}

void speed() {
		 sp = 2 + ( score / 8 ) ;
		if ( sp >= 6 ) sp = 6 ;
		falling 	+= sp;
	 if (findCar2)	falling2  += sp;

	
}

void displayImage() {
	
		if ( findCar2 ) Nokia5110_PrintBMP(falling2 , r2 , car, 0); 
		Nokia5110_PrintBMP(falling, r , car, 0);
		Nokia5110_PrintBMP(63, direction , car, 0);   	      
    Nokia5110_DisplayBuffer();
	
}
 
void game_over() {
			start = 0;
			flag=1;
			Nokia5110_Clear();
			Nokia5110_SetCursor(1, 0);
			Nokia5110_OutString("Game Over");
			Nokia5110_SetCursor(1, 1);
			Nokia5110_OutString("To start ");
			Nokia5110_SetCursor(1, 2);
			Nokia5110_OutString("again press");
			Nokia5110_SetCursor(1, 3);
			Nokia5110_OutString("the Button");
			Nokia5110_SetCursor(1, 4);
			Nokia5110_OutString("Score:");
			Nokia5110_SetCursor(7, 4);
			Nokia5110_OutUDec(score);
		 for(i=0;i<4;++i){   
				 GPIO_PORTB_DATA_R |=(1<<0);
				 Delay100ms(250);
				 GPIO_PORTB_DATA_R &=~(1<<0);
				 Delay100ms(250);
		 }
	
}


void carCrash() {
			if (Check (direction , r , falling) == 1 ) {
			   falling = 68;
				 loss++;
		}
		
	if (findCar2) {
				if (Check (direction , r2 , falling2) == 1 ) {
			   falling2 = 68;
				 loss++;
		}
			
	}
}
