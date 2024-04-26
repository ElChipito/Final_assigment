#include "FreeRTOS.h"
#include "task.h"
#include "ipsa_shed.h"
#include <stdio.h>

/* Priorités des tâches */
#define PRINT_WORKING_PRIORITY      (tskIDLE_PRIORITY + 4)
#define MULTIPLY_NUMBERS_PRIORITY   (tskIDLE_PRIORITY + 3)
#define CONVERT_TEMP_PRIORITY       (tskIDLE_PRIORITY + 2)
#define BINARY_SEARCH_PRIORITY      (tskIDLE_PRIORITY + 1)

/* Déclarations des fonctions externes des tâches */
extern void print_working(void *pvParameters);
extern void vTaskConvertTemp(void *pvParameters);
extern void vTaskMultiplyNumbers(void *pvParameters);
extern void vTaskBinarySearch(void *pvParameters);
extern void vAperiodicTaskExample(void *pvParameters);


void ipsa_sched(void)
{
    xTaskCreate(print_working, "PrintWorking", configMINIMAL_STACK_SIZE, NULL, PRINT_WORKING_PRIORITY, NULL);
    xTaskCreate(vTaskConvertTemp, "ConvertTemp", configMINIMAL_STACK_SIZE, NULL, CONVERT_TEMP_PRIORITY, NULL);
    xTaskCreate(vTaskMultiplyNumbers, "MultiplyNumbers", configMINIMAL_STACK_SIZE, NULL, MULTIPLY_NUMBERS_PRIORITY, NULL);
    xTaskCreate(vTaskBinarySearch, "BinarySearch", configMINIMAL_STACK_SIZE, NULL, BINARY_SEARCH_PRIORITY, NULL);

    vTaskStartScheduler();
}


static void print_working(void *pvParameters) {
	const TickType_t xDelay = pdMS_TO_TICKS(100); // Period of 100ms
	while(1) {
        printf("Working\n");
        vTaskDelayUntil(xDelay);
    }
}


static void vTaskConvertTemp(void *pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(60); // Period of 60ms
    while(1) {
        double fahrenheit = 98.6;
        FahrenheitToCelsius(fahrenheit);
        vTaskDelayUntil(xDelay);
    }
}
void FahrenheitToCelsius(double fahrenheit) {
    double celsius = (fahrenheit - 32) * 5 / 9;
    printf("%.2f degrés Fahrenheit équivalent à %.2f degrés Celsius.\n", fahrenheit, celsius);
}


static void vTaskMultiplyNumbers(void *pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(150); // Period of 150ms
    while(1) {
        long int x1 = 19838074558;
        long int x2 = 65642864582;
        long int result = x1 * x2;
        printf("Résultat de la multiplication: %ld\n", result);
        vTaskDelayUntil(xDelay);
    }
}


static int arr[50]; 

static void vTaskBinarySearch(void *pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(25); // Period of 25ms
    while(1) {
        int x = 25;
        int result = binary_search(arr, 0, 49, x);
        if (result != -1) {
            printf("Élément trouvé à l'indice : %d\n", result);
        } else {
            printf("Élément non trouvé.\n");
        }
        vTaskDelayUntil(xDelay);
    }
}



int binary_search(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}
