/* mqttClient_main.c
 *
 * Copyright (C) 2006-2023 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/ssl.h"

#include "wolf/common.h"
#include "wolf/tcp.h"
#include "wolf/wifi.h"
#include "wolf/blink.h"
#include "lwip/tcp.h"

#define USE_CERT_BUFFERS_256
#define USE_CERT_BUFFERS_2048

#include <wolfssl/certs_test.h>



#include "wolfmqtt/mqtt_types.h"
#include "wolfmqtt/mqtt_client.h"
#include "examples/mqttport.h"
#include "examples/mqttnet.h"
#include "examples/mqttexample.h"

#include "wolf/mqtt.h"

#include "wolf/test_mosquitto_cert.h"

#include "tiny-json.h"

#include <FreeRTOS.h>
#include <task.h>

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void vTask1(void *pvParameters) {
    while(true) {
        printf("TASK 1 !!!\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // wait 1000 ms
    }
}

void vTask2(void *pvParameters) {
    while(true) {
        printf("TASK 2 !!!\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // wait 2000 ms
    }
}


TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;


void main(void)
{
    blink(15, 1);

    xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle);
    xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, &xTask2Handle);

    // Start Scheduler
    vTaskStartScheduler();

    while(true);
}


