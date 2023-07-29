/**
  ******************************************************************************
  * File Name          : main.c
  * Date               : 09/10/2014 11:13:03
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2014 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "xnucleoihm02a1.h"
#include "example.h"
#include "example_usart.h"

/**
  * @defgroup   MotionControl
  * @{
  */

/**
  * @addtogroup BSP
  * @{
  */

/**
  * @}
  */ /* End of BSP */

/**
  * @addtogroup MicrosteppingMotor_Example
  * @{
  */

/**
  * @defgroup   ExampleTypes
  * @{
  */

//#define MICROSTEPPING_MOTOR_EXAMPLE        //!< Uncomment to performe the standalone example
#define MICROSTEPPING_MOTOR_USART_EXAMPLE  //!< Uncomment to performe the USART example
#if ((defined (MICROSTEPPING_MOTOR_EXAMPLE)) && (defined (MICROSTEPPING_MOTOR_USART_EXAMPLE)))
  #error "Please select an option only!"
#elif ((!defined (MICROSTEPPING_MOTOR_EXAMPLE)) && (!defined (MICROSTEPPING_MOTOR_USART_EXAMPLE)))
  #error "Please select an option!"
#endif
#if (defined (MICROSTEPPING_MOTOR_USART_EXAMPLE) && (!defined (NUCLEO_USE_USART)))
  #error "Please define "NUCLEO_USE_USART" in "stm32fxxx_x-nucleo-ihm02a1.h"!"
#endif

/**
  * @}
  */ /* End of ExampleTypes */

/**
  * @brief The FW main module
  */

int main(void) {
	/* NUCLEO board initialization */
	NUCLEO_Board_Init();

	/* X-NUCLEO-IHM02A1 initialization */
	BSP_Init();

#ifdef NUCLEO_USE_USART
  /* Transmit the initial message to the PC via UART */
  USART_TxWelcomeMessage();
#endif

  	HAL_Init();

  	USART_Transmit(&huart2, (uint8_t* )"Hello Tyler");

	// Enable GPIO clocks (needed for interrupts)
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Create GPIO structs to manipulate
	GPIO_InitTypeDef GPIO_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct7;
	GPIO_InitTypeDef GPIO_InitStruct8;
	GPIO_InitTypeDef GPIO_InitStruct9;
	GPIO_InitTypeDef GPIO_InitStruct10;

//	GPIO_InitTypeDef GPIO_InitStruct2;
////	GPIO_InitTypeDef GPIO_InitStruct4;
//	GPIO_InitTypeDef GPIO_InitStruct5;
//	GPIO_InitTypeDef GPIO_InitStruct10;


//	// Configure pin 5 on GPIO B as input from push button
//	GPIO_InitStruct5.Pin = GPIO_PIN_5;
//	GPIO_InitStruct5.Mode = GPIO_MODE_IT_FALLING;
//	GPIO_InitStruct5.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct5);


	// Configure pin 6 on GPIO A as input from push button
//	GPIO_InitStruct6.Pin = GPIO_PIN_6;
//	GPIO_InitStruct6.Mode = GPIO_MODE_IT_FALLING;
//	GPIO_InitStruct6.Pull = GPIO_PULLDOWN;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct6);


	// Configure pin 7 on GPIO A as input from push button
	GPIO_InitStruct7.Pin = GPIO_PIN_7;
	GPIO_InitStruct7.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct7.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct7);


	// Configure pin 8 on GPIO A as input from push button
	GPIO_InitStruct8.Pin = GPIO_PIN_8;
	GPIO_InitStruct8.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct8.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct8);

	// Configure pin 9 on GPIO A as input from push button
	GPIO_InitStruct9.Pin = GPIO_PIN_9;
	GPIO_InitStruct9.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct9.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct9);

	// Configure pin 10 on GPIO A as input from push button
	GPIO_InitStruct10.Pin = GPIO_PIN_10;
	GPIO_InitStruct10.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct10.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct10);

	//Enable the 5-9 IRQ and set the priority
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0x01, 0x00);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	// Configure pin 4 on GPIO A as input from push button
//	GPIO_InitStruct4.Pin = GPIO_PIN_4;
//	GPIO_InitStruct4.Mode = GPIO_MODE_IT_RISING;
//	GPIO_InitStruct4.Pull = GPIO_PULLDOWN;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct4);
//
//	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	// Configure pin 2 on GPIO A as input from push button
//	GPIO_InitStruct2.Pin = GPIO_PIN_2;
//	GPIO_InitStruct2.Mode = GPIO_MODE_IT_FALLING;
//	GPIO_InitStruct2.Pull = GPIO_PULLDOWN;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct2);
//
//	HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	// Configure pin 2 on GPIO A as input from push button
//	GPIO_InitStruct10.Pin = GPIO_PIN_10;
//	GPIO_InitStruct10.Mode = GPIO_MODE_IT_FALLING;
//	GPIO_InitStruct10.Pull = GPIO_PULLDOWN;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct10);
//
//	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Configure pin 1 on GPIO A as output
	GPIO_InitStruct1.Pin = GPIO_PIN_1;
	GPIO_InitStruct1.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct1.Pull = GPIO_PULLUP;
	GPIO_InitStruct1.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct1);

#if defined (MICROSTEPPING_MOTOR_EXAMPLE)
  /* Perform a batch commands for X-NUCLEO-IHM02A1 */
  MicrosteppingMotor_Example_01();

  /* Infinite loop */
  while (1);
#elif defined (MICROSTEPPING_MOTOR_USART_EXAMPLE)
  /* Fill the L6470_DaisyChainMnemonic structure */
  Fill_L6470_DaisyChainMnemonic();

  // Counter to run characterization code multiple times
  int counter = 0;
  /* Infinite loop */
  while (1)
  {
    /* Check if any Application Command for L6470 has been entered by USART */
    USART_CheckAppCmd();

	// Can increase counter if moving at slow speed and run multiple
	// tests without restarting
    if(counter < 1)
    {
    	// Arguments are motor #, direction, speed
    	L6470_Run(1, L6470_DIR_FWD_ID, 25000);
    	
		// Delay for 1 second
		HAL_Delay(1000);
		
		// Stop
    	L6470_HardStop(1);
    	
		// Delay for 5 seconds to record pencil line
		HAL_Delay(5000);
    	counter++;
    }
  }
#endif
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ /* End of MicrosteppingMotor_Example */

/**
  * @}
  */ /* End of MotionControl */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
