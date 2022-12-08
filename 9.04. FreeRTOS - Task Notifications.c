#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* Private variables ---------------------------------------------------------*/
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
int notificationValue = 0;


/* Private function prototypes -----------------------------------------------*/
void Task1(void *argument);
void Task2(void *argument);


int main(void)
{
    while(1)
    {
        
    }
}


void Task1(void* argument)
{
    while(1)
    {
        xTaskNofityGive(myTask2Handle);
        vTaskDelay(1000);
    }
}


void Task2(void *argument)
{
    while(1)
    {
        notificationValue = ulTaskNotifyTake(pdTRUE, (TickType_t) portMAX_DELAY);
        if(notificationValue > 0)
        {
            printf("notification received: %d \r\n", notificationValue);
        }
    }
}
