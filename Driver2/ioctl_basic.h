#include <linux/ioctl.h>
#define IOC_MAGIC k // defines the magic number

#define IOCTL_HELLO _IO(IOC_MAGIC,0) // defines our ioctl call
