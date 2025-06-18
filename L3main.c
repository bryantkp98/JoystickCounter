#include "stm32l476xx.h"
#include "L3Mane.h"
#include "SysTimer.h"

int main(void){
	
	internalClock(); // Set System Clock as 8 MHz
	SysTick_Init();
	SEG_Init();
	Btn_Init();
	
	while(1){
	countup(5);
	countdown(3);
	}
	}