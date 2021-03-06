/* Blink Example Task

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* From ESP-IDF examples */
#include "led_strip.h"

#include "sdkconfig.h"

static const char *TAG = "blink";

/* None of this will be compiled in at all if no blink LED is configured */
#ifndef CONFIG_BLINK_LED_NONE


/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;

#ifdef CONFIG_BLINK_LED_RMT

static int blink_stack_size = 0x1000;

static led_strip_t *pStrip;

static void blink_led(void)
{
    /* If the addressable LED is enabled */
    if (s_led_state) {
        /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
        pStrip->set_pixel(pStrip, 0, 16, 16, 16);
        /* Refresh the strip to send data */
        pStrip->refresh(pStrip, 100);
    } else {
        /* Set all LED off to clear all pixels */
        pStrip->clear(pStrip, 50);
    }
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED every %d ms", CONFIG_BLINK_PERIOD);
    /* LED strip initialization with the GPIO and pixels number*/
    pStrip = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, BLINK_GPIO, 1);
    /* Set all LED off to clear all pixels */
    pStrip->clear(pStrip, 50);
}

#elif CONFIG_BLINK_LED_GPIO

static int blink_stack_size = 0x0220;

static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink LED on GPIO %d!", BLINK_GPIO);
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

#endif


static void run_blink_led()
{
    while (1) {
        ESP_LOGD(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        blink_led();
        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}

#endif /* BLINK_LED_NONE */

void initialize_blink()
{
#ifndef CONFIG_BLINK_LED_NONE
    /* Configure the peripheral according to the LED type */
    configure_led();

    xTaskCreate(run_blink_led, "blink", blink_stack_size, NULL, tskIDLE_PRIORITY, NULL);
#endif
}
