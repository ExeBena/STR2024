#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define LED_PIN 16
#define LED_AMARILLO 17
#define LED_VERDE 18

// TaskHandle_t xTaskLedHandle;

void TareaLed(void *pvParameters) {
  // Inicializar el pin del LED como salida
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    uint32_t contador = 0;

    while (1) {
        // Encender el LED
        gpio_put(LED_PIN, 1);
        vTaskDelay(500); // Esperar 500 ms

        // Apagar el LED
        gpio_put(LED_PIN, 0);
        vTaskDelay(500); // Esperar 500 ms
        
        contador ++;

        if(contador>=5)
            vTaskDelete(NULL);

    }
}


int main() {

    stdio_init_all();

    // Crear las tareas
    xTaskCreate(TareaLed, "Led", 1024, NULL, 1, NULL);

    // Iniciar el scheduler de FreeRTOS
    vTaskStartScheduler();

    // No debería llegar aquí
    while (1) {}

    return 0;
}

