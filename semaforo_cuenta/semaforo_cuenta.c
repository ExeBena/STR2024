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
SemaphoreHandle_t cuenta;

void main()
{
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);


    cuenta = xSemaphoreCreateCounting(5,0);

    xTaskCreate(hola_task1, "Tarea 1", 256, NULL , 2, NULL);
    xTaskCreate(hola_task2, "Tarea 2", 256, NULL , 2, NULL);

    vTaskStartScheduler();


}

void hola_task1(void *pvParameters)
{

while (1)
{

    xSemaphoreTake(cuenta,25);
    printf("Tarea 1 dice Hola!\n");
    
    // vTaskDelay(100);
}

}

void hola_task2(void *pvParameters)
{

while (1)
{

    
    printf("Tarea 2 dice Hola!\n");
    xSemaphoreGive(cuenta);
    // vTaskDelay(100);
}

}