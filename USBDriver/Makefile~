obj-m := USBDriver.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *-
