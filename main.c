#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Delay(uint32_t nTime);

int main(void)
{
  int i;

  /* Initialize LED which connected to PC13, Enable the Clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	

  /* Configure the GPIO_LED pin */
	  /* Initialize Leds mounted on STM32 board */
  GPIO_InitTypeDef  GPIO_InitStructure;
	// We will work with Pin_6 & Pin_14
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_14; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		

	if (SysTick_Config(SystemCoreClock / 1000))
     while (1);
	
  while (1)
  { 
		/*GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		Delay(15);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		Delay(5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		Delay(30);*/
		

		GPIOB->ODR=GPIO_Pin_14;
		GPIOA->ODR=GPIO_Pin_6;
		Delay(15);
		GPIOB->ODR=~GPIO_Pin_14;
		Delay(5);
		GPIOA->ODR=~GPIO_Pin_6;
		Delay(30);

  }
}

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void SysTick_Handler(void){
    if (TimingDelay != 0x00)
        TimingDelay --;
}
