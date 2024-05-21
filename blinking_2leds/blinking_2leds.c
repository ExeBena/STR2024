#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define LED_ROJO 16
#define LED_AMARILLO 17

void led_task(void * const led_pin)
{   
    while (true) {
        gpio_xor_mask(1ul<<(unsigned int)led_pin);
        vTaskDelay(500);
    }
}

int main()
{
    stdio_init_all();

    gpio_init(LED_ROJO);
    gpio_set_dir(LED_ROJO, GPIO_OUT);
    gpio_init(LED_AMARILLO);
    gpio_set_dir(LED_AMARILLO, GPIO_OUT);

    xTaskCreate(led_task, "Tarea 1", 256, LED_ROJO, 1, NULL);
    xTaskCreate(led_task, "Tarea 2", 256, LED_AMARILLO, 1, NULL);

    vTaskStartScheduler();

    while(1){};
}