#ifndef __MAX6675_TC__
#define __MAX6675_TC__

//==========================================
// Title	:	THERMOCOUPLE STM32 LIBRARY
// Author :	Metehan TURAN
// Date	  :	9 Oct 2021
// Ver. 	:	1.0
//==========================================

//****************************** INCLUDES ******************************
#include "stm32f0xx_hal.h"
#include "main.h"
#include "spi.h"

//****************************** DEFINES ******************************
#define TC_CS_PIN		TC_CS_Pin
#define TC_CS_PORT	TC_CS_GPIO_Port
#define TC_SPI_TYPE	hspi1

//****************************** VARIABLES ******************************
struct tc_data
{
	uint8_t receive_buf[2];
	uint16_t tc_raw_data;
	uint8_t tc_state;
};

//****************************** EXTERNS ******************************
extern struct tc_data s_tc_data;

//****************************** FUNCTIONS ******************************
void tc_start(void);
uint16_t read_tc_raw_data(void);
float read_tc_temp_data(void);
uint8_t read_tc_state(void);

#endif
