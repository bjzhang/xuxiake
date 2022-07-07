#ifndef __XUXIAKE_H
#define __XUXIAKE_H
#ifndef __ASSEMBLY__
extern void _vectors(void);
/**
 * low level trap handler
 */
extern void _trap_handler(void);
/**
 * setup the _vectors/_trap_handler to exception vector
 */
void setup_exception_vector(void);
void jump_to_user_mode(void);
void cpu_entry(void);
#endif /* #ifndef __ASSEMBLY__ */
#endif /* #ifndef __XUXIAKE_H */
