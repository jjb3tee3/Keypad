#include "keypad.h"

int KP_DEBUG_MODE = 0;

/* Helper function to print debug messages */
void printd(unsigned int level, const char* format, ...) {
	va_list arg;

	if(!KP_DEBUG_MODE)
		return;

	switch(level) {
		case KP_DEBUG:
			printf("[*] ");
			break;
		case KP_INFO:
			printf("[-] ");
			break;
		case KP_ERROR:
			printf("[!] ");
			break;
		default:	
			printf("[-] ");
	}

	va_start(arg, format);
	vprintf(format, arg);
	va_end(arg);
	printf("\n");
}

int kp_init() {
	int fd;	
	//int page_size = getpagesize();
	unsigned int *mem_addr = NULL;
	unsigned int mem_phys = 0x72A00000;
	volatile unsigned int *enable_vga;
	volatile unsigned int *vga_reg;

	fd = open("/dev/mem", O_RDWR | O_SYNC);

	if(fd < 0) {
		printd(KP_ERROR, "Open /dev/mem failed - %s %d",
			strerror(errno), errno);
		return -1;
	}

	mem_addr = (int *)mmap(
		0,
		page_size,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		fd,
		mem_phys);

	if(mem_addr == (unsigned int *)MAP_FAILED) {
		printd(KP_ERROR, "mmap failed");
		close(fd);	
		return -1;
	}

	printd(KP_INFO, "%x: %x", (int)mem_addr, *(mem_addr));

	vga_reg = mem_addr + 0x00;
	enable_vga = mem_addr + 0x01;

	*enable_vga = 0x000001E0;

	kp_loop(vga_reg);
}

void kp_loop(volatile unsigned int port) {
// check keypad for input
}

void kp_register_handler(unsigned int event, kp_key_handler_t handler) {
// set handler functions in struct
}

int main(int argc, char **argv) {
	int c;

	while((c = getopt(argc, argv, "dh")) != EOF) {
		switch(c) {
			case 'd':
				KP_DEBUG_MODE = 1;
				break;
			default:
				break;
		}
	}

	printd(0, "Debug mode: %d", KP_DEBUG_MODE);

	/*
	if(kp_init() < 0) {
		printd(KP_ERROR, "Unable to initialize keypad.");
		return -1;
	}
	*/
	return 0;
}
