#include "Nokia5110.h"
#include "GPIO_Driver.h"
#include "tm4c123gh6pm.h"
#include "delay_lib.h"
#include "ADC_Driver.h"
#include "Timer1_Driver.h"
#include "Random.h"
#include "TExaS.h"
#include <time.h>
#include <stdlib.h>

void startGame() ;
void fixDataValues() ;
void goSlowToRight() ;
void goSlowToLeft() ;
void goFastToRight() ;
void goFastToLeft() ;
void fixBorder() ;
void firstCar() ;
void sacondCar() ;
void displayImage() ;
void carCrash ()  ;
void game_over() ;
void speed () ;
long Check(long X , long x , long y ) ;
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
