#include <linux/init.h>
#include <linux/module.h>

#ifndef PFX
#define PFX "simple: "
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebastian Parschauer <s.parschauer@gmx.de>");
MODULE_DESCRIPTION("Simple kernel module");

static __init int init_simple(void)
{
	pr_info(PFX "init\n");
	return 0;
}

static __exit void cleanup_simple(void)
{
	pr_info(PFX "cleanup\n");
}

module_init(init_simple);
module_exit(cleanup_simple);
