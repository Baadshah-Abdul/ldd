#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>

//change printk format to include function name
#undef pr_fmt
#define pr_fmt(fmt) "%s :" fmt,__func__

//this acts as device memory buffer/storage
#define DEV_MEM_SIZE 512

static char device_buffer[DEV_MEM_SIZE]; //device memory buffer
static dev_t device_number; //stores major and minor number
static struct cdev pcd_cdev; //pointer to device class
static struct  class *class_pcd; //pointer to deviced class
static struct device *device_pcd; //pointer to device instance


/*lseek: llseek file operation*/
static loff_t pcd_lseek(struct file *filp, loff_t offset, int whence)
{
	loff_t temp;

	pr_info("lseek requested\n");
	pr_info("current value of file position = %lld\n", filp->f_pos);

	switch(whence)
	{
		case SEEK_SET://set positon to offset from start
			if ((offset > DEV_MEM_SIZE) || (offset < 0))
				return -EINVAL;
			filp->f_pos = offset;
			break;
		case SEEK_CUR://adjust position by offset from current
			temp = filp->f_pos + offset;
			if ((temp > DEV_MEM_SIZE) || (temp < 0))
				return -EINVAL;
			filp->f_pos = temp;
			break;
		case SEEK_END://set position to offset from end
			temp = DEV_MEM_SIZE + offset;
			if ((temp > DEV_MEM_SIZE) || (temp < 0))
				return -EINVAL;
			filp->f_pos = temp;
			break;
		default:
			return -EINVAL;
	}
	pr_info("New valuse of file position = %lld\n", filp->f_pos);
	return filp->f_pos;
}


/*read: read file operation*/
ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)

{
	pr_info("read requested for %zu bytes\n", count);
	pr_info("current file position %lld\n", *f_pos);
	
	//adjjust count if it will read past device memory
	if((*f_pos + count) > DEV_MEM_SIZE)
		count = DEV_MEM_SIZE - *f_pos;

	//copy data from kernel buffer to user space
	if(copy_to_user(buff, &device_buffer[*f_pos], count))
		return -EFAULT;//return error i dcopy fail

	//Update file position
	*f_pos += count;

	pr_info("Number of bytes read successfully  = %zu\n", count);
	pr_info("Update file positon = %lld\n", *f_pos);
	
	return count;//number of bytes read
}


/*write file operation*/
ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("write requested for = %zu\n", count);
	pr_info("current file position = %lld\n", *f_pos);

	//adjust count if it will write past device memory
	if ((*f_pos + count ) > DEV_MEM_SIZE)
		count = DEV_MEM_SIZE - *f_pos;

	//check if thers is space left
	if(!count)
	{
		pr_info("NO space left in device memory\n");
		return -ENOMEM;
	}

	//copy data from user to keernel space
	if(copy_from_user(&device_buffer[*f_pos], buff, count))
			return -EFAULT;//failed to copy from the user

	//update file position
	*f_pos +=count;

	pr_info("Number of bytes written successfully = %zu\n", count);
	pr_info("Curren tfile position =  %lld\n", *f_pos);

	return count;//written bytes
}


/*open file operation*/
static int pcd_open(struct inode *inode, struct file *filp)
{
	pr_info("Open was successfull!\n");
	return 0;
}


/*release file operation*/
static int pcd_release(struct inode *inode, struct file *filp)
{
	pr_info("Release was successful!\n");
	return 0;
}


/*file operations structure - links functions to system caaaaalls*/
static struct file_operations pcd_fops = {
	.open = pcd_open, 
	.read = pcd_read,
	.write = pcd_write,
	.llseek = pcd_lseek,
	.release = pcd_release,
	.owner = THIS_MODULE //prevents unloading of module when in use
};


/*Module initialization function*/
static int __init pcd_driver_init(void)
{
	int ret;
	//1 dynamically allocate a device number (major and mino)
	ret = alloc_chrdev_region(&device_number, 0, 1, "pseudo_chr_devices");
	if(ret < 0)
	{
		pr_err("alloc_chardev_region() failed!\n");
		goto out;
	}
	pr_info("Device numer <major>:<minor> = %d:%d\n", MAJOR(device_number), MINOR(device_number));

	//2 initialize hte cdev structure with file operations
	cdev_init(&pcd_cdev,  &pcd_fops);
	pcd_cdev.owner = THIS_MODULE;

	//3 add character devices to the systeeem
	ret = cdev_add(&pcd_cdev,device_number, 1);
	if(ret < 0)
	{
		pr_err("cdev_add() failed!\n");
			goto unreg_chrdev;
	}

	//4 create device class (/sys/class)
	class_pcd = class_create("pseudo_chr_dev_class");
	if(IS_ERR(class_pcd))
	{
		pr_err("class_create() ffffailed!\n");
		ret = PTR_ERR(class_pcd);
		goto cdev_del;
	}

	//5 create device node (/dev/)
	device_pcd = device_create(class_pcd, NULL, device_number, NULL, "pseudo_chr_dev");
	if(IS_ERR(device_pcd))
	{
		pr_err("device_create() failed!\n");
		ret = PTR_ERR(device_pcd);
		goto class_del;
	}

	pr_info("Module init suucessfull!\n");
	return 0;

/*Error handling*/
class_del:
	class_destroy(class_pcd);
cdev_del:
	cdev_del(&pcd_cdev);
unreg_chrdev:
	unregister_chrdev_region(device_number, 1);
out: 
	pr_err("Module insertion failed!\n");
	return ret;
}


/*Module cleanup funtion*/
static void __exit pcd_driver_cleanup(void)
{
	device_destroy(class_pcd, device_number);
	class_destroy(class_pcd);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(device_number, 1);
	pr_info("Module Unloaded\n");
}

/*initialization and cleanup function*/
module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);


/*Metaadata*/
MODULE_DESCRIPTION("Pseudo character device");
MODULE_AUTHOR("Abdul Haque");
MODULE_LICENSE("GPL");





