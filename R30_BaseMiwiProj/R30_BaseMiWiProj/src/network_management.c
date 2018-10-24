/*
 * network_management.c
 *
 * Created: 10/23/2018 11:24:26 AM
 *  Author: C41175
 */ 

#include <asf.h>
#include "network_management.h"
#include "debug_interface.h"
#include "miwi_api.h"
#include "miwi_nvm.h"

#include "app.h" //needed for receive callback function

uint8_t AdditionalNodeID[ADDITIONAL_NODE_ID_SIZE] = {0x1}; //ToDo: what is this?

uint8_t myChannel = 8;

static void Connection_Confirm(miwi_status_t status)
{
	printf("\r\nConnect Operation Status: ");
	printf("%d\n",status);
}

void NetworkInit(bool freezer_enable)
{
	
	if(MiApp_SubscribeDataIndicationCallback(ReceivedDataIndication))
	{
		DEBUG_PRINT(printf("MiWi receive callback registered\r\n"));
	}
	else
	{
		DEBUG_PRINT(printf("error: MiWi receive callback not registered\r\n"));
	}
	
	DEBUG_PRINT(printf("network init\r\n"));
	MiApp_ProtocolInit(NULL, NULL); //initializes MiApp, MAC, PHY, & radio i/f 
	
	
	 DEBUG_PRINT(printf("set default channel\r\n"));
	 if( MiApp_Set(CHANNEL, &myChannel) == false )
	 {
		 DEBUG_PRINT(printf("channel %d not supported\r\n", myChannel));
	 }
	 
	 DEBUG_PRINT(printf("set connection mode\r\n"));
	 MiApp_ConnectionMode(ENABLE_ALL_CONN);
	 
	 DEBUG_PRINT(printf("start connection\r\n"));
	 MiApp_StartConnection(START_CONN_DIRECT, 10, 0, Connection_Confirm);
	 
//	 role = true; //true = PAN coordinator, false = end device
//	 nvmPutMyRole(&role);  // Saving the Role of the device
	 
}

void NetworkTasks(void)
{
	P2PTasks(); //maintain the operation of the stack - call often
}
