

/**
 * main.c
 */

/****************************************************************************
 *                                  Includes
 * ************************************************************************/

/* Application file include */

#include"APP/APP.h"


int main(void)
{

    /* Initialize all components */
    vSetupHardware();

    while(xTaskCreate( vRunTimeMeasurementsTask,   /* Task function implementation */
                 "Runtime measurements",           /* Task name (Debugging purposes) */
                 256,                              /* Stack size of the task : 256 words >> 1024 bytes */
                 NULL,                             /* Passed parameter to refer instance */
                 4,                                /* Priority */
                 &task0handle                      /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vInitialValuesTask,   /* Task function implementation */
                 "Initial values",           /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 NULL,                       /* Passed parameter to refer driver instance */
                 2,                          /* Priority */
                 &task1handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vTemperatureMonitoringTask, /* Task function implementation */
                 "Temperature monitoring",   /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&driver),           /* Passed parameter to refer driver instance */
                 1,                          /* Priority */
                 &task2handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vTemperatureMonitoringTask, /* Task function implementation */
                 "Temperature monitoring",   /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&passenger),        /* Passed parameter to refer passenger instance */
                 1,                          /* Priority */
                 &task3handle                       /* Task handle to refer the Task */
    ) == pdFAIL);


    while(xTaskCreate( vButtonMonitoringTask,/* Task function implementation */
                 "Button monitoring",        /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&driver),           /* Passed parameter to refer driver instance */
                 1,                          /* Priority */
                 &task4handle                        /* Task handle to refer the Task */
    )== pdFAIL);

    while(xTaskCreate( vButtonMonitoringTask,/* Task function implementation */
                 "Button monitoring",        /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&passenger),        /* Passed parameter to refer passenger instance */
                 1,                          /* Priority */
                 &task5handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vHeatingLevelMonitoringTask,/* Task function implementation */
                 "Heating level monitoring", /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&driver),           /* Passed parameter to refer Driver instance */
                 1,                          /* Priority */
                 &task6handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vHeatingLevelMonitoringTask,/* Task function implementation */
                 "Heating level monitoring", /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&passenger),        /* Passed parameter to refer Passenger instance */
                 1,                          /* Priority */
                 &task7handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vDataProcessingTask,  /* Task function implementation */
                 "Data processing",          /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&driver),           /* Passed parameter to refer Driver instance */
                 3,                          /* Priority */
                 &task10handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vDataProcessingTask,  /* Task function implementation */
                 "Data processing",          /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&passenger),        /* Passed parameter to refer Passenger instance */
                 3,                          /* Priority */
                 &task11handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vHeaterHandlerTask,   /* Task function implementation */
                 "Heating handler",          /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&driver),           /* Passed parameter to refer Driver instance */
                 2,                          /* Priority */
                 &task8handle                        /* Task handle to refer the Task */
    ) == pdFAIL);

    while(xTaskCreate( vHeaterHandlerTask,   /* Task function implementation */
                 "Heating handler",          /* Task name (Debugging purposes) */
                 256,                        /* Stack size of the task : 256 words >> 1024 bytes */
                 (void*)(&passenger),        /* Passed parameter to refer Passenger instance */
                 2,                          /* Priority */
                 &task9handle                        /* Task handle to refer the Task */
    ) == pdFAIL);


    vTaskSetApplicationTaskTag( task0handle, ( TaskHookFunction_t ) 1 );
    vTaskSetApplicationTaskTag( task1handle, ( TaskHookFunction_t ) 2 );
    vTaskSetApplicationTaskTag( task2handle, ( TaskHookFunction_t ) 3 );
    vTaskSetApplicationTaskTag( task3handle, ( TaskHookFunction_t ) 4 );
    vTaskSetApplicationTaskTag( task4handle, ( TaskHookFunction_t ) 5 );
    vTaskSetApplicationTaskTag( task5handle, ( TaskHookFunction_t ) 6 );
    vTaskSetApplicationTaskTag( task6handle, ( TaskHookFunction_t ) 7 );
    vTaskSetApplicationTaskTag( task7handle, ( TaskHookFunction_t ) 8 );
    vTaskSetApplicationTaskTag( task8handle, ( TaskHookFunction_t ) 9 );
    vTaskSetApplicationTaskTag( task9handle, ( TaskHookFunction_t ) 10 );
    vTaskSetApplicationTaskTag( task10handle, ( TaskHookFunction_t ) 11 );
    vTaskSetApplicationTaskTag( task11handle, ( TaskHookFunction_t ) 12 );


    /* This mutex for the mutual exclusion between Driver and passenger of ADC in any monitoring task */
    ADC_mutex = xSemaphoreCreateMutex();

    /* This mutex for the mutual exclusion between Driver and passenger of UART in any monitoring task */
    UART_mutex = xSemaphoreCreateMutex();

    /* The following two queues refer to the temperature measured by temperature sensor in both seats */
    Q_currentTempDriver = xQueueCreate(QUEUE_CURRENT_TEMP_SIZE,sizeof(uint8));
    Q_currentTempPassenger = xQueueCreate(QUEUE_CURRENT_TEMP_SIZE,sizeof(uint8));

    /* The following two queues refer to the temperature set by both driver and passenger by the push buttons */
    Q_desiredTempDriver = xQueueCreate(QUEUE_DESIRED_TEMP_SIZE,sizeof(uint8));
    Q_desiredTempPassenger = xQueueCreate(QUEUE_DESIRED_TEMP_SIZE,sizeof(uint8));

    /* Each of the following queue sets combine both the current and desired temperature (queue set for driver and other for passenger) */
    QS_DriverTemp = xQueueCreateSet(QUEUE_CURRENT_TEMP_SIZE+QUEUE_DESIRED_TEMP_SIZE);
    QS_PassengerTemp = xQueueCreateSet(QUEUE_CURRENT_TEMP_SIZE+QUEUE_DESIRED_TEMP_SIZE);

    /* Adding every previous queue into it's related queue set */
    xQueueAddToSet(Q_currentTempDriver, QS_DriverTemp);
    xQueueAddToSet(Q_desiredTempDriver, QS_DriverTemp);
    xQueueAddToSet(Q_currentTempPassenger, QS_PassengerTemp);
    xQueueAddToSet(Q_desiredTempPassenger, QS_PassengerTemp);

    /* Heater handler pass heating level of driver seat through this queue to be monitored */
    Q_heatingLevelDriver = xQueueCreate(QUEUE_HEATING_LEVEL_SIZE,sizeof(uint8));

    /* Heater handler pass heating level of passenger seat through this queue to be monitored */
    Q_heatingLevelPassenger = xQueueCreate(QUEUE_HEATING_LEVEL_SIZE,sizeof(uint8));

    /* Data processing task pass heating level of driver seat through this queue to be handled */
    Q_heatingModeDriver = xQueueCreate(QUEUE_HEATING_MODE_SIZE,sizeof(uint8));

    /* Data processing task pass heating level of passenger seat through this queue to be handled */
    Q_heatingModePassenger = xQueueCreate(QUEUE_HEATING_MODE_SIZE,sizeof(uint8));

    /* This event group has 3 used bits for the 3 push buttons, the ISR set them and button monitoring task wait for them to be set */
    PB_group = xEventGroupCreate();

    vTaskStartScheduler();

    /* Should never reach here!  If you do then there was not enough heap
    available for the idle task to be created. */

    while(1){}

}
