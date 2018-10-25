/*
 * app.c
 *
 * Created: 10/23/2018 1:57:40 PM
 *  Author: C41175
 */ 

#include <asf.h>
#include "app.h"
#include "debug_interface.h"

void AppTask(void)
{
	if(port_pin_get_input_level(SW0))
	{
		port_pin_set_output_level(LED1, LED_OFF);
	}
	else
	{
		port_pin_set_output_level(LED1,LED_ON);
	}
}

void ReceivedDataIndication (RECEIVED_MESSAGE *ind)
{
	uint8_t startPayloadIndex = 0;
	/*******************************************************************/
	// If a packet has been received, handle the information available
	// in rxMessage.
	/*******************************************************************/
	DEBUG_PRINT(printf("data received: "));
	
	// Toggle LED to indicate receiving a packet.
	port_pin_toggle_output_level(LED0);
	
	for(uint8_t i=startPayloadIndex; i<rxMessage.PayloadSize;i++)
	{
		putchar(rxMessage.Payload[i]);
	}
}
