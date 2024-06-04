
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

#include "driver.c"

unsigned int major;
const unsigned int minor = 1;
const char *device_name = "scdrv";

struct cdev scdrv_cdev;

dev_t dev;
size_t buffer_size = 1024;
    
int mod_init(void)
{
    printk(KERN_INFO "Initializing scdrv module\n");

    int rv = alloc_chrdev_region(&dev, 1, minor, device_name);
    major = MAJOR(dev);

    drv = scdrv_init(buffer_size);
    if (rv < 0)
    {
        printk("%s failed with %d\n", "Registering driver", rv);
        return rv;
    }

    cdev_init(&scdrv_cdev, &fops);
    scdrv_cdev.owner = THIS_MODULE;

    rv = cdev_add(&scdrv_cdev, dev, 1);
    if (rv < 0)
    {
        printk(KERN_ERR "Failed to add character device\n");
        unregister_chrdev_region(dev, 1);
        return rv;
    }
    return 0;
}

void mod_close(void)
{
    printk(KERN_INFO "Exiting scdrv module\n");
    cdev_del(&scdrv_cdev);
    unregister_chrdev_region(MKDEV(MAJOR(dev), MINOR(dev)), 1);
}



module_init(mod_init);
module_exit(mod_close);
// module_param(buffer_size, __u16, S_IRUGO);

MODULE_AUTHOR("Bogdan Bescherepov");
MODULE_DESCRIPTION("Simple char driver");
MODULE_LICENSE("GPL v2");
MODULE_PARM_DESC(buffer_size, "Buffer size");
