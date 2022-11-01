FreeRTOS da bir task oluşturmak için aşağıdaki fonksiyon kullanılır.

```c
    BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,
							              const char * const pcName,		
							              const configSTACK_DEPTH_TYPE usStackDepth,
							              void * const pvParameters,
							              UBaseType_t uxPriority,
							              TaskHandle_t * const pxCreatedTask )
                       
```                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
