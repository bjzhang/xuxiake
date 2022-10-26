
#include <xuxiake.h>
#include <lib.h>
#include <gpio.h>
#include <asm.h>

void cpu_entry(void)
{
	xxk_print("XXK: Hello XU Xiake\n");
	setup_exception_vector();
	xxk_print("XXK: After set vector\n");
	mmu_init();
#ifdef CONFIG_MMU
	xxk_print("XXK: Test write addres not mappped by kernel:");
	*((unsigned long*)USER_MEM_START) = 0x0;
	xxk_print("...DONE\n");
#endif /* #ifdef CONFIG_MMU */
#ifdef CONFIG_USERSPACE
	xxk_print("XXK: Jump to userspace\n");
	copy_user_program();
	jump_to_user_mode();
#endif /* #ifdef CONFIG_USERSPACE */
	xxk_print("XXK: Exit!(Please poweroff or kill the qemu process)\n");
	while(1);
}

