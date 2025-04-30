obj-m += pcd_multi.o
KERN_DIR=$(HOME)/linux-rpi
ARCH = arm64
CROSS_COMPILE = aarch64-linux-gnu-


all:	
	make -C $(KERN_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	
	
clean:		
	make -C $(KERN_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean


help:
	make -C $(KERN_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) help


host:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
