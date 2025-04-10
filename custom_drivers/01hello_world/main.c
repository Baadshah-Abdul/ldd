#include <linux/module.h>


static int __init hello_init(void){
	printk("Hello, World!\n");
	return 0;
}

static void __exit hello_cleanup(void){
	pr_info("Goodbye\n");

}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdul");
MODULE_DESCRIPTION("hello world module");
