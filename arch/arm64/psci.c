/* Partial Copy from linux/drivers/firmware/psci/psci.c */

#include <xuxiake.h>
#include <psci.h>
#include <asm.h>

static __always_inline unsigned long
__invoke_psci_fn_smc(unsigned long function_id,
		     unsigned long arg0, unsigned long arg1,
		     unsigned long arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	return res.a0;
}

typedef unsigned long (psci_fn)(unsigned long, unsigned long,
				unsigned long, unsigned long);
static psci_fn *invoke_psci_fn;

void psci_sys_poweroff(void)
{
	invoke_psci_fn(PSCI_0_2_FN_SYSTEM_OFF, 0, 0, 0);
}

/**
 *  Simplicity from the following function
 * int __init psci_dt_init(void)
 * int __init psci_acpi_init(void)
 */
void psci_init(void)
{
	invoke_psci_fn = __invoke_psci_fn_smc;
}
