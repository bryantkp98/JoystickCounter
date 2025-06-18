#include "stm32l476xx.h"
#include "SysTimer.h"
#define RED_LED_PORT GPIOA
#define GREEN_LED_PORT GPIOE

void Btn_Init(void);
void SEG_Init(void);
void setODRs(uint8_t value);
void internalClock(void);
void countup(int pin5);
void countdown(int pin3);
