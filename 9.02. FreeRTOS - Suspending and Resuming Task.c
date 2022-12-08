#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"


/* Private variables ---------------------------------------------------------*/
TaskHandle_t myTask1Handle = NULL;
int count = 0;
int pass = 25;


/* Private function prototypes -----------------------------------------------*/
void Task1(void *argument);
void Task2(void *argument);


int main(void)
{
    /* Task1 is created -----------------------------------------------*/
    vTaskCreate(myTask1, "task1", 200, (void*)pass, tskIDLE_PRIORITY, &myTask1Handle);

    /* Task2 is created -----------------------------------------------*/
    vTaskCreate(myTask2, "task2", 200, (void*)pass, tskIDLE_PRIORITY, &myTask2Handle);
    vTaskStartScheduler();

    while(1)
    {
        ;
    }
}

/* Task1 ---------------------------------------------------------*/
void Task1(void *argument)
{
    while(1)
    {
        printf("Task1 is running..., %d",count++);
        vTaskDelay(1000 *(configTICK_RATE_HZ / 1000));  
        
        if(count == 30)
        {
            vTaskDelete(myTask1Handle); // Task1 is deleted
        }
    }
}

/* Task2 ---------------------------------------------------------*/
void Task2(void* argument)
{
    while(1)
    {
        vTaskDelay(5000 *(configTICK_RATE_HZ / 1000));      // Wait 5 second  
        vTaskSuspend(myTask1Handle);                        // Task1 is suspend
        vTaskDelay(1000 *(configTICK_RATE_HZ / 1000));      // Wait 5 second
        vTaskResume(myTask1Handle);                         // Task1 is resuming...
    }   
}
