#include "stm32l476xx.h"
#include "SysTimer.h"
#include "SysTimer.h"



void Btn_Init(void){
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOAEN;
	//PA3 for input, up on joystick 
	GPIOA->MODER &= ~(3UL)<< 2*3;
	GPIOA->MODER &= ~(3UL)<< 2*5;
	GPIOA->OSPEEDR |= (3UL)<< 2*3 ;
	GPIOA->OSPEEDR |= (3UL)<< 2*5;
	GPIOA->OTYPER &= ~ (0x2);
	GPIOA->OTYPER &= ~(0x8);
	GPIOA->PUPDR &= ~ (3UL)<< 2*3 ;
	GPIOA->PUPDR &= ~(3UL)<< 2*5;
	GPIOA->PUPDR |= (2UL)<< 2*3 ;
	GPIOA->PUPDR |= (2UL)<< 2*5;
	

	
	
	//PA5 for input, down on joystick 
	
	
}
uint32_t ButtonPressed(int x){
	return (GPIOA->IDR & 1U << x );
	//return (GPIOA->IDR & 2U);
}



void SEG_Init(void){

	/* Enable GPIOs clock */ 	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOHEN | RCC_AHB2ENR_GPIOEEN;
	
	//PH0
	GPIOH->MODER &= ~(0x3);
	GPIOH->MODER |= 0x1;
	GPIOH->OSPEEDR |= 0x3;
	GPIOH->OTYPER &= ~(0x1);
	GPIOH->PUPDR &= ~(0x3);
	
	//PE10-PE15
	GPIOE->MODER &= ~(0xFFFU << (2*10));
	GPIOE->MODER |= (0x555U<< (2*10));
	GPIOE->OSPEEDR |= (0xFFFU<<(2*10));
	GPIOE->OTYPER &= ~(0x3FU<<10);
	GPIOE->PUPDR &= ~(0xFFFU << (2*10));
}

void setODRs(uint8_t value) {
	GPIOE->ODR &= ~(0xFC00);
	GPIOE->ODR |= (uint32_t) ((value&0x3F)<<10);
	GPIOH->ODR &=~(0x1);
	GPIOH->ODR |= (value>>6);
}

void countup(int pin5){
	uint8_t segt[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,0x6F};
	uint8_t i=0;
	int v =1;
	
	while (1) {
		v = 0;
		while((ButtonPressed(pin5) == 1UL << pin5)){
			if(v==0){
		setODRs(segt[i]);
		i = (i+1) % 10;
			}
			v=1;
	}
	delay(10);
}
	
}
void countdown(int pin3){
	uint8_t segt[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,0x6F};
	uint8_t i=0;
	int v =1;
	
	while (1) {
		v = 0;
			while((ButtonPressed(pin3) == 1UL << pin3)){
	if(v==0){
		if(i==0){
			i=9;
		}
		setODRs(segt[i]);
		i = (i-1) % 10;
	}
			v=1;
	}
	delay(10);
}
	
}
void internalClock(void){
	
	RCC->CR |= RCC_CR_MSION; 
	
	// Select MSI as the clock source of System Clock
	RCC->CFGR &= ~RCC_CFGR_SW; 
	
	// Wait until MSI is ready
	while ((RCC->CR & RCC_CR_MSIRDY) == 0); 	
	
	// MSIRANGE can be modified when MSI is OFF (MSION=0) or when MSI is ready (MSIRDY=1). 
	RCC->CR &= ~RCC_CR_MSIRANGE; 
	RCC->CR |= RCC_CR_MSIRANGE_7;  // Select MSI 8 MHz	
 
	// The MSIRGSEL bit in RCC-CR select which MSIRANGE is used. 
	// If MSIRGSEL is 0, the MSIRANGE in RCC_CSR is used to select the MSI clock range.  (This is the default)
	// If MSIRGSEL is 1, the MSIRANGE in RCC_CR is used. 
	RCC->CR |= RCC_CR_MSIRGSEL; 
	
	// Enable MSI and wait until it's ready	
	while ((RCC->CR & RCC_CR_MSIRDY) == 0); 		
}

	
