/**********************************************************************************************************
 *
 * Module: Application
 *
 * File Name: APP.c
 *
 * Description: source file contain the implementation of any task or function used in the application
 *
 * Author: Mario kaldas
 *
 **********************************************************************************************************/

#include"APP.h"

/****************************************************************************
 *                              Global variables
 * ************************************************************************/

/* This mutex for the mutual exclusion between Driver and passenger of ADC in any monitoring task */
SemaphoreHandle_t ADC_mutex;

/* This mutex for the mutual exclusion between Driver and passenger of UART in any monitoring task */
SemaphoreHandle_t UART_mutex;

/* The following two queues refer to the temperature set by both driver and passenger by the push buttons */
QueueHandle_t     Q_desiredTempDriver;
QueueHandle_t     Q_desiredTempPassenger;

/* The following two queues refer to the temperature measured by temperature sensor in both seats */
QueueHandle_t     Q_currentTempDriver;
QueueHandle_t     Q_currentTempPassenger;

/* Each of the following queue sets combine both the current and desired temperature (queue set for driver and other for passenger) */
QueueSetHandle_t QS_DriverTemp;
QueueSetHandle_t QS_PassengerTemp;

/* Heater handler pass heating level of driver seat through this queue to be monitored */
QueueHandle_t     Q_heatingLevelDriver;

/* Data processing task pass heating level of driver seat through this queue to be handled */
QueueHandle_t     Q_heatingModeDriver;

/* Heater handler pass heating level of passenger seat through this queue to be monitored */
QueueHandle_t     Q_heatingLevelPassenger;

/* Data processing task pass heating level of passenger seat through this queue to be handled */
QueueHandle_t     Q_heatingModePassenger;

/* This event group has 3 used bits for the 3 push buttons, the ISR set them and button monitoring task wait for them to be set */
EventGroupHandle_t PB_group;

/* These structures contain the type of the seat (Driver or Passenger) and instance number to be used in the task */
info driver = {0,"Driver"};
info passenger = {1,"Passenger"};

/******************************************************************************/
/* RTOS Runtime Measurements. *************************************************/
/******************************************************************************/

uint32 ullTasksOutTime[13];
uint32 ullTasksInTime[13];
uint32 ullTasksTotalTime[13];

/****************************************************************************
 *                             Hooks implementation
 * ************************************************************************/

/* Heap overflow hook */
void vApplicationMallocFailedHook( void ){

    while(1){}
}

/* Stack overflow hook */
void vApplicationStackOverflowHook( TaskHandle_t xTask,char *pcTaskName ){

    while(1){}
}

/****************************************************************************
 *                        Interrupt service routine (ISRs)
 * ************************************************************************/

void ISR_PORTFhandler(void){

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(GPIO_PORTF_GPIORIS_R & (1<<PB_DRIVER_CONTROL)){

        xEventGroupSetBitsFromISR(PB_group, EVENTGROUP_DRIVER_SEAT_BIT,&xHigherPriorityTaskWoken);
        GPIO_PORTF_GPIOICR_R |= (1<<PB_DRIVER_CONTROL);
    }
    else if(GPIO_PORTF_GPIORIS_R & (1<<PB_PASSENGER_CONTROL)){

        xEventGroupSetBitsFromISR(PB_group, EVENTGROUP_PASSENGER_SEAT_BIT,&xHigherPriorityTaskWoken);
        GPIO_PORTF_GPIOICR_R |= (1<<PB_PASSENGER_CONTROL);
    }

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


void ISR_PORTBhandler(void){

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(GPIO_PORTB_GPIORIS_R & (1<<(PB_DRIVER_MULTI_FN % (NUM_OF_PINS_PER_PORT-1))) ){

        xEventGroupSetBitsFromISR(PB_group, EVENTGROUP_DRIVER_WHEEL_BIT,&xHigherPriorityTaskWoken);
        GPIO_PORTB_GPIOICR_R |= (1<<(PB_DRIVER_MULTI_FN % (NUM_OF_PINS_PER_PORT-1)));
    }

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


/****************************************************************************
 *                             Functions definition
 * ************************************************************************/

void vSetupHardware( void )
{
    /* Initialize all hardware components LEDs, Push buttons and Temperature sensor in addition to UART for monitoring
     * and General Purpose Timer for runtime
     *  */

    LED_init(LED_DRIVER_RED);
    LED_init(LED_DRIVER_GREEN);
    LED_init(LED_DRIVER_BLUE);
    LED_init(LED_PASSENGER_RED);
    LED_init(LED_PASSENGER_GREEN);
    LED_init(LED_PASSENGER_BLUE);

    PB_init(PB_DRIVER_CONTROL);
    PB_init(PB_DRIVER_MULTI_FN);
    PB_init(PB_PASSENGER_CONTROL);
    PB_initEdgeTriggered(PB_DRIVER_CONTROL,PB_INTERRUPT_PRIORITY);
    PB_initEdgeTriggered(PB_DRIVER_MULTI_FN,PB_INTERRUPT_PRIORITY);
    PB_initEdgeTriggered(PB_PASSENGER_CONTROL,PB_INTERRUPT_PRIORITY);

    TEMPSENSOR_init();

    UART0_Init();
    GPTM_WTimer0Init();
}


/****************************************************************************
 *                               Tasks definition
 * ************************************************************************/

/* This task just display initial values of both temperature sensors and the initial state of the heater(off) and then deletes itself*/
void vInitialValuesTask( void * pvParameters ){

    uint8 initialTemperature;

    xSemaphoreTake(ADC_mutex,portMAX_DELAY);
    xSemaphoreTake(UART_mutex,portMAX_DELAY);
    initialTemperature = TEMPSENSOR_getTemperature(TEMPERATURE_DRIVER);

    UART0_SendString("Initial temperature of ");
    UART0_SendString("Driver");
    UART0_SendString(" seat is : ");
    UART0_SendInteger(initialTemperature);
    UART0_SendString(" degree celsius\r\n");

    initialTemperature = TEMPSENSOR_getTemperature(TEMPERATURE_PASSENGER);

    xSemaphoreGive(ADC_mutex);


    UART0_SendString("Initial temperature of ");
    UART0_SendString("Passenger");
    UART0_SendString(" seat is : ");
    UART0_SendInteger(initialTemperature);
    UART0_SendString(" degree celsius\r\n");

    UART0_SendString("Current mode of ");
    UART0_SendString("Driver");
    UART0_SendString(" seat heater is : ");
    UART0_SendString("OFF");
    UART0_SendString("\r\n");

    UART0_SendString("Current mode of ");
    UART0_SendString("Passenger");
    UART0_SendString(" seat heater is : ");
    UART0_SendString("OFF");
    UART0_SendString("\r\n");

    xSemaphoreGive(UART_mutex);

    vTaskDelete(NULL);

    /* Processor will never reach this line */
    for(;;);
}

/* Monitoring the current temperature read from both temperature sensors and pass these temperatures to DataProcessing task through queue*/
void vTemperatureMonitoringTask( void * pvParameters ){

    /*
     * The previousTemp and currentTemp are made to control which temperature to be monitored on the terminal,
     * as no temperature will be monitored unless there is a change in the temperature at least 2 degrees
     * (prevent too much data on the terminal)
     */
    uint8 currentTemp;
    uint8 previousTemp;

    /* Send the initial temperature to DataProcessing task just in case these initial values need to be processed
     * and decide the heater intensity level according to initial temperature
     */
    previousTemp = TEMPSENSOR_getTemperature(((info*)pvParameters)->instance);

    if(((info*)pvParameters)->instance == DRIVER){

        xQueueSend(Q_currentTempDriver,(void*)(&previousTemp),portMAX_DELAY);
    }
    else if(((info*)pvParameters)->instance == PASSENGER){

        xQueueSend(Q_currentTempPassenger,(void*)(&previousTemp),portMAX_DELAY);
    }

    while(1){

        /* Reduce CPU load */
        vTaskDelay(pdMS_TO_TICKS(500));

        /* Acquire the ADC resource as there is 6 tasks trying to access the same resource by time slicing.  */
        xSemaphoreTake(ADC_mutex,portMAX_DELAY);

        /* As this function shared between two tasks (with different stacks so currentTemp variable not the same),
         * we must guarantee that every task access the right channel for temperature sensor.
         */
        if(((info*)pvParameters)->instance == DRIVER){

            /* Check the temperature sensor in the driver seat */
            currentTemp = TEMPSENSOR_getTemperature(TEMPERATURE_DRIVER);
        }
        else if(((info*)pvParameters)->instance == PASSENGER){

            /* Check the temperature sensor in the passenger seat */
            currentTemp = TEMPSENSOR_getTemperature(TEMPERATURE_PASSENGER);
        }

        /* Release ADC resource */
        xSemaphoreGive(ADC_mutex);


        /* If there is at least 2 degrees changed then print the current temperature on terminal and send it to DataProcessing task */
        if((currentTemp - previousTemp) >= 2 | (previousTemp - currentTemp) >= 2){

            if(((info*)pvParameters)->instance == DRIVER){

                xQueueSend(Q_currentTempDriver,(void*)(&currentTemp),portMAX_DELAY);
            }
            else if(((info*)pvParameters)->instance == PASSENGER){

                xQueueSend(Q_currentTempPassenger,(void*)(&currentTemp),portMAX_DELAY);
            }

            /* Acquire the UART resource as there is 6 tasks trying to access the same resource by time slicing.  */
            xSemaphoreTake(UART_mutex,portMAX_DELAY);

            UART0_SendString("Current temperature of ");
            UART0_SendString(((info*)pvParameters)->name);
            UART0_SendString(" seat is : ");
            UART0_SendInteger(currentTemp);
            UART0_SendString(" degree celsius\r\n");
            previousTemp = currentTemp;

            /* Release UART resource */
            xSemaphoreGive(UART_mutex);

        }

    }
}

/* Monitoring the desired temperature read from both push buttons and pass these temperatures to handler task through queue*/
void vButtonMonitoringTask( void * pvParameters ){

    /* This is a state counter to loop between the states of desired temperature */
    heatingMode_Type desiredLevel = HEATER_OFF;

    /* This flag indicates if there is a change in the desired temperature to monitor the new state
     * (prevent too much data on the terminal)
     */
    uint8 flag = 0;

    const EventBits_t BitsToWaitFor = ( EVENTGROUP_DRIVER_SEAT_BIT | EVENTGROUP_DRIVER_WHEEL_BIT | EVENTGROUP_PASSENGER_SEAT_BIT);

    EventBits_t PB_group_value;

    while(1){



        /* As this function shared between two tasks (with different stacks so desiredLevel and flag variables not the same),
         * we must guarantee that every task access the right channel for the push button.
         */
        if(((info*)pvParameters)->instance == DRIVER){

            PB_group_value = xEventGroupWaitBits(PB_group,      /* Event group responsible for the three push buttons */
                                                 BitsToWaitFor,       /* The three bits to check on */
                                                 pdTRUE,              /* Clear events on exit */
                                                 pdFALSE,             /* If any of push buttons are pressed get ready */
                                                 portMAX_DELAY);       /* Max delay to stay in blocked state */

            /* Check on the push button of the driver seat and the push button on the driving wheel */
            if((PB_group_value & EVENTGROUP_DRIVER_SEAT_BIT) | (PB_group_value & EVENTGROUP_DRIVER_WHEEL_BIT)){

                /* Go to next state */
                desiredLevel++;

                vTaskDelay(pdMS_TO_TICKS(50));

                /* If the last state reached then go to first state again */
                if(desiredLevel == (HEATER_HIGH + 1)){
                    desiredLevel = HEATER_OFF;
                }

                /* Send the new state to DataProcessing task */
                xQueueSend(Q_desiredTempDriver,(void*)(&desiredLevel),portMAX_DELAY);

                flag = 1;

            }
        }

        else if(((info*)pvParameters)->instance == PASSENGER){

            PB_group_value = xEventGroupWaitBits(PB_group,      /* Event group responsible for the three push buttons */
                                                 BitsToWaitFor,       /* The three bits to check on */
                                                 pdTRUE,              /* Clear events on exit */
                                                 pdFALSE,             /* If any of push buttons are pressed get ready */
                                                 portMAX_DELAY);       /* Max delay to stay in blocked state */

            /* Check on the push button of the passenger seat */
            if(PB_group_value & EVENTGROUP_PASSENGER_SEAT_BIT){

                /* Go to next state */
                desiredLevel++;

                vTaskDelay(pdMS_TO_TICKS(50));


                /* If the last state reached then go to first state again */
                if(desiredLevel == (HEATER_HIGH + 1)){
                    desiredLevel = HEATER_OFF;
                }

                /* Send the new state to DataProcessing task */
                xQueueSend(Q_desiredTempPassenger,(void*)(&desiredLevel),portMAX_DELAY);

                flag = 1;
            }

        }



        if(flag == 1){

            /* Acquire the UART resource as there is 6 tasks trying to access the same resource by time slicing.  */
            xSemaphoreTake(UART_mutex,portMAX_DELAY);

            UART0_SendString("Desired temperature of ");
            UART0_SendString(((info*)pvParameters)->name);
            UART0_SendString(" seat heater is : ");

            switch(desiredLevel){

            case HEATER_OFF:
                UART0_SendString("OFF");
                break;

            case HEATER_LOW:
                UART0_SendString("25 degree celsius");
                break;

            case HEATER_MEDIUM:
                UART0_SendString("30 degree celsius");
                break;

            case HEATER_HIGH:
                UART0_SendString("35 degree celsius");
                break;
            }
            UART0_SendString("\r\n");

            /* Release UART resource */
            xSemaphoreGive(UART_mutex);

            flag = 0;

        }

    }
}

/* Monitor the state of the heater which is decided by the handler task */
void vHeatingLevelMonitoringTask( void * pvParameters ){

    /*
     * The previousHeatingLevel and currentHeatingLevel are made to control which heating level to be monitored on the terminal,
     * as no temperature will be monitored unless there is a change in the heating level
     * (prevent too much data on the terminal)
     */
    heatingMode_Type previousHeatingLevel = HEATER_OFF;
    heatingMode_Type currentHeatingLevel;

    while(1){

        /* As this function shared between two tasks
         * (with different stacks so currentHeatingLevel and desiredHeatingLevel variables not the same),
         * we must guarantee that every task access the right queue.
         */
        if(((info*)pvParameters)->instance == DRIVER){

            xQueueReceive(Q_heatingLevelDriver,&currentHeatingLevel , portMAX_DELAY);
        }

        else if(((info*)pvParameters)->instance == PASSENGER){

            xQueueReceive(Q_heatingLevelPassenger,&currentHeatingLevel , portMAX_DELAY);
        }

        /* If there is a change in the heating level monitor it (prevent too much data to be monitored) */
        if(currentHeatingLevel != previousHeatingLevel){

            /* Acquire the UART resource as there is 6 tasks trying to access the same resource by time slicing.  */
            xSemaphoreTake(UART_mutex,portMAX_DELAY);

            UART0_SendString("Heater of the ");
            UART0_SendString(((info*)pvParameters)->name);
            UART0_SendString(" seat is ");


            switch(currentHeatingLevel){

            case HEATER_OFF:

                UART0_SendString("OFF\r\n");
                break;

            case HEATER_LOW:

                UART0_SendString("on LOW intensity\r\n");
                break;

            case HEATER_MEDIUM:

                UART0_SendString("on MEDIUM intensity\r\n");
                break;

            case HEATER_HIGH:

                UART0_SendString("on HIGH intensity\r\n");
                break;
            }

            /* Release UART resource */
            xSemaphoreGive(UART_mutex);

            previousHeatingLevel = currentHeatingLevel;
        }
    }

}



/* This task receives the desired and current temperature and process them to decide the intensity level of the heater
 * then pass it to the handler task and also to the heating level monitoring task to be monitored */
void vDataProcessingTask( void * pvParameters ){

    /* This variable used to convert the desired temperature from a state (0,1,2,3) to actual temperature (off,25,30,35) */
    heatingMode_Type desiredLevel;

    /* The following two variables will receive the current or desired temperature from according queue */
    desiredTemp_Type desiredTemperature;
    uint8 currentTemperature;

    /* This variable will receive the handle of one of both queues (current temperature or desired temperature)
     * to know which temperature is changed
     */
    QueueHandle_t modeOrTemp;

    /* The last decision of the heater intensity level will be places here and sent to the handler task */
    heatingMode_Type Mode=HEATER_OFF;

    while(1){

        /* Check which task accessing this function (driver of passenger) */
        if(((info*)pvParameters)->instance == DRIVER){


            /* The task will be blocked until desired temperature or current temperature change, every temperature is passed
             * through their according queue, notice that both queues (current temperature and desired temperature) are in same queue set,
             * so we must check which temperature is changed (desired or current)
             *  */
            modeOrTemp = xQueueSelectFromSet(QS_DriverTemp, portMAX_DELAY);

            if(modeOrTemp == Q_currentTempDriver){

                xQueueReceive(Q_currentTempDriver, &currentTemperature , portMAX_DELAY);
            }
            else if(modeOrTemp == Q_desiredTempDriver){

                xQueueReceive(Q_desiredTempDriver, &desiredLevel , portMAX_DELAY);
            }

        }
        else if (((info*)pvParameters)->instance == PASSENGER){

            modeOrTemp = xQueueSelectFromSet(QS_PassengerTemp, portMAX_DELAY);

            if(modeOrTemp == Q_currentTempPassenger){

                xQueueReceive(Q_currentTempPassenger, &currentTemperature , portMAX_DELAY);
            }
            else if(modeOrTemp == Q_desiredTempPassenger){

                xQueueReceive(Q_desiredTempPassenger, &desiredLevel , portMAX_DELAY);
            }
        }

        /* Put the actual temperature in the desired level variable not just a state */
        switch(desiredLevel){

        case HEATER_OFF:

            /* Off */
            desiredTemperature = LEVEL0;
            break;

        case HEATER_LOW:

            /* 25 degree celsius */
            desiredTemperature = LEVEL1;
            break;

        case HEATER_MEDIUM:

            /* 30 degree celsius */
            desiredTemperature = LEVEL2;
            break;

        case HEATER_HIGH:

            /* 35 degree celsius */
            desiredTemperature = LEVEL3;
            break;
        }


        /* If the current temperature in this range then the temperature sensor is failed so turn off heater and turn on red LED */
        if((currentTemperature > 40) || (currentTemperature < 5)){

            Mode = TEMPERATURE_SENSOR_FAILURE;
        }

        /* If difference between desired temperature and current temperature 10 or greater then turn on heater on high intensity */
        else if((desiredTemperature - currentTemperature) >= 10){

            Mode = HEATER_HIGH;
        }

        /* If difference between desired temperature and current temperature 5 or greater then turn on heater on medium intensity */
        else if((desiredTemperature - currentTemperature) >= 5){

            Mode = HEATER_MEDIUM;
        }

        /* If difference between desired temperature and current temperature 2 or greater then turn on heater on low intensity */
        else if((desiredTemperature - currentTemperature) >= 2){

            Mode = HEATER_LOW;
        }

        /* If difference between desired temperature and current temperature less than 2 then turn off heater */
        else{

            Mode = HEATER_OFF;
        }

        if(((info*)pvParameters)->instance == DRIVER){

            /* Send the decided mode to the handler task to handle heater */
            xQueueSend(Q_heatingModeDriver,&Mode,portMAX_DELAY);

            /* Send the decided mode to the heater monitoring task to monitor the heater intensity level */
            xQueueSend(Q_heatingLevelDriver,&Mode,portMAX_DELAY);
        }
        else if(((info*)pvParameters)->instance == PASSENGER){

            xQueueSend(Q_heatingModePassenger,&Mode,portMAX_DELAY);
            xQueueSend(Q_heatingLevelPassenger,&Mode,portMAX_DELAY);
        }
    }
}


/* Handler task which receive the intensity level of the heater which been decided by the DataProcessing task*/
void vHeaterHandlerTask( void * pvParameters ){

    /* This is the variable in which the task will receive the heater intensity level from Data processing task */
    heatingMode_Type Mode=HEATER_OFF;


    while(1){

        /* As this function shared between two tasks (with different stacks so Mode variable not the same),
         * we must guarantee that every task access the right heater.
         */
        if(((info*)pvParameters)->instance == DRIVER){

            xQueueReceive(Q_heatingModeDriver, &Mode, portMAX_DELAY);
        }
        else if(((info*)pvParameters)->instance == PASSENGER){

            xQueueReceive(Q_heatingModePassenger, &Mode, portMAX_DELAY);
        }

        /* Handle the heater according to the received mode from DataProcessing task */
        switch(Mode){

        case HEATER_OFF:

            /* As this function shared between two tasks,
             * we must guarantee that every task access the right heater.
             */
            if(((info*)pvParameters)->instance == DRIVER){

                LED_set(LED_DRIVER_RED, LED_OFF);
                LED_set(LED_DRIVER_GREEN, LED_OFF);
                LED_set(LED_DRIVER_BLUE, LED_OFF);
            }
            else if(((info*)pvParameters)->instance == PASSENGER){

                LED_set(LED_PASSENGER_RED, LED_OFF);
                LED_set(LED_PASSENGER_GREEN, LED_OFF);
                LED_set(LED_PASSENGER_BLUE, LED_OFF);
            }

            break;

        case HEATER_LOW:

            if(((info*)pvParameters)->instance == DRIVER){

                LED_set(LED_DRIVER_RED, LED_OFF);
                LED_set(LED_DRIVER_GREEN, LED_ON);
                LED_set(LED_DRIVER_BLUE, LED_OFF);
            }
            else if(((info*)pvParameters)->instance == PASSENGER){

                LED_set(LED_PASSENGER_RED, LED_OFF);
                LED_set(LED_PASSENGER_GREEN, LED_ON);
                LED_set(LED_PASSENGER_BLUE, LED_OFF);
            }

            break;

        case HEATER_MEDIUM:

            if(((info*)pvParameters)->instance == DRIVER){

                LED_set(LED_DRIVER_RED, LED_OFF);
                LED_set(LED_DRIVER_GREEN, LED_OFF);
                LED_set(LED_DRIVER_BLUE, LED_ON);
            }
            else if(((info*)pvParameters)->instance == PASSENGER){

                LED_set(LED_PASSENGER_RED, LED_OFF);
                LED_set(LED_PASSENGER_GREEN, LED_OFF);
                LED_set(LED_PASSENGER_BLUE, LED_ON);
            }

            break;

        case HEATER_HIGH:

            if(((info*)pvParameters)->instance == DRIVER){

                LED_set(LED_DRIVER_RED, LED_OFF);
                LED_set(LED_DRIVER_GREEN, LED_ON);
                LED_set(LED_DRIVER_BLUE, LED_ON);
            }
            else if(((info*)pvParameters)->instance == PASSENGER){

                LED_set(LED_PASSENGER_RED, LED_OFF);
                LED_set(LED_PASSENGER_GREEN, LED_ON);
                LED_set(LED_PASSENGER_BLUE, LED_ON);
            }

            break;

            /* Heater off and turn on the red LED */
        case TEMPERATURE_SENSOR_FAILURE:

            if(((info*)pvParameters)->instance == DRIVER){

                LED_set(LED_DRIVER_RED, LED_ON);
                LED_set(LED_DRIVER_GREEN, LED_OFF);
                LED_set(LED_DRIVER_BLUE, LED_OFF);
            }
            else if(((info*)pvParameters)->instance == PASSENGER){

                LED_set(LED_PASSENGER_RED, LED_ON);
                LED_set(LED_PASSENGER_GREEN, LED_OFF);
                LED_set(LED_PASSENGER_BLUE, LED_OFF);
            }

            break;
        }
    }
}



/* Runtime measurements */
void vRunTimeMeasurementsTask(void *pvParameters){

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        uint8 ucCounter, ucCPU_Load;
        uint32 ullTotalTasksTime = 0;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(RUNTIME_MEASUREMENTS_TASK_PERIODICITY));
        for(ucCounter = 1; ucCounter < 13; ucCounter++)
        {
            ullTotalTasksTime += ullTasksTotalTime[ucCounter];
        }
        ucCPU_Load = (ullTotalTasksTime * 100) /  GPTM_WTimer0Read();

        taskENTER_CRITICAL();
        UART0_SendString("CPU Load is ");
        UART0_SendInteger(ucCPU_Load);
        UART0_SendString("% \r\n");
        taskEXIT_CRITICAL();
    }
}
