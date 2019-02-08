//GROVE_NAME        "Grove - Hall Sensor"
//SKU               101020046
//WIKI_URL          http://wiki.seeedstudio.com/Grove-Hall_Sensor/

#include <stdlib.h>
#include <applibs/gpio.h>

#pragma once

void *GroveHallSensor_Init(GPIO_Id sensor);
GPIO_Value_Type GroveHallSensor_GetState(void *inst);
