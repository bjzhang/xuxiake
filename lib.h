
#ifndef __LIB_H__
#define __LIB_H__

#include <type.h>
/**
 * bit ops
 */
#define SET_BITS(dst, val, mask, shift)			\
{							\
	(dst) = (dst) & (~((mask) << (shift)));		\
	(dst) = (dst) | (((mask) & (val)) << (shift));	\
}

#define GET_BITS(src, val, mask, shift)			\
{							\
	(val) = (src) >> (shift);			\
	(val) = (val) & (mask);				\
}

u8 xxk_getchar(void);
void xxk_putchar(u8 c);
void xxk_print(char *s);
void xxk_print_hex32(u32 num);
void xxk_print_hex64(u64 num);
void memcpy(void *dst, void *src, s32 size);

#endif /* #ifndef __LIB_H__ */
