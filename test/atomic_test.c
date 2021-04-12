// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/kthread.h>

#define NUM_OF_THREADS 2

struct atomic_args {
	spinlock_t lock;
	int nr;		/* the sequence number os thread */
};

struct atomic_args atomic_args_array[NUM_OF_THREADS];
struct task_struct *atomic_threads[NUM_OF_THREADS];

static int atomic_test(void *arg)
{
	struct atomic_args *th = (struct atomic_args*)arg;
	pr_info("thread %d\n", th->nr);

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

	pr_info("byebye %s\n", __func__);
}

module_init(atomic_init);
module_exit(atomic_exit);
MODULE_LICENSE("GPL");
