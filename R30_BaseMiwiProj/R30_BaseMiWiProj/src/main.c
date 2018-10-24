/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "debug_interface.h"
#include "rf_transceiver.h"
#include "network_management.h"
#include "miwi_api.h"

void ReadMacAddress(void);

int main (void)
{
	system_init();
	delay_init(); //used to to initialize radio interface
	configure_console();
	
	printf("R30 Base Project\r\n");
	uint32_t cpuClock = system_cpu_clock_get_hz();
	DEBUG_PRINT(printf("CPU clock %lu Hz\r\n", cpuClock));

	TransceiverConfig(); //initialize pins to the radio
	
	NetworkInit(NETWORK_FREEZER_OFF);
	
	while(1)
	{
		if(port_pin_get_input_level(SW0))
		{
			port_pin_set_output_level(LED1, LED_OFF);
		}
		else
		{
			port_pin_set_output_level(LED1,LED_ON);
		}
		NetworkTasks();
	}
}


/*********************************************************************
* Function:         void ReadMacAddress()
*
* PreCondition:     none
*
* Input:		    none
*
* Output:		    Reads MAC Address from MAC Address EEPROM
*
* Side Effects:	    none
*
* Overview:		    Uses the MAC Address from the EEPROM for addressing
*
* Note:			    
**********************************************************************/
void ReadMacAddress(void)
{ 
	//placholder function to read MAC address
   for(uint8_t i=0; i<MY_ADDRESS_LENGTH; i++)
   {
	   myLongAddress[i] = i+1;
   }

}