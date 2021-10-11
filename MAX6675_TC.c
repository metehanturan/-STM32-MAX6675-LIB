#include "MAX6675_TC.h"

//==========================================
// Title	:	THERMOCOUPLE STM32 LIBRARY
// Author :	Metehan TURAN
// Date	  :	9 Oct 2021
// Ver. 	:	1.0
//==========================================

//****************************** VARIABLES ******************************
struct tc_data s_tc_data = {0, 0, 0};

//****************************** FUNCTIONS ******************************
// THERMOCUPLE START FUNCTION
void tc_start(void)
{
	HAL_GPIO_WritePin(TC_CS_PORT, TC_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_Receive(&TC_SPI_TYPE, s_tc_data.receive_buf, 2, 100);
	s_tc_data.tc_state = ((s_tc_data.receive_buf[1] & 0x04) >> 2);
	HAL_GPIO_WritePin(TC_CS_PORT, TC_CS_PIN, GPIO_PIN_SET);
}

// READING THERMOCOUPLE RAW DATA
// LENGTH OF DATA ARE 12 BITS.
// IF THE FUNCTION RETURN 9999, THIS IS FAIL.
uint16_t read_tc_raw_data(void)
{
	if(s_tc_data.tc_state == 1) return 9999;
	
	s_tc_data.tc_raw_data  = (uint16_t)(s_tc_data.receive_buf[1]) >> 3;
	s_tc_data.tc_raw_data |= (uint16_t)(s_tc_data.receive_buf[0]) << 5;
	return s_tc_data.tc_raw_data;
}

// READING THERMOCOUPLE TEMPERATURE DATA
// IF THE FUNCTION RETURN 9999, THIS IS FAIL.
float read_tc_temp_data(void)
{
	if(s_tc_data.tc_state == 0)
	{
		return s_tc_data.tc_raw_data * 0.25;
	}	
		
	return 9999;
}

// RETURN THERMOCOUPLE STATE  
// RESULT 1 -> THERMOCOUPLE IS CONNECTED.
// RESULT 2 -> THERMOCOUPLE IS UNCONNECTED. 
// IF THE FUNCTION RETURN 255, THIS IS FAIL.
uint8_t read_tc_state(void)
{
	if(s_tc_data.tc_state == 0) return 1;
	if(s_tc_data.tc_state == 1) return 2;
	
	return 255;
}
