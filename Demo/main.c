//main.c
//authored by Jared Hull
//
//tasks 1 and 2 blink the ACT LED
//main initialises the devices and IP tasks

#include <FreeRTOS.h>
#include <task.h>

#include "interrupts.h"
#include "gpio.h"
#include "video.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"


//Only for debug, normally should not 
//   include private header
#include "FreeRTOS_IP_Private.h"

#define BUTTON_PIN 21
#define LED_PIN 26

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef long int32_t;

void blinkDot(){
	SetGpio(LED_PIN, 1);
	vTaskDelay(300);
	SetGpio(LED_PIN, 0);
	vTaskDelay(200);
}
void blinkDash(){
	SetGpio(LED_PIN, 1);
	vTaskDelay(700);
	SetGpio(LED_PIN, 0);
	vTaskDelay(200);
}

void restSpace(){
	vTaskDelay(800);
}
void task3(){
	char message[] = ".-- .. -. ... .- -";
	int messageIndex = 0;
	while(1){
		if(ReadGpio(BUTTON_PIN) == 0){
			continue;
		}
		switch(message[messageIndex]){
			case '.':
				blinkDot();
				break;
			case '-':
				blinkDash();
				break;
			case ' ':
				restSpace();
				break;
			case '\0':
				messageIndex = 0;
				vTaskDelay(1000);
				break;
			default:
				break;
		}
		++messageIndex;
	}
}
int main(void) {
	SetGpioFunction(LED_PIN, 1);			// RDY led
	SetGpioFunction(BUTTON_PIN, 0);

	initFB();
	SetGpio(LED_PIN, 0);
	//videotest();

	DisableInterrupts();
	InitInterruptController();

	xTaskCreate(task3, "HELLO_WORLD_BLINK", 128, NULL, 0, NULL);
	//set to 0 for no debug, 1 for debug, or 2 for GCC instrumentation (if enabled in config)
	loaded = 1;

	vTaskStartScheduler();

	/*
	 *	We should never get here, but just in case something goes wrong,
	 *	we'll place the CPU into a safe loop.
	 */
	while(1) {
		;
	}
}
