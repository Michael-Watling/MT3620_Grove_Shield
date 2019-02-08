#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// applibs_versions.h defines the API struct versions to use for applibs APIs.
#include "applibs_versions.h"
#include <applibs/log.h>

#include "mt3620_rdb.h"

#include "Grove.h"
#include "Sensors/GroveHallSensor.h"
// This C application for the MT3620 Reference Development Board (Azure Sphere)
// outputs a string every second to Visual Studio's Device Output window
//
// It uses the API for the following Azure Sphere application libraries:
// - log (messages shown in Visual Studio's Device Output window during debugging)

static volatile sig_atomic_t terminationRequired = false;

/// <summary>
///     Signal handler for termination requests. This handler must be async-signal-safe.
/// </summary>
static void TerminationHandler(int signalNumber)
{
    // Don't use Log_Debug here, as it is not guaranteed to be async-signal-safe.
    terminationRequired = true;
}

/// <summary>
///     Main entry point for this sample.
/// </summary>
int main(int argc, char *argv[])
{
    Log_Debug("Application starting.\n");

    // Register a SIGTERM handler for termination requests
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = TerminationHandler;
    sigaction(SIGTERM, &action, NULL);

	static GPIO_Value_Type sensor_status, last_sensor_status;
	void* sensor = GroveHallSensor_Init(4); //Connect Hall Sensor to a GPIO Port. 
	//If using GPIO0 the set this number to 0, if using GPIO4 set this number to 4.
	last_sensor_status = GroveHallSensor_GetState(sensor);

    // Main loop
	while (!terminationRequired) {

		sensor_status = GroveHallSensor_GetState(sensor);

		if (sensor_status != last_sensor_status) {
			if (sensor_status == 0) {
				Log_Debug("Magnet.\n");
			}
			else {
				Log_Debug("No Magent.\n");
			}
		}
		last_sensor_status = sensor_status;

	}
	Log_Debug("Application exiting.\n");
	return 0;
}
