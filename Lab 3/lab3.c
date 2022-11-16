#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// #define configUSE_PREEMPTION 1       Espressif\frameworks\esp-idf-v4.4.2\components\freertos\include\freertos\FreeRTOS.h
// #define configUSE_TIME_SLICING 1     Espressif\frameworks\esp-idf-v4.4.2\components\freertos\include\esp_additions\freertos\FreeRTOSConfig.h

volatile uint32_t ulIdleCycleCount = 0UL;

volatile uint32_t ulIdleTask1Count = 0UL;       // PREEMPTION = 0
volatile uint32_t ulIdleTask2Count = 0UL;
volatile uint32_t ulIdleTask3Count = 0UL;
// =============================================

void vApplicationIdleHook( void )
{
        ulIdleCycleCount++;
}

void func_1(void *pvParameter)
{
    while (1)
    {
        if (configUSE_PREEMPTION == 0)
        {
            ulIdleTask1Count++;
            if (ulIdleTask1Count == 2)
            {
                xTaskCreatePinnedToCore(&func_2,"task2",1024*5,NULL,2,NULL,0);
            }
            else if (ulIdleTask1Count == 4)
            {
                xTaskCreatePinnedToCore(&func_3,"task3",1024*5,NULL,5,NULL,0);
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        else 
        {
            printf("==============|| %d \n", ulIdleTask2Count);
            printf("=======|| %d \n", ulIdleTask3Count);
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }
}

void func_2(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        if (configUSE_PREEMPTION == 0)
        {
            count++;
            printf("====> task 2 count: %d\n",count);
            if(count == 10)    
            {
                printf("====> task 2 end !!!\n");
                vTaskDelete(NULL);
            }
        }
        else if (configUSE_PREEMPTION == 1)
        {
            ulIdleTask2Count++;
        }
    }
}

void func_3(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        if (configUSE_PREEMPTION == 0)
        {
            count++;
            printf("==========> task 3 count: %d\n",count);
            if(count == 5)    
            {
                printf("==========> task 3 end !!!\n");
                vTaskDelete(NULL);
            }
        }
        else if (configUSE_PREEMPTION == 1)   
        {
            ulIdleTask3Count++;
        } 
    }
}

void app_main()
{
    printf("Preemption : %d \n",configUSE_PREEMPTION);
    printf("Time-slicing : %d \n\n",configUSE_TIME_SLICING);

    if (configUSE_PREEMPTION == 0)
    {
        xTaskCreate(&func_1,"task1",1024*5,NULL,0,NULL);
    }
    else
    {
        xTaskCreatePinnedToCore(&func_1,"task1",1024*5,NULL,2,NULL,1);
        xTaskCreatePinnedToCore(&func_2,"task2",1024*5,NULL,0,NULL,0);
        xTaskCreatePinnedToCore(&func_3,"task3",1024*5,NULL,0,NULL,0);
    }
}

