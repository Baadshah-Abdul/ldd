#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

//meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdul");
MODULE_DESCRIPTION("Registers device nuber and implement some callback functions");

//@brief This function, when the device file is opened
static int driver_open(struct inode *device_file, struct file *instance){
	printk("dev_nr - open was called\n");
	return 0;
}

//brief This function was called, when the device file is closed
static int driver_close(struct inode *device_file, struct file *intance){
	printk("dev_nr - closed was called\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
};


#define MYMAJOR 64


//@brief This function is called, when the module is loaded into the kernel
static int __init ModuleInit(void){
	int retval;
	printk("Hello, Kernel\n");
	
	//register device number
		
	retval = register_chrdev(MYMAJOR, "dev_nr", &fops);
	if(retval == 0){
		printk("dev_nr - registerd Device number Magor : %d, Minor : %d\n", MYMAJOR, 0);
	}
	else if(retval > 0){
		 printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}	 
	else{
		printk("Could not register Device number!\n");
		return -1;
	}
	return 0;

}

//@brief This function is called, when the module is removed fro the kernel
static void __exit ModuleExit(void){
	unregister_chrdev(MYMAJOR, "dev_nr");
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

