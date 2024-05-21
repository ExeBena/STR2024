#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define LED_ROJO 16
#define LED_AMARILLO 17
#define LED_VERDE 18

typedef struct datos_funciones
{
    /* data */
    uint32_t led;
    uint32_t periodo;
    uint32_t iter;
    TaskHandle_t handle_propio;
}parametro_struct;


void led_task(parametro_struct * param )
{   

    param->handle_propio = xTaskGetCurrentTaskHandle();

    while (true) {
        gpio_xor_mask(1ul<<(unsigned int)param->led);

        vTaskDelay(pdMS_TO_TICKS(param->periodo));
    }
}

void sched_task(TaskHandle_t * tareas)
{

    uint32_t contador = 0;
    while(true){

           
        if(contador == 5)
            vTaskDelete(tareas[0]);
        else if(contador == 8)
            vTaskDelete(tareas[1]);
        else if(contador==10)
            vTaskDelete(tareas[2]);
        
        contador ++;

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    TaskHandle_t Tareas[3];
    parametro_struct parametros_tarea1 = {LED_ROJO,500,4,Tareas[0]};
    parametro_struct parametros_tarea2 = {LED_AMARILLO,100,50,Tareas[1]};
    parametro_struct parametros_tarea3 = {LED_VERDE,1000,10,Tareas[2]};

    stdio_init_all();

    gpio_init(LED_ROJO);
    gpio_set_dir(LED_ROJO, GPIO_OUT);
    gpio_init(LED_AMARILLO);
    gpio_set_dir(LED_AMARILLO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);


    xTaskCreate(led_task, "Tarea 1", 256, &parametros_tarea1, 1, &Tareas[0]);
    xTaskCreate(led_task, "Tarea 2", 256, &parametros_tarea2, 1, &Tareas[1]);
    xTaskCreate(led_task, "Tarea 3", 256, &parametros_tarea3, 1, &Tareas[2]);
    xTaskCreate(sched_task, "Tarea_planificadora", 256, Tareas, 2,NULL);

    vTaskStartScheduler();

    while(1){};
}