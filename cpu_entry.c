
#include "xuxiake.h"
#include "lib.h"
#include "gpio.h"

#ifdef DEBUG
#define xxk_debug(a) xxk_print(a)
#else
#define xxk_debug(a) while(0);
#endif /* ifdef DEBUG */

void setup_exception_vector();
void jump_to_user_mode();

void user_program()
{
	xxk_print("try to output!\n");
}

void cpu_entry(void)
{
	xxk_print("XXK: Hello XU Xiake\n");
	setup_exception_vector();
	xxk_print("XXK: after set vector\n");
	jump_to_user_mode();
	xxk_print("XXK: exit!\n");
	while(1);
}

