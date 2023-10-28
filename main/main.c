#include <stdio.h>
#include <inttypes.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_33, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_33, GPIO_PULLUP_ONLY);
    while(1)
    {
        printf("Pin level is: %d\n", gpio_get_level(GPIO_NUM_33));
        fflush(stdout);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}