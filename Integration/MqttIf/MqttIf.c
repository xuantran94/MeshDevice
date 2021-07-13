#include "MqttIf.h"

MQTT_Client* localClient_st;

Std_ReturnType MqttIf_Init(MQTT_Client *client)
{
    localClient_st = client;
    return E_OK;
}

Std_ReturnType MqttIf_Publish(const char* topic, const char* data, int data_length, int qos, int retain)
{
    MQTT_Publish(localClient_st, topic, data, data_length, qos, retain);
    return E_OK;
}