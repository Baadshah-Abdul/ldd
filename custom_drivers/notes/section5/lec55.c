LECTURE 55: pcd drivers with multiple devices

Structure to represent device's private data:


/*This structure represents device private data*/

	struct pcdev_private_data
	{
		char *buffer;	//pointer to start address
		unsigned size;
		const char *serial_number;
		int perm;	//permission
		struct cdev cdev;	//data structure - character device
	};
	
/* DEFINED in <linux/cdev.h>

    struct cdev {
  	struct kobject kobj;          // Embedded kernel object
    	struct module *owner;         // Pointer to module owning this device
    	const struct file_operations *ops; // File operations for this device
	struct list_head list;        // Linked list of devices
   	dev_t dev;                    // Device number (major/minor)
   	unsigned int count;           // Number of minor numbers
};
 */
 
 
 Structure to represent driver's private data
 
 /*this structure represents driver private data*/
 struct pcdev_private_data 
 {
 	int total_devices;
 	struct pcdev_privata_data pcddev_data[NO_OF_DEVICES];
 };
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
