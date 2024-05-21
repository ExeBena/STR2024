#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"


TaskHandle_t xTask2Handle = NULL;

void vTask1( void * pvParameters )
{
    UBaseType_t uxPriority;

    //Obtencion de prioridad de la tarea
    uxPriority = uxTaskPriorityGet( NULL );

    for( ;; )
    {
        printf( "Tarea 1 corriendo\n" );

        printf( "Elevando la prioridad de la tarea 2\n" );

        //Seteo de prioridad de tarea
        vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );
    }
}

void vTask2( void * pvParameters )
{
    UBaseType_t uxPriority;

//Obtencion de prioridad de tarea
    uxPriority = uxTaskPriorityGet( NULL );
    for( ;; )
    {
        printf( "Tarea 2 ejecutando\n" );

        printf( "Bajando prioridad de la tarea 2\n" );

        //Seteo de prioridad de tarea
        vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
    }
}

int main( void )
{
    stdio_init_all();

    xTaskCreate( vTask1, "Task 1", 1000, NULL, 2, NULL );
    /* La tarea es creada con prioridad 2 _____^. */
    

    xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle );
    /*El handler de la tarea es el ultimo argumento^^^^^^^^^^^^^ */

    vTaskStartScheduler();

    while(true)
    {
    }
}