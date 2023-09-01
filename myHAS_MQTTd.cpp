/**
 * MQTT daemon
 * Subscribe to all topics from MQTT server and update status of each object in a database
 * Allows to display status in the website
 * 
 * TODO: 
 *  - clean objects from dB if they do not report status for a while (TBD)
 *  
 * (c) Cédric Millard 2023
 */

#include <iostream>
#include <unistd.h> 
#include "../myHAS_Library/myHAS_SQLClient.h"
#include "myHAS_Daemon.h"

#define _DEBUG_

using namespace std;

int main(void)
{
	myHAS_SQLClient * pSQL = new myHAS_SQLClient();
	myHAS_Daemon pDaemon(pSQL);
	while(true)
	{
		sleep(1);
	}
	cout<<"Exiting...\n";

	delete pSQL;
	
	return 0;
}
