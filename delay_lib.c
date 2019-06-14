#include "delay_lib.h"

void Delay100ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 7277;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}