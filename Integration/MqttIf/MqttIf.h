#ifndef _MQTT_IF_H_
#define _MQTT_IF_H_

#include "mqtt.h"
#include "Std_Types.h"

Std_ReturnType MqttIf_Init(MQTT_Client *client);
Std_ReturnType MqttIf_Publish(const char* topic, const char* data, int data_length, int qos, int retain);

#endif