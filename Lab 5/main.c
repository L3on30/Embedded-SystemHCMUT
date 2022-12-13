// #include <stdio.h>
// #include <time.h>
// #include <string.h>
// #include <stdlib.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/queue.h"
// #include "freertos/queue.h"
// #include "freertos/timers.h"

// int cnt = 0;
// int cnt_0 = 0;
// int cnt_1 = 0;

// void func_CallBack(TimerHandle_t xTimer)
// {
//    const char *str;
//    str = pcTimerGetTimerName(xTimer);   
   

//    int Timer_ID = (int) pvTimerGetTimerID(xTimer);

//    if (Timer_ID == 0)
//    {
//       printf("Count: %d       ",++cnt);
//    }

//    if (Timer_ID == 1)
//    {
//       printf("%s _ %d\n",str,++cnt_0);
//       if (cnt_0 == 10)
//       {
//          xTimerStop(xTimer, 0);
//          printf("Timer 1 stopped\n");
//       }
//    }
//    if (Timer_ID == 2)
//    {
//       printf("==========|| %s _ %d\n",str,++cnt_1);
//       if (cnt_1 == 5)
//       {
//          xTimerStop(xTimer, 0);
//          printf("==========|| Timer 2 stopped\n");

//       }
//    }
//    printf("\n");
// }

// void app_main()
// {
//    TaskHandle_t Timer_1 = xTimerCreate("ahihi", pdMS_TO_TICKS(2000),pdTRUE,(void *) 1 , func_CallBack);
//    TaskHandle_t Timer_2 = xTimerCreate("ihaha", pdMS_TO_TICKS(3000),pdTRUE,(void *) 2 , func_CallBack);
//    TaskHandle_t Timer_3 = xTimerCreate("Count", pdMS_TO_TICKS(1000),pdTRUE,(void *) 0 , func_CallBack);

//    xTimerStart(Timer_1, 0);
//    xTimerStart(Timer_2, 0);
//    xTimerStart(Timer_3, 0);

// }

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "FreeRTOSConfig.h"

uint8_t counter_timer_1 = 0;
uint8_t counter_timer_2 = 0;
uint8_t counter_time = 1;
void timer_Callback(TimerHandle_t xTimer)
{
  const uint8_t* timer_id = pvTimerGetTimerID(xTimer);
  if(timer_id == 0) 
  {

  }

  if(timer_id == 1)
  {
    printf("ahihi count %d times \r\n",  ++counter_timer_1);
    // counter_timer_1++;
    if(counter_timer_1 == 10) {
      printf("ahihi stop \r\n");
      xTimerStop(xTimer, 0);
    } 
  }
  if(timer_id == 2)
  {
    printf("ihaha count %d times \r\n", ++counter_timer_2);
    // counter_timer_2++;
    if(counter_timer_2 == 5) {
      printf("ihaha stop \r\n");
      xTimerStop(xTimer, 0);
    } 
  }
}

void timer_CountTime()
{
    counter_time++;
    if (counter_time <= 20)
        printf("TimeStamp: %d \n", counter_time);
}

void app_main()
{
    TimerHandle_t xTimer_temp = xTimerCreate("Timer temp", pdMS_TO_TICKS(1000), pdTRUE, 0, timer_CountTime);
    TimerHandle_t xTimer_1 = xTimerCreate("Timer 1", pdMS_TO_TICKS(2000), pdTRUE, 1, timer_Callback);
    TimerHandle_t xTimer_2 = xTimerCreate("Timer 2", pdMS_TO_TICKS(3000), pdTRUE, 2, timer_Callback);
        
        printf("TimeStamp: %d \n", counter_time);
        printf("Start timer !!!\r\n");
        xTimerStart(xTimer_temp, 0);
        xTimerStart(xTimer_1, 0);
        xTimerStart(xTimer_2, 0);


}