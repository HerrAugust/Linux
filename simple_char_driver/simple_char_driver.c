#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h> // copy_to_user and copy_from_user

// -------------------------------------------
// -------------Summary:----------------------
// A Character Driver transfers streams of data
// from and to the user (where there is no filesystem).
// E.g., audio and video devices,
// serial ports. Thus, you have to define:
// 1. Module information
// 2. init and exit functions
// 		2.1. get major & minor numbers
//		2.2. register driver (i.e., make the kernel know about it)
// 3. File operations (open, read, write, close)
// -------------------------------------------


// -----------Module information:-------------
MODULE_LICENSE("GPL");
MODULE_AUTHOR("GitHub: HerrAugust");
MODULE_DESCRIPTION("Simple Char Driver");

//--------END Module information--------------


// Information about the driver. Used on exit.
static dev_t device;
static struct cdev mycdev;


// -----------File operations:----------------

// The string received from the user (main.c)
static char user_string[255] = "Nothing here...:( ";



static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "SimpleCharDriver.open()\n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "SimpleCharDriver.close()\n");
	return 0;
}

/*  @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 */
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	int res = -1;
  	printk(KERN_INFO "SimpleCharDriver.read()\n");

  	// I write a simple string, as if it was read from the real device. Check it with cat /dev/SimpleCharDriver
  	res = copy_to_user(buf, user_string, strlen(user_string));
  	if(res != 0)
  		return -res;
  	printk(KERN_INFO "Replied.\n");
  	memset(user_string, 0, 255);


  	return 0;
}

/** @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 */
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	  int res = 0;
	  printk(KERN_INFO "SimpleCharDriver.write()\n");

	  // unsigned long copy_from_user(void * to, const void __user * from, unsigned long n);
	  res = copy_from_user(user_string, buf, sizeof(user_string));
	  if(res != 0)
		  return -res;
	  printk(KERN_INFO "Received: %s\n", user_string);

	  return len;
}

// Note: in the following structure, some methods default to a standard implementation.
// E.g., ioctl() is not implemented and, in fact, it misses!
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

// ---------END File operations---------------


// -----------Init & Exit functions-----------

static int init(void)
{
	int res = -1;
    printk(KERN_ALERT "SimpleCharDriver.init()\n");

    // Allocating major and minor numbers
    res = alloc_chrdev_region(&device, 0, 1, "SimpleCharDriver"); // output: device
    if(res < 0) return -1;
    printk(KERN_INFO "MAJOR=%d and MINOR=0\n", MAJOR(device));

    // Char driver registration (s.t. the Kernel knows about this module):
    cdev_init(&mycdev, &fops);
    res = cdev_add(&mycdev, device, 1);
    if(res < 0) return -1;
    printk(KERN_INFO "Device registered.\n");

    // Device creation:
    // Note: if you do not declare them, the functions above won't be called and the device will not stay in /dev!
    // Open Terminal and: sudo mknod /dev/SimpleCharDriver -c YOUR_MAJOR YOUR_MINOR

    return 0;
}
	
static void myexit(void)
{
    printk(KERN_ALERT "SimpleCharDriver.myexit()\n");
    unregister_chrdev_region(device, 1);
    cdev_del(&mycdev);
} 
module_init(init);
module_exit(myexit);

// -------END Init & Exit functions-----------
