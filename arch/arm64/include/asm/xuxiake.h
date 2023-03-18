#ifndef __ASM_XUXIAKE_H
#define __ASM_XUXIAKE_H
/**
 * svc handler in c language
 */
void trap_handler(unsigned long esr, struct trap_regs *t);

/**
 * Power off system by send the psci command
 */
void psci_sys_poweroff(void);
/**
 * psci initialization
 */
void psci_init(void);
#endif /* ifndef __ASM_XUXIAKE_H */
