#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define configUSE_PREEMPTION 0
#define configUSE_TIME_SLICING 0
// #define configUSE_IDLE_HOOK 1


// void vApplicationIdleHook(void);

void func_1(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        printf("---------------|| %d \n", ++count);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void func_2(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        printf("-----|| %d\n", ++count);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
}

void func_3(void *pvParameter)
{
    int count = 0;
    while (1)
    {
        printf("--------|| %d \n", ++count);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
}

void app_main()
{
    xTaskCreate(&func_1,"task1",1024*5,NULL,2,NULL);
    xTaskCreate(&func_2,"task2",1024*5,NULL,1,NULL);
    xTaskCreate(&func_3,"task3",1024*5,NULL,1,NULL);

}