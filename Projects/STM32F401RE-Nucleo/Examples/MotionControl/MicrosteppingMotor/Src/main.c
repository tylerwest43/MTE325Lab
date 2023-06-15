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

/**
  * @}
  */ /* End of ExampleTypes */

/**
  * @brief The FW main module
  */

int main(void) {

	// Constant defined for minimum consecutive reads when debouncing
	// push button input
	const int MIN_CONSEC_READS = 30;

	/* NUCLEO board initialization */
	NUCLEO_Board_Init();

	/* X-NUCLEO-IHM02A1 initialization */
	BSP_Init();

#ifdef NUCLEO_USE_USART
  /* Transmit the initial message to the PC via UART */
  USART_TxWelcomeMessage();
#endif

	// Create GPIO Structs to manipulate
	GPIO_InitTypeDef GPIO_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct2;

	// Configure pin 13 on GPIO C as input from push button
	GPIO_InitStruct1.Pin = GPIO_PIN_13;
	GPIO_InitStruct1.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct1.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct1);

	// Configure pin 1 on GPIO A as output
	GPIO_InitStruct2.Pin = GPIO_PIN_1;
	GPIO_InitStruct2.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct2.Pull = GPIO_PULLUP;
	GPIO_InitStruct2.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct2);

	// Variable to track the status of the light (1 is on, 0 is off)
	int lightOn = 0;

	// Variable to hold status of pin read on each loop iteration
	int pin13Set = 0;

	// Variable to count the number of consecutive reads of push button pin for debouncing
	int numConsecReads = 0;

	while (1)
	{
		// If pin13Set resolves to 0 (GPIO_PIN_RESET) then that means the button is pressed
		// If pin13Set resolves to 1 (GPIO_PIN_SET) then that means the button is not pressed
		pin13Set = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

		// Debouncing code, require that we get 30 consecutive reads of the
		// button being pushed before taking action

		// Add one to the read counter if the button is being pushed
		if (pin13Set == GPIO_PIN_RESET)
		{
			numConsecReads++;
		}
		// Reset the read counter to 0 if the button is not being pushed
		else
		{
			numConsecReads = 0;
		}

		// Button has been pushed and light is not already on
		if (numConsecReads == MIN_CONSEC_READS && lightOn == 0)
		{
			// Turn on the light and record the state of the light
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			lightOn = 1;
		}
		// Button has been pushed and light is already on
		else if (numConsecReads == MIN_CONSEC_READS && lightOn == 1)
		{
			// Turn off the light and record the state of the light
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			lightOn = 0;
		}
	}
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
