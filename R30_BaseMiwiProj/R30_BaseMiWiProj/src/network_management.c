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
	switch(status)
	{
		case SUCCESS:
		{
			DEBUG_PRINT(printf("SUCCESS\r\n"));
			break;
		}
		case FAILURE:
		{
			DEBUG_PRINT(printf("FAILURE\r\n"));
			break;
		}
		case CHANNEL_ACCESS_FAILURE:
		{
			DEBUG_PRINT(printf("CHANNEL_ACCESS_FAILURE\r\n"));
			break;
		}
		case NO_ACK:
		{
			DEBUG_PRINT(printf("NO_ACK\r\n"));
			break;
		}
		case TIMER_EXPIRED:
		{
			DEBUG_PRINT(printf("TIMER_EXPIRED\r\n"));
			break;
		}
		case TRANSACTION_EXPIRED:
		{
			DEBUG_PRINT(printf("TRANSACTION_EXPIRED\r\n"));
			break;
		}
		case ALREADY_EXISTS:
		{
			DEBUG_PRINT(printf("ALREADY_EXISTS\r\n"));
			break;
		}
		case NO_ROUTE:
		{
			DEBUG_PRINT(printf("NO_ROUTE\r\n"));
			break;
		}
		case SCAN_NO_BEACON:
		{
			DEBUG_PRINT(printf("SCAN_NO_BEACON\r\n"));
			break;
		}
		case SCAN_MAX_REACHED:
		{
			DEBUG_PRINT(printf("SCAN_MAX_REACHED\r\n"));
			break;
		}
		case MEMORY_UNAVAILABLE:
		{
			DEBUG_PRINT(printf("MEMORY_UNAVAILABLE\r\n"));
			break;
		}
		case ERR_TX_FAIL:
		{
			DEBUG_PRINT(printf("ERR_TX_FAIL\r\n"));
			break;
		}
		case ERR_TRX_FAIL:
		{
			DEBUG_PRINT(printf("ERR_TRX_FAIL\r\n"));
			break;
		}
		case ERR_INVALID_INPUT:
		{
			DEBUG_PRINT(printf("ERR_INVALID_INPUT\r\n"));
			break;
		}
		default:
		{
			DEBUG_PRINT(printf("connection fail? default case\r\n"));
			break;
		}
	}
}

void NetworkInit(bool freezer_enable, bool networkRole)
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
	 
	role = networkRole;//true = PAN coordinator, false = end device
//	 nvmPutMyRole(&role);  // Saving the Role of the device
	if(role==true)
	{
		DEBUG_PRINT(printf("Role = PAN Coordinator\r\n"));
		DEBUG_PRINT(printf("start PAN\r\n"));
		MiApp_StartConnection(START_CONN_DIRECT, 10, (1L << myChannel), Connection_Confirm);
	}
	else
	{
		DEBUG_PRINT(printf("Role = Edge Node\r\n"));
		DEBUG_PRINT(printf("Connect to PAN\r\n"));
		uint8_t ret = MiApp_EstablishConnection(myChannel, 0, NULL, 0, Connection_Confirm);
		if(ret == 0xFF)
		{
			DEBUG_PRINT(printf("Connection not established\r\n"));
		}
		else
		{
			DEBUG_PRINT(printf("Connected to peer %u\r\n", ret));
		}
	}
	 
}

void NetworkTasks(void)
{
	P2PTasks(); //maintain the operation of the stack - call often
}
