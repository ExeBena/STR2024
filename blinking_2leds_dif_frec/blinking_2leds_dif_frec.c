#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define LED_ROJO 16
#define LED_AMARILLO 17

typedef struct datos_funciones
{
    /* data */
    uint32_t led;
    uint32_t periodo;
}parametro_struct;


void led_task(parametro_struct * param )
{   
    while (true) {
        gpio_xor_mask(1ul<<(unsigned int)param->led);
        vTaskDelay(pdMS_TO_TICKS(param->periodo));
    }
}

int main()
{
    parametro_struct parametros_tarea1 = {LED_ROJO,500};
    parametro_struct parametros_tarea2 = {LED_AMARILLO,100};

    stdio_init_all();

    gpio_init(LED_ROJO);
    gpio_set_dir(LED_ROJO, GPIO_OUT);
    gpio_init(LED_AMARILLO);
    gpio_set_dir(LED_AMARILLO, GPIO_OUT);

    xTaskCreate(led_task, "Tarea 1", 256, &parametros_tarea1, 1, NULL);
    xTaskCreate(led_task, "Tarea 2", 256, &parametros_tarea2, 1, NULL);

    vTaskStartScheduler();

    while(1){};
}