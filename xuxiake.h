#ifndef __XUXIAKE_H
#define __XUXIAKE_H
#ifndef __ASSEMBLY__
#include <asm-generic/errno.h>
#include <lib.h>

#ifdef DEBUG
#warning "DEBUG mode: it may lead to lots of output"
#define xxk_debug(str) xxk_print(str)
#define xxk_debug_hex32(hex) xxk_print_hex32(hex)
#define xxk_debug_hex64(hex) xxk_print_hex64(hex)
#else
#define xxk_debug(str) ({while(0);})
#define xxk_debug_hex32(hex) ({while(0);})
#define xxk_debug_hex64(hex) ({while(0);})
#endif /* ifdef DEBUG */

#define xxk_info(str) xxk_print(str)
#define xxk_info_hex32(hex) xxk_print_hex32(hex)
#define xxk_info_hex64(hex) xxk_print_hex64(hex)

#define xxk_error(str) xxk_print(str)
#define xxk_error_hex32(hex) xxk_print_hex32(hex)
#define xxk_error_hex64(hex) xxk_print_hex64(hex)

//TODO: It is more clearer that if define _vectors as array
extern void _vectors(void);
/**
 * low level trap handler
 */
extern void _trap_handler(void);
/**
 * setup the _vectors/_trap_handler to exception vector
 */
void setup_exception_vector(void);
void copy_user_program(void);
void jump_to_user_mode(void);
/**
 * mmu init
 *
 * Including static memory and device register map and turn on MMU
 */
void mmu_init(void);
struct trap_regs;
/**
 * Data abort handler. came from low exception level or curent exception level
 *
 * Return 1 means exeption haneld; 0 means unhandled
 */
int da_handler(unsigned long esr, struct trap_regs *t);
/**
 * Instruction abort handler. came from low exception level or curent exception
 * level
 *
 * Return 1 means exeption haneld; 0 means unhandled
 */
int ia_handler(unsigned long esr, struct trap_regs *t);
/**
 * The overall entry of XU xiake
 */
void cpu_entry(void);
#endif /* #ifndef __ASSEMBLY__ */
#endif /* #ifndef __XUXIAKE_H */
