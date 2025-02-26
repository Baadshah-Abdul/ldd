/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 */                                                    
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <asm/current.h>
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Abdul");
MODULE_DESCRIPTION("learning linux device drivers");

static int hello_init(void)
{
	printk (KERN_ALERT "Hello, world\n %s function\n",__FUNCTION__);
	//it prints the command name andd the process id
	printk(KERN_INFO "the process is \"%s\"(pid %i)\n", current->comm,
		current->pid);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
	//it prints the command name and the process id
 	printk(KERN_INFO "the process is \"%s\"(pid %i)\n", current -> comm, current -> pid);	
}

module_init(hello_init);
module_exit(hello_exit);
