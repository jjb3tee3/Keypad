/*
	Author: 	Jake Baker, Peter Smith, Nathan Toft
	Email:		jake@rithium.com
	Date:		19/02/2014
	Desc:		Event based keypad implementation for the 
			robot arm Embedded Co-Design assignment.		
*/
#include <stdio.h>
#include <stdlib.h>

#define KP_KEYPRESS_EVENT 0x00
#define KP_KEY_DOWN_EVENT 0x01
#define KP_KEY_UP_EVENT 0x02

typedef void (*kp_key_handler_t)(int)

struct kp_handler {
	kp_key_handler_t key_pressed,
	kp_key_handler_t key_down,
	kp_key_handler_t key_up
};

void kp_init();
void kp_loop();
void kp_register_handler(int, kp_key_handler_t);
