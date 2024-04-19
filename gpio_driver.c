#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#define DEVICE_NAME "gpio_driver"
#define CLASS_NAME "gpio"

static int majorNumber;
static struct class* gpioDriverClass = NULL;
static struct device* gpioDriverDevice = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
    .open = dev_open,
    .write = dev_write,
    .release = dev_release,
};

static int __init gpio_driver_init(void){
    printk(KERN_INFO "GPIO_Driver: Initializing the GPIO_Driver LKM\n");

    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber<0){
        printk(KERN_ALERT "GPIO_Driver failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "GPIO_Driver: registered correctly with major number %d\n", majorNumber);

    gpioDriverClass = class_create(CLASS_NAME);
    if (IS_ERR(gpioDriverClass)){
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(gpioDriverClass);
    }
    printk(KERN_INFO "GPIO_Driver: device class registered correctly\n");

    gpioDriverDevice = device_create(gpioDriverClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(gpioDriverDevice)){
        class_destroy(gpioDriverClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(gpioDriverDevice);
    }
    printk(KERN_INFO "GPIO_Driver: device class created correctly\n");
    return 0;
}

static void __exit gpio_driver_exit(void){
    device_destroy(gpioDriverClass, MKDEV(majorNumber, 0));
    class_unregister(gpioDriverClass);
    class_destroy(gpioDriverClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "GPIO_Driver: Goodbye from the LKM!\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "GPIO_Driver: Device has been opened\n");
    return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    printk(KERN_INFO "GPIO_Driver: Received %zu characters from the user\n", len);
    return len;
}

static int dev_release(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "GPIO_Driver: Device successfully closed\n");
    return 0;
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bill Wang");
MODULE_DESCRIPTION("A simple Linux GPIO driver for the Raspberry Pi");
MODULE_VERSION("0.1");
