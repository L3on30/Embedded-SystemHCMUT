#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

xQueueHandle Stored;
typedef struct
{
	int Id;
	int Data;
} Data_t;

void reception(void *pvParameter)
{
    Data_t requestPtr;
    uint32_t Data = 0;
    srand(time(0));
    while (1)
    {
        requestPtr.Id = (rand() % (3 - 1 + 1)) + 1;  
        requestPtr.Data = Data;
        Data++;
        xQueueSend(Stored, &requestPtr, portMAX_DELAY);
        printf("\n\n Add ID: %d , Data: %d into queue !!! \n\n", requestPtr.Id, requestPtr.Data);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void func_3(Data_t requestReceived)
{
    if (Stored == NULL){
        printf("func_3 is null\n");
        return;
    }
    else{
        if ((requestReceived.Id > 2)){
            printf("\n\n func_3 Ignore ID: %d , Data: %d !!! \n\n", requestReceived.Id, requestReceived.Data);
        }
    }
}

void func_2(Data_t requestReceived)
{
    if (Stored == NULL){
        printf("Stored is empty !!! \n");
        return;
    }
    else{
        if (requestReceived.Id == 2){
            printf("\n\n func_2 ID: %d , Data: %d !!! \n\n", requestReceived.Id, requestReceived.Data);
        } 
	else{
            printf("error func_2 !!! \n");
            func_3(requestReceived);
        }
    }
}

void func_1(void *pvParameter)
{
    if (Stored == NULL)
    {
        printf("Stored is empty !!! \n");
        return;
    }
    else
    {
        Data_t requestReceived;
        while (1)
        {
            if (xQueueReceive(Stored, &requestReceived, pdMS_TO_TICKS(1000)) == pdPASS)
            {
                if (requestReceived.Id == 1)
                {
                     printf("\n\n func_1 ID: %d , Data: %d !!! \n\n", requestReceived.Id, requestReceived.Data);
                }
                else
                {
                    printf("error func_1 !!! \n");
                    func_2(requestReceived);
                }
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}


void app_main()
{
    Stored = xQueueCreate(5, sizeof(Data_t));
    xTaskCreate(reception, "reception", 2048, NULL, 2, NULL);
    xTaskCreate(func_1, "function_1", 2048, NULL, 1, NULL);
}
