// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <asm/spinlock.h>

#define NUM_OF_THREADS 2

struct atomic_args {
	int nr;		/* the sequence number os thread */
};

struct atomic_args atomic_args_array[NUM_OF_THREADS];
struct task_struct *atomic_threads[NUM_OF_THREADS];

static DEFINE_SPINLOCK(atomic_op);

#define CONFIG_SMP
/**
 * From linux/arch/riscv/include/asm/fence.h
 */
#ifdef CONFIG_SMP
#define RISCV_ACQUIRE_BARRIER		"\tfence r , rw\n"
#define RISCV_RELEASE_BARRIER		"\tfence rw,  w\n"
#else
#define RISCV_ACQUIRE_BARRIER
#define RISCV_RELEASE_BARRIER
#endif
/**
 * From linux/arch/riscv/include/asm/fence.h end
 */

typedef struct {
	volatile unsigned int lock;
} xxk_arch_spinlock_t;

/**
 * OutputOperands:
 * r A register operand is allowed provided that it is in a general register.
 * https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html#Simple-Constraints
 * A An address that is held in a general-purpose register.
 * https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html#Machine-Constraints
 * = Means that this operand is written to by this instruction: the previous value is discarded and replaced by new data.
 * https://gcc.gnu.org/onlinedocs/gcc/Modifiers.html#Modifiers
 */
static inline int xxk_arch_spin_trylock(xxk_arch_spinlock_t *lock)
{
	int tmp = 1, busy;

	__asm__ __volatile__ (
		"	amoswap.w %0, %2, %1\n"
		RISCV_ACQUIRE_BARRIER
		: "=r" (busy), "+A" (lock->lock)
		: "r" (tmp)
		: "memory");

	return !busy;
}
static int atomic_test(void *arg)
{
	struct atomic_args *th = (struct atomic_args*)arg;
	pr_info("thread %d\n", th->nr);

	set_current_state(TASK_INTERRUPTIBLE);
	while (!kthread_should_stop()) {
		arch_spin_lock(&atomic_op.rlock.raw_lock);
		pr_info("thread %d get lock\n", th->nr);
		arch_spin_unlock(&atomic_op.rlock.raw_lock);
		usleep_range(1000000, 1000001);
	}
	__set_current_state(TASK_RUNNING);

	return 0;
}


static int __init atomic_init(void)
{
	int i;
	int ret;

	pr_info("hello %s\n", __func__);

	for (i = 0; i< NUM_OF_THREADS; i++) {
		atomic_args_array[i].nr = i;
		atomic_threads[i] = kthread_create(atomic_test,
						   (void*)(&atomic_args_array[i]),
						   "atomic_test_%d",
						   atomic_args_array[i].nr);
		if (IS_ERR(atomic_threads[i])) {
			pr_err("atomic test thread %d create failed\n",
			       atomic_args_array[i].nr);
			ret = -1;
			goto exit;
		}
		wake_up_process(atomic_threads[i]);
	}

	ret = 0;
exit:
	return ret;
}

static void __exit atomic_exit(void)
{
	int i;

	for (i = 0; i< NUM_OF_THREADS; i++) {
		kthread_stop(atomic_threads[i]);
	}
	pr_info("byebye %s\n", __func__);
}

module_init(atomic_init);
module_exit(atomic_exit);
MODULE_LICENSE("GPL");
