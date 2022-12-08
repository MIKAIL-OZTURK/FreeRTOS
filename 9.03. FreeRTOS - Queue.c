#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* Private variables ---------------------------------------------------------*/
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
QueueHandle_t myQueue = NULL;
char myTxBuff[30] = { 0 };
char myRxBuff[30] = { 0 };

/* Private function prototypes -----------------------------------------------*/
void Task1(void *argument);
void Task2(void *argument);

int main(void)
{
    while(1)
    {
        ;
    }
}


void Task1(void* arguemnt)
{
    myQueue = xQueueCreate(5, sizeof(myTxBuff));        // 5 is lenght of the queue

    sprintf(myTxBuff, "message 1");
    xQueueSend(myQueue, (void*)myTxBuff, (TickType_t) 0);
    sprintf(myTxBuff, "message 2");
    xQueueSend(myQueue, (void*)myTxBuff, (TickType_t) 0);
    sprintf(myTxBuff, "message 3");
    xQueueSend(myQueue, (void*)myTxBuff, (TickType_t) 0);

    printf("data waiting to be read: %d \r\n," uxQueueMessagesWaiting(myQueue));
    printf("available spaces: %d \r\n", uxQueueSpacesAvailable(myQueue));

    while(1)
    {

    }
}


void Task2(void *argument)
{
    while(1)
    {
        if(myQueue != 0)
        {
            if(xQueueReceive(myQueue, (void*)myRxBuff, (TickType_t)5))
            {
                printf("Data received: %s \r\n", myRxBuff);
            }
        }
    }
}