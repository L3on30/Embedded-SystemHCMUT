#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BTN_NUM GPIO_NUM_27
#define STUDENT_ID 1915672

int counter = 0;
int status = 0;

void checkButton(void *pvParameter)
{

    for ( ; ; )
    {
        status = gpio_get_level(BTN_NUM);
        if (status == 0)     //deboucing
            counter++;
        else counter = 0;

        if (counter == 1)   
            printf("ESP32\n");   
        
        vTaskDelay (100 / portTICK_PERIOD_MS ) ;
    }
    vTaskDelete(NULL);
}

void printID(void *pvParameter)
{
    for ( ; ; )
    {
        printf("%d\n", STUDENT_ID);
        vTaskDelay (1000 / portTICK_PERIOD_MS ) ;
    }
    vTaskDelete(NULL);
}


void app_main()
{
    gpio_pad_select_gpio(BTN_NUM);
    gpio_set_direction(BTN_NUM,GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_NUM,GPIO_PULLUP_ONLY);
    xTaskCreate(&checkButton,"buttons",8000,NULL,0,NULL);
    xTaskCreate(&printID,"ID",8000,NULL,1,NULL);
}