#include "stm32f4xx.h"

/*HAL_UART_Transmit() & uart_init() both of these functions need to use
  USART_HandleTypeDef structure, hence we've declared it as a Global variable*/
USART_HandleTypeDef huart2; 	//USART InitTypeDef structure comes under HandleTypeDef

void uart_init(void);

char message[20] = "Hello from STM32\r\n";
int main (){

	HAL_Init();
	uart_init();

	while(1){
		HAL_UART_Transmit (&huart2, (uint8_t *) message, 20, 100); //MessageLength=20 & Timeout=100ms (Don't keep trying to achieve it if that's not possible)
		HAL_Delay(10);		//10ms delay
	}
}

//SysTick is the Heartbeat of the system
//Delay functions depends on SysTick
void SysTick_Handler(void){
	HAL_IncTick();
}


//Initialization of UART Module
void uart_init(void){

	__HAL_RCC_GPIOA_CLK_ENABLE();		//Enable UART Pins Clock access (Port A)
	__HAL_RCC_USART2_CLK_ENABLE();		//Enable UART Module's Clock Access

	//Configure pins to act as Alternate function pins (UART)
	//Port-A Pin2 = TX | Port-A Pin3 = RX
	GPIO_InitTypeDef GPIO_InitStruct = {0};  		//Configure GPIO Pins as USART Pins we use this structure definition
	GPIO_InitStruct.Pin  = 	GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = 	GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2; 	//USART2 TX-RX belongs to Alternate function 07
	GPIO_InitStruct.Pull = 	GPIO_NOPULL;  			//No pull-up resistors required on these pins
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 		//Applying pin configuration to Port A pins


	//Configure UART Module
	huart2.Instance = USART2;   	//.Instance allows us to select which USART Module do we want to use
	huart2.Init.BaudRate = 115200; 	//InitTypeDef allows us to configure our USART Specifications
	huart2.Init.WordLength = UART_WORDLENGTH_8B;  		//Word-length = 8-bits
	huart2.Init.StopBits = UART_STOPBITS_1;				//Stop-bits = 1-bit
	huart2.Init.Parity = UART_PARITY_NONE;				//Parity = None
	huart2.Init.Mode = UART_MODE_TX; 					//Mode = TX & RX
	//huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//HwFlowCtl means bi-directional communication
	//huart2.Init.OverSampling = UART_OVERSAMPLING_16;	//Oversampling = 16*SamplingRate
	HAL_UART_Init(&huart2);		//Initializing UART2 module

}






