#include "GroveHallSensor.h";

typedef struct
{
	int sensorFind;
}
GroveHallInstance;

void *GroveHallSensor_Init(GPIO_Id sensor)
{
	GroveHallInstance *this = (GroveHallInstance*)malloc(sizeof(GroveHallInstance));
	this->sensorFind = GPIO_OpenAsInput(sensor);
	//this->ledFd = GPIO_OpenAsOutput(led, GPIO_OutputMode_PushPull, GPIO_Value_Low);

	return this;
}

GPIO_Value_Type GroveHallSensor_GetState(void *inst)
{
	GPIO_Value_Type state;
	GroveHallInstance *this = (GroveHallInstance*)inst;
	GPIO_GetValue(this->sensorFind, &state);

	return state;
}
