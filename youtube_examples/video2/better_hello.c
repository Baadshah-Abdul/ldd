#include <linux/module.h>
#include <linux/init.h>

//meta data
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABDUL");
MODULE_DESCRIPTION("Better version of module written in video2 dir");

//entry function
static int __init my_init(void)
{
	printk("Assalamualaikum - Hello, Kernel\n");
	return 0;
}

//exit function
static void __exit my_exit(void)
{
	printk("Goodbye, Kernel\n");
}

module_init(my_init);
module_exit(my_exit);

