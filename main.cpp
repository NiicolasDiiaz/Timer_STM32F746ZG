#include <stdio.h>
#include "STM32F7xx.h"

int contador=0;
int tiempo=0;
	
int main(void)
{
	RCC->AHB1ENR=0x6;//PUERTO B
	RCC->APB1ENR=0x1;//TIMER 2
	
	GPIOC->MODER=0;
	
	GPIOB->MODER=0x10004001;//COLOCAR COMO SALIDA LOS LEDS
	GPIOB->PUPDR=0x10004001;//PULL UP
	GPIOB->OTYPER=0x0;
	GPIOB->OSPEEDR=0x10004001;//VELOCIDAD MEDIA
	
	
	TIM2->ARR=14;//RESET
	TIM2->PSC=15999999;//PRE-ESCARLER DE TIEMPO
	
	while(1)
	{
		if((GPIOC->IDR & 0x2000)==0x2000){
			if (contador==0){
				TIM2->EGR=0x1;
			}
			contador++;			
			TIM2->CR1=0x1;
		}
		else if ((GPIOC->IDR & 0x2000)==0){
			TIM2->CR1=0;
			tiempo = TIM2->CNT;
			contador=0;
			
		}
			
			if(TIM2->CNT<1)
			{
				GPIOB->ODR=0x0080; 
			}
			else if (TIM2->CNT>2&TIM2->CNT<4)
			{
				GPIOB->ODR=0x0001;
			}
			else if (TIM2->CNT>4&TIM2->CNT<6)
			{
				GPIOB->ODR=0x4000;
			}
			else if(TIM2->CNT>6 & TIM2->CNT<8)
			{
				GPIOB->ODR |=0x0001; //Verde
				GPIOB->ODR |=0x4000; //Rojo
			}
			else if(TIM2->CNT>8 & TIM2->CNT<10)
			{
				GPIOB->ODR |=0x4000; //Rojo
				GPIOB->ODR |=0x0080; //Azul
			}
			else if (TIM2->CNT>12)
			{
				GPIOB->ODR |=0x4081; //Azul, Verde, Rojo
			}
				
		}
	
	}