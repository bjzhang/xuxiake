
#include <xuxiake.h>

int poweroff()
{
	u32 magic1 = LINUX_REBOOT_MAGIC1;
	u32 magic2 = LINUX_REBOOT_MAGIC2;
	u32 power_off = LINUX_REBOOT_CMD_POWER_OFF;
	s32 ret;

	__asm__ __volatile__("mov x0, %1\n\t"\
			     "mov x1, %2\n\t"\
			     "mov x2, %3\n\t"\
			     "mov x8, #142\n\t"\
			     "svc #0\n\t"\
			     "mov %0, x0\n\t"\
			     : "=r" (ret)
			     : "r" (magic1), "r" (magic2), "r" (power_off)
			     : "x0", "x1", "x2", "x8");
	return ret;
}

