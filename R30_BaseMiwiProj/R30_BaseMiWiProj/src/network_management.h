/*
 * network_management.h
 *
 * Created: 10/23/2018 11:24:58 AM
 *  Author: C41175
 */ 


#ifndef NETWORK_MANAGEMENT_H_
#define NETWORK_MANAGEMENT_H_

#define NETWORK_FREEZER_OFF false
#define NETWORK_FREEZER_ON true

void NetworkInit(bool freezer_enable);

void NetworkTasks(void);

#endif /* NETWORK_MANAGEMENT_H_ */