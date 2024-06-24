#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include "hardware/gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


QueueHandle_t cola;

void transmisor(void *pvParameters);
void receptor(void *pvParameters);

void main()
{

    stdio_init_all();

    printf("Iniciando...");


    cola = xQueueCreate(5,sizeof(uint32_t));

    xTaskCreate(transmisor,"transmisor", 256, NULL, 1, NULL);
    xTaskCreate(receptor,"receptor", 256, NULL, 1, NULL);

    vTaskStartScheduler();


}

void transmisor(void *pvParameters)
{
    uint32_t contador = 0;

    while(true)
    {
        xQueueSend(cola,&contador,100);
        contador++;

        vTaskDelay(500);
    }
}

void receptor(void *pvParameters)
{

    uint32_t dato;
    while(true)
    {
        if(xQueueReceive(cola, &dato,100)==pdPASS)
            printf("El dato recibido es: %u\n",dato);

        // vTaskDelay(500);
    }
}