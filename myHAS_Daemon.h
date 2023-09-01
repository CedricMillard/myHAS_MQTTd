#ifndef myHAS_Daemon_h
#define myHAS_Daemon_h

#include "../myHAS_Library/myHAS_MQTTClient.h"
#include "../myHAS_Library/myHAS_SQLClient.h"

using namespace std;

class myHAS_Daemon : myHAS_MQTTClient
{ 
	public:
		myHAS_Daemon(myHAS_SQLClient * iSQLClient, const char * iMQTTClientID = "myHAS_MQTTd");
		
	protected:
		void mqtt_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
		void setTopics();
	
	private	:
		myHAS_SQLClient * pSQLClient = NULL;
};

#endif
