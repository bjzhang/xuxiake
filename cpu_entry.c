
#include <xuxiake.h>
#include <lib.h>
#include <gpio.h>
#include <asm.h>

void cpu_entry(void)
{
	arch_init();
	xxk_print("XXK: Hello XU Xiake\n");
	setup_exception_vector();
	xxk_print("XXK: After set vector\n");
	copy_user_program();
	mmu_init();
#if defined(CONFIG_MMU) && !defined(CONFIG_USERSPACE)
	xxk_print("XXK: Test write addres not mappped by kernel:");
	*((unsigned long*)USER_MEM_START) = 0x0;
	xxk_print("...DONE\n");
#endif /* #ifdef CONFIG_MMU */
#ifdef CONFIG_USERSPACE
	xxk_print("XXK: Jump to userspace\n");
	jump_to_user_mode();
#endif /* #ifdef CONFIG_USERSPACE */
	xxk_print("XXK: Exit!(Please Ctrl+a,x or kill the qemu process)\n");
	while(1);
}

