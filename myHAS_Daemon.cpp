#include "myHAS_Daemon.h"
#include <iostream>

//#define _DEBUG_

using namespace std;

myHAS_Daemon::myHAS_Daemon(myHAS_SQLClient * iSQLClient, const char * iMQTTClientID)
{
    pSQLClient = iSQLClient;
    start_MQTT(iMQTTClientID);
}

void myHAS_Daemon::mqtt_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    string topic = msg->topic;
	string sPayload = (char*)msg->payload;

#ifdef _DEBUG_
	cout<<topic<<endl;
#endif

	if(sPayload.length()>0)
	{
		if(topic.find("/prise/")==0)
		{
			//retrieve ID of the prise
			string sID ="";
			if(topic.find("/net/")==0) sID = topic.substr(11, topic.find("/", 11));
			else sID = topic.substr(7, topic.find("/", 7));
			short iID = stoi(sID);

			if(topic.find("/name")!=string::npos) 
				pSQLClient->updateObject("Socket", iID, "Name", sPayload);
			
			else if(topic.find("/status")!=string::npos) 
				pSQLClient->updateObject("Socket", iID, "Status", sPayload);
			
			else if(topic.find("/rules")!=string::npos) 
				pSQLClient->updateObject("Socket", iID, "Rules", sPayload);
			
			else if(topic.find("/type")!=string::npos)
				pSQLClient->updateObject("Socket", iID, "Type", sPayload);
			
			else if(topic.find("/blink")!=string::npos)
				pSQLClient->updateObject("Socket", iID, "Blink", sPayload);
		}
		else if(topic.find("/sensor/")==0)
		{
			string sID ="";
			if(topic.find("/net/")==0) sID = topic.substr(12, topic.find("/", 12));
			else sID = topic.substr(8, topic.find("/", 8));
			
			short iID = stoi(sID);

			if(topic.find("/name")!=string::npos) 
				pSQLClient->updateObject("Sensor", iID, "Name", sPayload);
			else if(topic.find("/type")!=string::npos)
				pSQLClient->updateObject("Sensor", iID, "Type", sPayload);
			else if(topic.find("/value")!=string::npos)
				pSQLClient->updateObject("Sensor", iID, "Value", sPayload);	
		}
		else if(topic.find("/display/")==0)
		{
			//retrieve ID of the display
			string sID ="";
			if(topic.find("/net/")==0) sID = topic.substr(13, topic.find("/", 13));
			else sID = topic.substr(9, topic.find("/", 9));
			short iID = stoi(sID);
			if(topic.find("/name")!=string::npos)
				pSQLClient->updateObject("WeatherStation", iID, "Name", sPayload);
			else if(topic.find("/leftInfo")!=string::npos)
				pSQLClient->updateObject("WeatherStation", iID, "leftInfo", sPayload);
			else if(topic.find("/rightInfo")!=string::npos)
				pSQLClient->updateObject("WeatherStation", iID, "rightInfo", sPayload);
			else if(topic.find("/layout")!=string::npos)
				pSQLClient->updateObject("WeatherStation", iID, "layout", sPayload);
		}
	}
}

void myHAS_Daemon::setTopics()
{
    addTopic("/#");
}
