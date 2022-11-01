# FreeRTOS | API's          

### 1.Task Oluşturmak                    

FreeRTOS da bir task oluşturmak için aşağıdaki fonksiyon kullanılır.

```c
    BaseType_t xTaskCreate( 	TaskFunction_t pvTask	
    				const char * const pcName,		
		                const configSTACK_DEPTH_TYPE usStackDepth,	
			        void * const pvParameters,
				UBaseType_t uxPriority,
				TaskHandle_t * const pxCreatedTask )
```                       
- **pvTask**: Bu parametre Task için oluşturulmuş fonksiyonu temsil eder.
- **pcName**: String olarak bir task’a isim vermek için kullanılır. Bu parametre freertos tarafından kullanılmaz. Debug vb. olaylar için kullanılabilir.               
- **usStackDepth**: Task için ayrılacak bellek boyutu. Burada girilen parametre byte cinsinden değildir.?Örneğin 32 bitlik bir işlemci için  usStackDepth 100 girilirse 
stack olarak 100×4 byte=400 byte yer ayrılırır.                     
- **pvParameters**: Task fonksiyonuna bir parametre göndermek icin kullanılır. Burada parametre tipi void* olarak belirlenmiştir. Fonksiyona gönderilicek parametrenin 
tipinin kesin olmadığı(int ,float,char vb) zamanlarda void* ile parametre geçilir. Yani parametre olarak ister int ister float isterse string gönderilebilir.         
- **uxPriority**: Task önceliğini ifade eder. Öncelik için girilen sayı arttıkça öncelik de artar.                                 
- **pxCreatedTask**: Bir handle oluşturmak için kullanılır. Bu handle daha sonra task silmek,taskın önceliğini değiştirmek için kullanılabilir.                   

> Return Değeri: xTaskCreate() fonksiyonu iki farklı değer döndürür. Eğer task sorunsuz bir şekilde oluşturulduysa **pdPASS**, task oluşturmada sorun çıktıysa (bellek 
> ayırma ile ilgili) **pdFAIL** değerini döndürür.      


###### ÖRNEK
```c
void Task1(void *pvParammeters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void Task2(void *pvParameters)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

int main()
{
	xTaskCreate(Task1, "t1", 128, NULL, 0, NULL);
	xTaskCreate(Task2, "t2", 128, NULL, 0, NULL);
}
```


                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
