#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include "hardware/gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define LED_PIN 25


// Prototipos de funciones
void hola_task1(void *pvParameters);
void hola_task2(void *pvParameters);

// Handlers necesarios
SemaphoreHandle_t mutex1;

void main()
{
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);


    // mutex1 = xSemaphoreCreateMutex();
    mutex1 = xSemaphoreCreateBinary();

    xTaskCreate(hola_task1, "Tarea 1", 256, NULL , 2, NULL);
    xTaskCreate(hola_task2, "Tarea 2", 256, NULL , 2, NULL);

    vTaskStartScheduler();


}

void hola_task1(void *pvParameters)
{

while (1)
{

    xSemaphoreTake(mutex1,25);
    printf("Tarea 1 dice Hola!\n");
    xSemaphoreGive(mutex1);
    // vTaskDelay(500);
}

}

void hola_task2(void *pvParameters)
{

while (1)
{

    xSemaphoreTake(mutex1,25);
    printf("Tarea 2 dice Hola!\n");
    vTaskDelay(50);
    xSemaphoreGive(mutex1);
}

}