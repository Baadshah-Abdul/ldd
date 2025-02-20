#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

static int example_init(void)
{
	printk(KERN_ALERT "Hello, first DIY\n");
	return 0;
}

static void example_exit(void)
{
	printk(KERN_ALERT "Allah Hafiz \nwe'll meet again In Sha Allah");
}
module_init(example_init);
module_exit(example_exit);
