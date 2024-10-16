/**********************************************************************************************************
 *
 * Module: Application
 *
 * File Name: APP.h
 *
 * Description: Header file contain the prototype of any task or function used in the application
 *
 * Author: Mario kaldas
 *
 **********************************************************************************************************/

#ifndef APP_APP_H_
#define APP_APP_H_


/****************************************************************************
 *                                  Includes
 * ************************************************************************/

/* FreeRTOS includes */

#include"FreeRTOS.h"
#include"task.h"
#include"semphr.h"
#include"queue.h"
#include"event_groups.h"


/* Application includes */

#include"HAL/LED.h"
#include"HAL/pushbutton.h"
#include"HAL/Temperature_sensor.h"

/* other includes */

#include"MCAL/UART0.h"
#include"MCAL/GPTM.h"
#include"MCAL/delay.h"

/***************************************************************************
 *                                Definitions
 *************************************************************************** */

#define QUEUE_CURRENT_TEMP_SIZE     5u
#define QUEUE_DESIRED_TEMP_SIZE     5u
#define QUEUE_HEATING_LEVEL_SIZE    5u
#define QUEUE_HEATING_MODE_SIZE     5u

#define EVENTGROUP_DRIVER_SEAT_BIT          (1ul<<0ul)
#define EVENTGROUP_DRIVER_WHEEL_BIT         (1ul<<1)
#define EVENTGROUP_PASSENGER_SEAT_BIT       (1ul<<2)

#define PB_INTERRUPT_PRIORITY       5

#define DRIVER                      0u
#define PASSENGER                   1u

#define RUNTIME_MEASUREMENTS_TASK_PERIODICITY   5000

/***************************************************************************
 *                             Types declaration
 *************************************************************************** */

typedef struct{

    /* If instance = 0 then it's driver, if instance = 1 then it's passenger  */
    uint8 instance;

    const uint8* name;
}info;

typedef enum{

    HEATER_OFF,
    HEATER_LOW,
    HEATER_MEDIUM,
    HEATER_HIGH,
    TEMPERATURE_SENSOR_FAILURE

}heatingMode_Type;

typedef enum{

    LEVEL0=HEATER_OFF,
    LEVEL1=25,
    LEVEL2=30,
    LEVEL3=35

}desiredTemp_Type;

/****************************************************************************
 *                              Global variables
 * ************************************************************************/

/* This mutex for the mutual exclusion between Driver and passenger of ADC in any monitoring task */
extern SemaphoreHandle_t ADC_mutex;

/* This mutex for the mutual exclusion between Driver and passenger of UART in any monitoring task */
extern SemaphoreHandle_t UART_mutex;

/* The following two queues refer to the temperature set by both driver and passenger by the push buttons */
extern QueueHandle_t     Q_desiredTempDriver;
extern QueueHandle_t     Q_desiredTempPassenger;

/* The following two queues refer to the temperature measured by temperature sensor in both seats */
extern QueueHandle_t     Q_currentTempDriver;
extern QueueHandle_t     Q_currentTempPassenger;

/* Each of the following queue sets combine both the current and desired temperature (queue set for driver and other for passenger) */
extern QueueSetHandle_t QS_DriverTemp;
extern QueueSetHandle_t QS_PassengerTemp;

/* Heater handler pass heating level of driver seat through this queue to be monitored */
extern QueueHandle_t     Q_heatingLevelDriver;

/* Data processing task pass heating level of driver seat through this queue to be handled */
extern QueueHandle_t     Q_heatingModeDriver;

/* Heater handler pass heating level of passenger seat through this queue to be monitored */
extern QueueHandle_t     Q_heatingLevelPassenger;

/* Data processing task pass heating level of passenger seat through this queue to be handled */
extern QueueHandle_t     Q_heatingModePassenger;

/* This event group has 3 used bits for the 3 push buttons, the ISR set them and button monitoring task wait for them to be set */
extern EventGroupHandle_t PB_group;

/* These structures contain the type of the seat (Driver or Passenger) and instance number to be used in the task (0>driver, 1>passenger) */
extern info driver;
extern info passenger;

/******************************************************************************/
/* RTOS Runtime Measurements. *************************************************/
/******************************************************************************/

extern uint32 ullTasksOutTime[13];
extern uint32 ullTasksInTime[13];
extern uint32 ullTasksTotalTime[13];

TaskHandle_t task0handle;   /* RunTime measurements task */
TaskHandle_t task1handle;   /* vInitialValuesTask */
TaskHandle_t task2handle;   /* vTemperatureMonitoringTask for driver */
TaskHandle_t task3handle;   /* vTemperatureMonitoringTask for passenger */
TaskHandle_t task4handle;   /* vButtonMonitoringTask for driver */
TaskHandle_t task5handle;   /* vButtonMonitoringTask for passenger */
TaskHandle_t task6handle;   /* vHeatingLevelMonitoringTask for driver */
TaskHandle_t task7handle;   /* vHeatingLevelMonitoringTask for passenger */
TaskHandle_t task8handle;   /* vHeaterHandlerTask for driver */
TaskHandle_t task9handle;   /* vHeaterHandlerTask for passenger */
TaskHandle_t task10handle;  /* vDataProcessingTask for driver */
TaskHandle_t task11handle;  /* vDataProcessingTask for passenger */

/****************************************************************************
 *                              Hooks prototype
 * ************************************************************************/

/* Stack overflow hook */
void vApplicationStackOverflowHook( TaskHandle_t xTask,char *pcTaskName );

/* Heap overflow hook */
void vApplicationMallocFailedHook( void );

/****************************************************************************
 *                             Functions prototype
 * ************************************************************************/

/* Initialize all hardware components */
void vSetupHardware( void );

/****************************************************************************
 *                               Tasks prototype
 * ************************************************************************/

/* This task just display initial values of both temperature sensors and the initial state of the heater(off) and then deletes itself*/
void vInitialValuesTask( void * pvParameters );

/* Monitoring the current temperature read from both temperature sensors and pass these temperatures to handler task through queue*/
void vTemperatureMonitoringTask( void * pvParameters );

/* Monitoring the desired temperature read from both push buttons and pass these temperatures to handler task through queue*/
void vButtonMonitoringTask( void * pvParameters );

/* Monitor the state of the heater which is decided by the handler task */
void vHeatingLevelMonitoringTask( void * pvParameters );

/* This task receives the desired and current temperature and process them to decide the intensity level of the heater
 * then pass it to the handler task and also to the heating level monitoring task to be monitored */
void vDataProcessingTask( void * pvParameters );

/* Handler task which receive the intensity level of the heater which been decided by the DataProcessing task*/
void vHeaterHandlerTask( void * pvParameters );



/* Runtime measurements */
void vRunTimeMeasurementsTask(void *pvParameters);




#endif /* APP_APP_H_ */
