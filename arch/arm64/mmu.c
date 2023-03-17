
#ifdef CONFIG_MMU
#include <xuxiake.h>
#include <lib.h>	//for SET_BITS, GET_BITS
#include <asm.h>
//SCTLR_EL1
//#define SCTLR_TBI1_SHIFT	(38UL)
//#define SCTLR_TBI1_MASK	(1UL)
//#define SCTLR_TBI0_SHIFT	(37UL)
//#define SCTLR_TBI0_MASK	(1UL)
//#define SCTLR_TOP_BIT_IGNORED (1UL)
//
//#define SCTLR_AS_SHIFT	(37UL)
//#define SCTLR_AS_MASK		(1UL)
//#define SCTLR_ASID_16BIT	(1UL)

//Cortex-A72 default value: 0x00C50838
#define SCTLR_EE_SHIFT			(25UL)
#define SCTLR_EE_MASK			(1UL)
#define SCTLR_EE_LITTLE_ENDIAN		(0UL)
#define SCTLR_EE_BIG_ENDIAN		(1UL)

#define SCTLR_WXN_SHIFT			(19UL)
#define SCTLR_WXN_MASK			(1UL)
#define SCTLR_WXN_NOT_FORCE_XN		(0UL)
#define SCTLR_WXN_FORCE_XN		(1UL)

#define SCTLR_NTWE_SHIFT		(18UL)
#define SCTLR_NTWE_MASK			(1UL)
#define SCTLR_NTWE_NOT_TRAP		(0UL)
#define SCTLR_NTWE_TRAP			(1UL)

#define SCTLR_NTWI_SHIFT		(18UL)
#define SCTLR_NTWI_MASK			(1UL)
#define SCTLR_NTWI_NOT_TRAP		(0UL)
#define SCTLR_NTWI_TRAP			(1UL)

#define SCTLR_I_SHIFT			(12UL)
#define SCTLR_I_MASK			(1UL)
#define SCTLR_I_CACHE_DISABLE		(0UL)
#define SCTLR_I_CACHE_ENABLE		(1UL)

#define SCTLR_UMA_SHIFT			(9UL)
#define SCTLR_UMA_MASK			(1UL)
#define SCTLR_UMA_DISABLE_FROM_EL0	(0UL)
#define SCTLR_UMA_ENABLE_FROM_EL0	(1UL)

#define SCTLR_SA0_SHIFT			(4UL)
#define SCTLR_SA0_MASK			(1UL)
#define SCTLR_SA0_DISABLE		(0UL)
#define SCTLR_SA0_ENABLE		(1UL)

#define SCTLR_SA_SHIFT			(4UL)
#define SCTLR_SA_MASK			(1UL)
#define SCTLR_SA_DISABLE		(0UL)
#define SCTLR_SA_ENABLE			(1UL)

#define SCTLR_C_SHIFT			(2UL)
#define SCTLR_C_MASK			(1UL)
#define SCTLR_C_DCACHE_DISABLE		(0UL)
#define SCTLR_C_DCACHE_ENABLE		(1UL)

#define SCTLR_A_SHIFT			(1UL)
#define SCTLR_A_MASK			(1UL)
#define SCTLR_A_AC_DISABLE		(0UL)
#define SCTLR_A_AC_ENABLE		(1UL)

#define SCTLR_M_SHIFT			(0UL)
#define SCTLR_M_MASK			(1UL)
#define SCTLR_M_MMU_DISABLE		(0UL)
#define SCTLR_M_MMU_ENABLE		(1UL)

//TCR_EL1
#define TCR_T0SZ_SHIFT		(0UL)
#define TCR_T0SZ_MASK		(0x3fUL)
#define TCR_SINGLE_ADDR(tcr)	((((u64)tcr) & (~TCR_T0SZ_MASK)) | 16)

//Page Table
//Table
#define PT_L1_4K_NLT_SHIFT		(12UL)
//48-12=36
#define PT_L1_4K_NLT_MASK		(0xfffffffffUL)
#define PT_L1_4K_OA_SHIFT		(30UL)
#define PT_L1_4K_OA_MASK		(0x3ffffUL)

//Block
#define PT_L1_NG_SHIFT			(11UL)
#define PT_L1_NG_MASK			(1UL)
#define PT_L1_AF_SHIFT			(10UL)
#define PT_L1_AF_MASK			(1UL)
#define PT_L1_AF_1			(1UL)
#define PT_L1_SH_SHIFT			(8UL)
#define PT_L1_SH_MASK			(3UL)
#define PT_L1_AP_SHIFT			(6UL)
#define PT_L1_AP_MASK			(3UL)
#define PT_L1_AP_RW_NONE		(0UL)
#define PT_L1_AP_RW_RW			(1UL)
#define PT_L1_AP_RO_NONE		(2UL)
#define PT_L1_AP_RO_RO			(3UL)
#define PT_L1_NS_SHIFT			(5UL)
#define PT_L1_NS_MASK			(1UL)
#define PT_L1_ATTR_INDX_SHIFT		(2UL)
#define PT_L1_ATTR_INDX_MASK		(7UL)
#define PT_L1_PT_TYPE_SHIFT		(0UL)
#define PT_L1_PT_TYPE_MASK		(3UL)
#define PT_L1_PT_TYPE_INVALID		(0UL)
#define PT_L1_PT_TYPE_TABLE		(3UL)
#define PT_L1_PT_TYPE_BLOCK		(1UL)

//MAIR
#define MAIR_ATTR_BITS_SHIFT		(3UL)
#define MAIR_ATTR_MAX			(1UL << MAIR_ATTR_BITS_SHIFT)
#define MAIR_ATTR_MASK			((1UL << MAIR_ATTR_MAX) - 1)
//Normal memory, Outer Write-Through Non-transient, Read allocate, Write allocate
#define MAIR_ATTR_NORMAL_OUTTER_SHIFT	(4UL)
#define MAIR_ATTR_NORMAL_OUTTER_MASK	(0xfUL)
#define MAIR_ATTR_NORMAL_OUTTER_WB_VAL	(0xfUL)
//Normal memory, Outer Write-Through Non-transient, Read allocate, Write allocate
#define MAIR_ATTR_NORMAL_INNER_SHIFT	(0UL)
#define MAIR_ATTR_NORMAL_INNER_MASK	(0xfUL)
#define MAIR_ATTR_NORMAL_INNER_WB_VAL	(0xfUL)
//Device memory with nGnRnE
#define MAIR_ATTR_DEVICE_SHIFT		(0UL)
#define MAIR_ATTR_DEVICE_NGNRNE_VAL	(0UL)
//Senario
#define MAIR_NORMAL			(MAIR_ATTR_NORMAL_OUTTER_WB_VAL << MAIR_ATTR_NORMAL_OUTTER_SHIFT) \
					| (MAIR_ATTR_NORMAL_INNER_WB_VAL << MAIR_ATTR_NORMAL_INNER_SHIFT)
#define MAIR_DEVICE			MAIR_ATTR_DEVICE_NGNRNE_VAL


enum mair_attr_idx {MAIR_NORMAL_IDX, MAIR_DEVICE_IDX, MAIR_IDX_VALID_MAX};
enum memory_type {MEMORY_KERNEL, MEMORY_DEVICE, MEMORY_USER, MEMORY_USER_DATA, MEMORY_TYPE_MAX};

/**
 * Memory barrier
 */
void dsb_sy(void);
/**
 * API for accessing EL1 system control regiser
 */
u64	get_far(void);
u64	get_mair(void);
void	set_mair(u64 mair);
u64	get_sctlr(void);
void	set_sctlr(u64 sctlr);
u64	get_tcr(void);
void	set_tcr(u64 tcr);
u64	get_ttbr(s32 idx);
void	set_ttbr(u64 ttbr, s32 idx);

u8 mair_attrs[MAIR_ATTR_MAX] = {
	[MAIR_NORMAL_IDX] = MAIR_NORMAL,
	[MAIR_DEVICE_IDX] = MAIR_DEVICE,
};

//From ARMv8 ARM TTBR0_EL1 description
//A translation table is required to be aligned to the size of the table. If a
//table contains fewer than eight entries, it must be aligned on a 64 byte
//address boundary.
u64 ttbr0_el1[1]  __attribute__ ((aligned (4096)));
u64 ttb_l1[MEMORY_MAX/1024/1024/1024]  __attribute__ ((aligned (4096)));

void dsb_sy(void)
{
	__asm__ __volatile__("dsb sy\n\t"	\
			     :
			     :
			     :);
}

/**
 * API for accessing system control regiser
 */
u64 get_far(void)
{
	u64 far = (u64)-1;

        __asm__ __volatile__("mrs %0, FAR_EL1\n\t"\
                             : "=r" (far)
                             :
                             :);

	return far;
}

u64 get_mair(void)
{
	u64 mair = (u64)-1;

        __asm__ __volatile__("mrs %0, MAIR_EL1\n\t"\
                             : "=r" (mair)
                             :
                             :);

	return mair;
}

void set_mair(u64 mair)
{
        __asm__ __volatile__("msr MAIR_EL1, %0\n\t"\
                             :
                             : "r" (mair)
                             :);
}

u64 get_sctlr(void)
{
	u64 sctlr = (u64)-1;

        __asm__ __volatile__("mrs %0, SCTLR_EL1\n\t"\
                             : "=r" (sctlr)
                             :
                             :);

	return sctlr;
}

void set_sctlr(u64 sctlr)
{
        __asm__ __volatile__("msr SCTLR_EL1, %0\n\t"\
                             :
                             : "r" (sctlr)
                             :);
}

u64 get_tcr(void)
{
	u64 tcr = (u64)-1;

        __asm__ __volatile__("mrs %0, TCR_EL1\n\t"\
                             : "=r" (tcr)
                             :
                             :);

	return tcr;
}

void set_tcr(u64 tcr)
{
        __asm__ __volatile__("msr TCR_EL1, %0\n\t"\
                             :
                             : "r" (tcr)
                             :);
}

u64 get_ttbr(s32 idx)
{
	u64 ttbr = (u64)-1;

	if (0 == idx) {
		__asm__ __volatile__("mrs %0, TTBR0_EL1\n\t"\
				     : "=r" (ttbr)
				     :
				     :);
	} else if (1 == idx) {
		__asm__ __volatile__("mrs %0, TTBR1_EL1\n\t"\
				     : "=r" (ttbr)
				     :
				     :);
	}

	return ttbr;
}

void set_ttbr(u64 ttbr, s32 idx)
{
	if (0 == idx) {
		__asm__ __volatile__("msr TTBR0_EL1, %0\n\t"\
				     :
				     : "r" (ttbr)
				     :);
	} else if (1 == idx) {
		__asm__ __volatile__("msr TTBR1_EL1, %0\n\t"\
				     :
				     : "r" (ttbr)
				     :);
	}
}

/**
 * API for memory mapping
 */
//Enable mmu, enable i/d cache by setting SCTLR
static void enable_mmu_en_cache()
{
	u64 sctlr = 0;

	sctlr = get_sctlr();
	SET_BITS(sctlr, SCTLR_M_MMU_ENABLE, SCTLR_M_MASK, SCTLR_M_SHIFT);
	SET_BITS(sctlr, SCTLR_I_CACHE_ENABLE, SCTLR_I_MASK, SCTLR_I_SHIFT);
	SET_BITS(sctlr, SCTLR_C_DCACHE_ENABLE, SCTLR_C_MASK, SCTLR_C_SHIFT);
	SET_BITS(sctlr, SCTLR_A_AC_ENABLE, SCTLR_A_MASK, SCTLR_A_SHIFT);
	SET_BITS(sctlr, SCTLR_SA_ENABLE, SCTLR_SA_MASK, SCTLR_SA_SHIFT);
	SET_BITS(sctlr, SCTLR_SA0_ENABLE, SCTLR_SA0_MASK, SCTLR_SA0_SHIFT);
	SET_BITS(sctlr, SCTLR_EE_LITTLE_ENDIAN, SCTLR_EE_MASK, SCTLR_EE_SHIFT);
	SET_BITS(sctlr, SCTLR_WXN_NOT_FORCE_XN, SCTLR_WXN_MASK, SCTLR_WXN_SHIFT);
	set_sctlr(sctlr);
}

//Set system as single address space from 0x0000_0000_0000_0000 to
//0x0000_ffff_ffff_ffff
static void set_single_address()
{
	u64 tcr = 0;

	tcr = get_tcr();
	tcr = TCR_SINGLE_ADDR(tcr);
	set_tcr(tcr);
}

static void set_mair_attr(u32 idx, u8 attr)
{
	u64 mair;

	//Index from 0 to 7
	if (idx > MAIR_ATTR_MAX - 1)
		return;
	
	if (idx > MAIR_IDX_VALID_MAX - 1)
		return;

	if (MAIR_ATTR_MASK & attr)
		return;

	mair = get_mair();
	SET_BITS(mair, attr, MAIR_ATTR_MASK, (idx << MAIR_ATTR_BITS_SHIFT));
	set_mair(mair);
}

static void clr_mair_attr(u32 idx)
{
	u64 mair;

	mair = get_mair();
	SET_BITS(mair, 0, MAIR_ATTR_MASK, (idx << MAIR_ATTR_BITS_SHIFT));
	set_mair(mair);
}

static void init_mair()
{
	int i;

	for (i = 0; i < MAIR_ATTR_MAX; i++) {
		clr_mair_attr(i);
	}
	set_mair_attr(MAIR_NORMAL_IDX, MAIR_NORMAL);
	set_mair_attr(MAIR_DEVICE_IDX, MAIR_DEVICE);
}

static s32 map_memory_l0_table(u64 vaddr, u64 next)
{
	u64 ttbr = (u64)-1;
	u64 entry = 0;
	u64 *entryp = NULL;

	ttbr = get_ttbr(0);
	entryp = (u64*)ttbr;
	SET_BITS(entry, next >> PT_L1_4K_NLT_SHIFT, PT_L1_4K_NLT_MASK, PT_L1_4K_NLT_SHIFT);
	SET_BITS(entry, PT_L1_PT_TYPE_TABLE, PT_L1_PT_TYPE_MASK, PT_L1_PT_TYPE_SHIFT)
	*entryp = entry;
	dsb_sy();
	return 0;
}

static void map_l0()
{
	map_memory_l0_table(0, (u64)ttb_l1);

}

//L1 map only. Single address model
static s32 map_memory_l1_block(u64 vaddr, u64 paddr, u64 size, enum memory_type t)
{
	u64 entry = 0;
	u64 *entryp = NULL;
	u64 addr_idx = (u64)-1;

	if (t > MEMORY_TYPE_MAX - 1)
		return -EINVAL;
	
	if (size > 1024 * 1024 * 1024)
		return -EINVAL;

	addr_idx = vaddr >> PT_L1_4K_OA_SHIFT;
	entryp = (u64*)(ttb_l1 + addr_idx);		//3: each page table is 8bytes(2^3)
	SET_BITS(entry, paddr >> PT_L1_4K_OA_SHIFT, PT_L1_4K_OA_MASK, PT_L1_4K_OA_SHIFT);
	SET_BITS(entry, PT_L1_PT_TYPE_BLOCK, PT_L1_PT_TYPE_MASK, PT_L1_PT_TYPE_SHIFT);
	if (MEMORY_KERNEL == t) {
		SET_BITS(entry, PT_L1_AP_RW_NONE, PT_L1_AP_MASK , PT_L1_AP_SHIFT);
		SET_BITS(entry, PT_L1_AF_1, PT_L1_AF_MASK, PT_L1_AF_SHIFT);
		t = MAIR_NORMAL_IDX;
	} else if (MEMORY_DEVICE == t) {
		SET_BITS(entry, PT_L1_AP_RW_RW, PT_L1_AP_MASK , PT_L1_AP_SHIFT);
		SET_BITS(entry, PT_L1_AF_1, PT_L1_AF_MASK, PT_L1_AF_SHIFT);
		t = MAIR_DEVICE_IDX;
	} else if (MEMORY_USER == t) {
		SET_BITS(entry, PT_L1_AP_RO_RO, PT_L1_AP_MASK , PT_L1_AP_SHIFT);
		t = MAIR_NORMAL_IDX;
	} else if (MEMORY_USER_DATA == t) {
		SET_BITS(entry, PT_L1_AP_RW_RW, PT_L1_AP_MASK , PT_L1_AP_SHIFT);
		t = MAIR_NORMAL_IDX;
	}
	SET_BITS(entry, t, PT_L1_ATTR_INDX_MASK, PT_L1_ATTR_INDX_SHIFT);

	xxk_debug("entry is ");
	xxk_debug_hex64(entry);
	xxk_debug("\n");
	*entryp = entry;
	dsb_sy();
	return 0;
}

static s32 map_memory_l1_block_set_af(u64 vaddr, u32 af)
{
	u64 entry = 0;
	u64 *entryp = NULL;
	u64 addr_idx = (u64)-1;

	addr_idx = vaddr >> PT_L1_4K_OA_SHIFT;
	entryp = (u64*)(ttb_l1 + addr_idx);		//3: each page table is 8bytes(2^3)

	entry = *entryp;
	SET_BITS(entry, (PT_L1_AF_MASK & af), PT_L1_AF_MASK, PT_L1_AF_SHIFT);
	*entryp = entry;
	dsb_sy();
	return 0;
}

static s32 map_memory_flat(u64 addr, u64 size, enum memory_type t)
{
	return map_memory_l1_block(addr, addr, size, t);
}

static s32 map_memory_kernel(u64 addr, u64 size)
{
	return map_memory_flat(addr, size, MEMORY_KERNEL);
}

static s32 map_memory_device(u64 addr, u64 size)
{
	return map_memory_flat(addr, size, MEMORY_DEVICE);
}

static s32 map_memory_user(u64 addr, u64 size)
{
	return map_memory_flat(addr, size, MEMORY_USER);
}

static s32 map_memory_user_data(u64 addr, u64 size)
{
	return map_memory_flat(addr, size, MEMORY_USER_DATA);
}

s32 da_handler(unsigned long esr, struct trap_regs *t)
{
#define ESR_ISS_DA_L_ISV_SHIFT		(24)
#define ESR_ISS_DA_L_ISV_MASK 	  	(1)
#define ESR_ISS_DA_L_SAV_SHIFT		(22)
#define ESR_ISS_DA_L_SAV_MASK 	  	(7)
#define ESR_ISS_DA_L_SAV_BYTE 	  	(0)
#define ESR_ISS_DA_L_SAV_HWORD		(1)
#define ESR_ISS_DA_L_SAV_WORD		(2)
#define ESR_ISS_DA_L_SAV_DWORD		(3)
#define ESR_ISS_DA_L_SRT_SHIFT		(16)
#define ESR_ISS_DA_L_SRT_MASK		(0x1f)
#define ESR_ISS_DA_L_FNV_SHIFT		(16)
#define ESR_ISS_DA_L_FNV_MASK		(0x1)
#define ESR_ISS_DA_L_FNV_VALID		(0x0)
#define ESR_ISS_DA_L_FNV_INVALID	(0x1)
#define ESR_ISS_DA_L_WNR_SHIFT		(6)
#define ESR_ISS_DA_L_WNR_MASK		(1)
#define ESR_ISS_DA_L_WNR_IS_WRITE	(1)
#define ESR_ISS_DA_L_DFSC_SHIFT		(0)
#define ESR_ISS_DA_L_DFSC_MASK		(0x1f)
#define ESR_ISS_DA_L_DFSC_LEVEL_SHIFT	(0)
#define ESR_ISS_DA_L_DFSC_LEVEL_MASK	(3)
#define ESR_ISS_DA_L_DFSC_TYPE_SHIFT	(2)
#define ESR_ISS_DA_L_DFSC_ADDR_SIZE	(0)
#define ESR_ISS_DA_L_DFSC_TRANS		(1)
#define ESR_ISS_DA_L_DFSC_AF		(2)
#define ESR_ISS_DA_L_DFSC_PERMISSION	(3)
#define ESR_ISS_DA_L_DFSC_TYPE_MASK	(3)

	u32 isv;
	u32 sas;
	u32 srt;
	u32 far_is_not_valid;
	u64 far;
	u32 is_write;
	u32 dfsc;
	u32 dfsc_level;
	u32 dfsc_type;
	s32 is_handled = 0;

	xxk_debug("Data abort from lower exception\n");
	GET_BITS(esr, isv, ESR_ISS_DA_L_ISV_MASK, ESR_ISS_DA_L_ISV_SHIFT);
	if (1 == isv) {
		xxk_debug("valid instruction syndrome\n");
		GET_BITS(esr, sas, ESR_ISS_DA_L_SAV_MASK, ESR_ISS_DA_L_SAV_SHIFT);
		switch(sas) {
		case ESR_ISS_DA_L_SAV_BYTE:
			xxk_debug("access is byte\n");
			break;
		case ESR_ISS_DA_L_SAV_HWORD:
			xxk_debug("access is half word\n");
			break;
		case ESR_ISS_DA_L_SAV_WORD:
			xxk_debug("access is word\n");
			break;
		case ESR_ISS_DA_L_SAV_DWORD:
			xxk_debug("access is double word\n");
			break;
		default:
			{;}//error handling stub
			break;
		}
		GET_BITS(esr, srt, ESR_ISS_DA_L_SRT_MASK, ESR_ISS_DA_L_SRT_SHIFT);
		xxk_debug("fault register is 0x");
		xxk_debug_hex64(srt);
		xxk_debug("\n");
	}
	GET_BITS(esr, far_is_not_valid, ESR_ISS_DA_L_FNV_MASK, ESR_ISS_DA_L_FNV_SHIFT);
	if (ESR_ISS_DA_L_FNV_INVALID == far_is_not_valid) {
		xxk_debug("fault address is invalid\n");
	} else {
		xxk_debug("fault address is valid ");
		far = get_far();
		xxk_debug_hex32(far);
		xxk_debug("\n");
	}
	GET_BITS(esr, is_write, ESR_ISS_DA_L_WNR_MASK, ESR_ISS_DA_L_WNR_SHIFT);
	if (ESR_ISS_DA_L_WNR_IS_WRITE == is_write)
		xxk_debug("fault by writing\n");
	else
		xxk_debug("fault by reading\n");

	GET_BITS(esr, dfsc, ESR_ISS_DA_L_DFSC_MASK, ESR_ISS_DA_L_DFSC_SHIFT);
	GET_BITS(esr, dfsc_level, ESR_ISS_DA_L_DFSC_LEVEL_MASK, ESR_ISS_DA_L_DFSC_LEVEL_SHIFT);
	GET_BITS(esr, dfsc_type, ESR_ISS_DA_L_DFSC_TYPE_MASK, ESR_ISS_DA_L_DFSC_TYPE_SHIFT);
	xxk_debug("CAUTION: may some level is not actually exist\n");
	xxk_debug("dfsc: 0x");
	xxk_print_hex32(dfsc);
	xxk_debug(", type: ");
	switch (dfsc_type){
	case ESR_ISS_DA_L_DFSC_ADDR_SIZE:
		xxk_debug("address size fault");
		break;
	case ESR_ISS_DA_L_DFSC_TRANS:
		xxk_debug("translation fault");
		break;
	case ESR_ISS_DA_L_DFSC_AF:
		xxk_debug("access flag fault, enable it by setting af=1");
		map_memory_l1_block_set_af(far, PT_L1_AF_1);
		is_handled = 1;
		break;
	case ESR_ISS_DA_L_DFSC_PERMISSION:
		xxk_debug("permission fault");
		break;
	default:
		{;}//error handling stub
		break;
	}
	xxk_debug(", level: ");
	xxk_debug_hex32(dfsc_level);
	xxk_debug("\n");
	return is_handled;
}

s32 ia_handler(unsigned long esr, struct trap_regs *t)
{
#define ESR_ISS_IA_L_FNV_SHIFT		(10)
#define ESR_ISS_IA_L_FNV_MASK		(0x1f)
#define ESR_ISS_IA_L_FNV_VALID		(0x0)
#define ESR_ISS_IA_L_FNV_INVALID	(0x1)
#define ESR_ISS_IA_L_IFSC_SHIFT		(0)
#define ESR_ISS_IA_L_IFSC_MASK		(0x1f)
#define ESR_ISS_IA_L_IFSC_LEVEL_SHIFT	(0)
#define ESR_ISS_IA_L_IFSC_LEVEL_MASK	(3)
#define ESR_ISS_IA_L_IFSC_TYPE_SHIFT	(2)
#define ESR_ISS_IA_L_IFSC_ADDR_SIZE	(0)
#define ESR_ISS_IA_L_IFSC_TRANS		(1)
#define ESR_ISS_IA_L_IFSC_AF		(2)
#define ESR_ISS_IA_L_IFSC_PERMISSION	(3)
#define ESR_ISS_IA_L_IFSC_TYPE_MASK	(3)

	u32 far_is_not_valid;
	u64 far;
	u32 ifsc;
	u32 ifsc_level;
	u32 ifsc_type;
	s32 is_handled = 0;

	xxk_debug("Instruction abort from lower exception\n");
	GET_BITS(esr, far_is_not_valid, ESR_ISS_IA_L_FNV_MASK, ESR_ISS_IA_L_FNV_SHIFT);
	if (ESR_ISS_IA_L_FNV_INVALID == far_is_not_valid) {
		xxk_debug("fault address is invalid\n");
	} else {
		xxk_debug("fault address is valid ");
		far = get_far();
		xxk_debug_hex64(far);
		xxk_debug("\n");
	}
	GET_BITS(esr, ifsc, ESR_ISS_IA_L_IFSC_MASK, ESR_ISS_IA_L_IFSC_SHIFT);
	GET_BITS(esr, ifsc_level, ESR_ISS_IA_L_IFSC_LEVEL_MASK, ESR_ISS_IA_L_IFSC_LEVEL_SHIFT);
	GET_BITS(esr, ifsc_type, ESR_ISS_IA_L_IFSC_TYPE_MASK, ESR_ISS_IA_L_IFSC_TYPE_SHIFT);
	xxk_debug("CAUTION: may some level is not actually exist\n");
	xxk_debug("ifsc: 0x");
	xxk_print_hex32(ifsc);
	xxk_debug(", type: ");
	switch (ifsc_type){
	case ESR_ISS_IA_L_IFSC_ADDR_SIZE:
		xxk_debug("address size fault");
		break;
	case ESR_ISS_IA_L_IFSC_TRANS:
		xxk_debug("translation fault");
		break;
	case ESR_ISS_IA_L_IFSC_AF:
		xxk_debug("access flag fault, enable it by setting af=1");
		map_memory_l1_block_set_af(far, PT_L1_AF_1);
		is_handled = 1;
		break;
	case ESR_ISS_IA_L_IFSC_PERMISSION:
		xxk_debug("permission fault");
		break;
	default:
		{;}//error handling stub
		break;
	}
	xxk_debug(", level: ");
	xxk_debug_hex32(ifsc_level);
	xxk_debug("\n");
	return is_handled;
}

//page size: x86 4k; ARM64 4k, 16k, 64k; For now, Xuxiake choose 1G page which is L1
//permission: Read, Write, eXecution; exception level accessable; cacheable; memory type
//init flow: indentical mapping;
//cost vs performance
void mmu_init()
{
	int ret = -1;

	xxk_print("XXK: MMU initing\n");
	set_ttbr((u64)ttbr0_el1, 0);
	init_mair();
	map_l0();
	ret = map_memory_kernel(PHY_OFFSET, PHY_SIZE);
	if (ret < 0)
		return;

	ret = map_memory_device(DEV_PL011_OFFSET, DEV_PL011_SIZE);
	if (ret < 0)
		return;

	ret = map_memory_user(USER_MEM_START, USER_DATA_START - USER_MEM_START);
	if (ret < 0)
		return;

	ret = map_memory_user_data(USER_DATA_START, USER_STACK_SIZE);
	if (ret < 0)
		return;

	set_single_address();
	enable_mmu_en_cache();
	dsb_sy();
	xxk_print("XXK: MMU init done\n");
}
#else
void mmu_init() {;}
#endif /* #ifdef CONFIG_MMU */
