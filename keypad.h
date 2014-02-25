/*
	Author: 	Jake Baker, Peter Smith, Nathan Toft
	Email:		jake@rithium.com
	Date:		19/02/2014
	Desc:		Event based keypad implementation for the 
			robot arm Embedded Co-Design assignment.		
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define KP_DEBUG 0x00
#define KP_INFO 0x01
#define KP_ERROR 0x02

#define KP_KEYPRESS_EVENT 0x00
#define KP_KEY_DOWN_EVENT 0x01
#define KP_KEY_UP_EVENT 0x02

typedef void (*kp_key_handler_t)(int);

typedef struct kp_handler {
	kp_key_handler_t key_pressed;
	kp_key_handler_t key_down;
	kp_key_handler_t key_up;
};

int kp_init();
void kp_loop(volatile unsigned int *);
void kp_register_handler(unsigned int, kp_key_handler_t);
