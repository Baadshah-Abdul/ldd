#include <linux/module.h>
#include <linux/init.h>

int enter_init(void)
{
	printk("Assalamualikum reader!!\n");
	return 0;
}

void leave_exit(void)
{
	printk(KERN_ALERT "It was nice knowing you\n");
}
module_init(enter_init);
module_exit(leave_exit);

MODULE_LICENSE("GPL");
