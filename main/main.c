#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ssd1306.h>

int16_t counter = 0;
char text_output[20];
static ssd1306_handle_t ssd1306_dev = NULL;

void display_task(void *pvParameters)
{
    while(1)
    {
        counter++;
        sprintf(text_output, "%d", counter);
        ssd1306_clear_screen(ssd1306_dev, 0x00);
        ssd1306_draw_string(ssd1306_dev, 0, 0, (const uint8_t *)text_output, 12, 1);
        ssd1306_refresh_gram(ssd1306_dev);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_8;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = GPIO_NUM_9;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    i2c_param_config(I2C_NUM_1, &conf);
    i2c_driver_install(I2C_NUM_1, conf.mode, 0, 0, 0);

    ssd1306_dev = ssd1306_create(I2C_NUM_1, SSD1306_I2C_ADDRESS);
    ssd1306_refresh_gram(ssd1306_dev);
    ssd1306_clear_screen(ssd1306_dev, 0x00);

    xTaskCreate(&display_task, "DisplayTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1)
    {
        printf("Hello World\n");
        fflush(stdout);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}