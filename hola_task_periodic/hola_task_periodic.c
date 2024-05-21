#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "FreeRTOS.h"
#include "task.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define LED_PIN 25


// Prototipos de funciones
void uart_task(void *pvParameters);
void uart_task_periodic(void *pvParameters);


void init_uart() {
    // Inicializar stdio para usar UART0
    stdio_init_all();
    // stdio_uart_init();

    // Establecer la velocidad de baudios, bits de datos, bits de parada y paridad de UART
    uart_init(UART_ID, BAUD_RATE);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Establecer los pines de UART
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
}

void main()
{
    // stdio_init_all();
    init_uart();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);

    xTaskCreate(uart_task, "Tarea 1", 256, "Tarea 1 dice Hola!", 2, NULL);
    xTaskCreate(uart_task, "Tarea 2", 256, "Tarea 2 dice Hola!", 2, NULL);
    xTaskCreate(uart_task_periodic,"Tarea_periodica",256,"Tarea periodica ejecutandose",3,NULL);

    vTaskStartScheduler();


}

void uart_task(void *pvParameters)
{


char *mensaje = (char*)pvParameters;

while (1)
{
    
    gpio_xor_mask(1ul<<LED_PIN);

    uart_puts(UART_ID,mensaje);

    uart_putc(UART_ID,'\n');

    uart_tx_wait_blocking(UART_ID);

}


}


void uart_task_periodic(void *pvParameters)
{
TickType_t ultimo_despertar = xTaskGetTickCount();
TickType_t periodo_5ms = pdMS_TO_TICKS(5);

char *mensaje = (char*)pvParameters;

while (1)
{
    
    gpio_xor_mask(1ul<<LED_PIN);

    uart_puts(UART_ID,mensaje);

    uart_putc(UART_ID,'\n');

    uart_tx_wait_blocking(UART_ID);

    vTaskDelayUntil(&ultimo_despertar,periodo_5ms);

}


}