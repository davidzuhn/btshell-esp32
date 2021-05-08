/* Network Shell example/demonstration program

   Allows manipulation of BLE & WiFi capabilities of the ESP32

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "blink.h"
#include "command-line.h"

#include "cmd_system.h"
#include "btshell.h"

void print_chip_info()
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
}


#ifdef __cplusplus
extern "C"
#endif
void app_main(void)
{
    /* Initialize everything */
    initialize_blink();

#if CONFIG_COMMAND_LINE_ENABLED
    initialize_command_line();

    initialize_btshell();
#if 1
    register_system();
#endif
#if 0
    register_btshell();
#endif
#endif


    /* Run the main application */
    print_chip_info();

    /* this function exits, but the program is intended to keep running
     * forever, since the other tasks (if any) never exit
     *
     * If you're running this without the command line, this program is
     * pretty useless and so it will immediately exit
     */
}
