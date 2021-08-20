
#include "lib.h"
#include "gpio.h"

#define GPIO_BASE		0x02000000U
//PORT_B_CFG 0x30
//PORT_C_CFG 0x60
//...
//PORT_G_CFG 0x120
#define GPIO_CFG_BASE(port)	(GPIO_BASE + ((u32)0x30 << (port - GPIO_PB)))
#define GPIO_DATA_BASE(port)	(GPIO_CFG_BASE(port) + 0x10)

typedef unsigned int u32;

enum gpio_port {
	GPIO_PB,
	GPIO_PC,
	GPIO_PD,
	GPIO_PE,
	GPIO_PF,
	GPIO_PG,
};

enum gpio_t {
	GPIO_INPUT,
	GPIO_OUTPUT,
};

//#define DEBUG
#ifdef DEBUG
#define xxk_debug(a) xxk_print(a)
#define xxk_debug_hex(a) xxk_print_hex(a)
#else
#define xxk_debug(a) while(0);
#define xxk_debug_hex(a) while(0);
#endif /* #ifdef DEBUG */

//type: input, output, other function
//Initialize gpio as specific port, num and type
static int gpio_init_D1(enum gpio_port port, u32 num, enum gpio_t type);
//output gpio value for specific port and num
static int gpio_output_D1(enum gpio_port port, u32 num, int value);

static int gpio_init_D1(enum gpio_port port, u32 num, enum gpio_t type)
{
	u32 *cfg_addr;
	u32 cfg_mask;
	u32 cfg_offset;

	if (port < GPIO_PB || port > GPIO_PG)
		return -EINVAL;

	if (num < 0 || num > 12)
		return -EINVAL;

	switch(type) {
		case GPIO_OUTPUT:
			xxk_debug("output mode\n");
			cfg_addr = (u32 *)GPIO_CFG_BASE(port);
			if (num > 7)
				cfg_addr += 1;

			xxk_debug("cfg addr: ");
			xxk_debug_hex((u32)cfg_addr);
			xxk_debug("\n");

			if (num < 8)
				cfg_offset = num << 2;
			else
				cfg_offset = (num - 8) << 2;

			xxk_debug("cfg offset : ");
			xxk_debug_hex(cfg_offset);
			xxk_debug("\n");
			cfg_mask = 0xf;
			xxk_debug("original cfg addr value: ");
			xxk_debug_hex(*cfg_addr);
			xxk_debug("\n");
			*cfg_addr &= ~(cfg_mask << cfg_offset);
			*cfg_addr |= (type & cfg_mask) << cfg_offset;
			xxk_debug("new cfg addr value: ");
			xxk_debug_hex(*cfg_addr);
			xxk_debug("\n");

			break;
		default:
			xxk_print("Only support output right now!\n");
			break;
	}

	return 0;
}

static int gpio_output_D1(enum gpio_port port, u32 num, int value)
{
	u32 *data_addr;

	if (port < GPIO_PB || port > GPIO_PG)
		return -EINVAL;

	if (num < 0 || num > 12)
		return -EINVAL;

	data_addr = (u32 *)GPIO_DATA_BASE(port);
	xxk_debug("original data: ");
	xxk_debug_hex(*data_addr);
	xxk_debug("\n");
	*data_addr = (!!value) << num;
	data_addr = (u32 *)GPIO_DATA_BASE(port);
	xxk_debug("new data: ");
	xxk_debug_hex(*data_addr);
	xxk_debug("\n");

	return 0;
}

void delay(int ms)
{
	int i, j;

	if (ms < 0)
		return;

	for (i = 0; i < ms; i++)
		for (j = 0; j < 1000000; j++);
}

void set_pmp()
{
        {
                unsigned long __v = 0x1b;
                __asm__ __volatile__("csrw 0x3a2, %0"
                                     :
                                     : "r"(__v)
                                     : "memory");
        }
        {
                unsigned long __v = 0x200001ff;
                __asm__ __volatile__("csrw 0x3b8, %0"
                                     :
                                     : "r"(__v)
                                     : "memory");
        }
}

void gpio_test_D1()
{
//	set_pmp();
	gpio_init_D1(GPIO_PB, 12, GPIO_OUTPUT);
	while(1) {
		xxk_debug("output 1\n");
		gpio_output_D1(GPIO_PB, 12, 1);
		delay(10);
		xxk_debug("output 0\n");
		gpio_output_D1(GPIO_PB, 12, 0);
		delay(10);
	}
}

void gpio_test()
{
	gpio_test_D1();
}

