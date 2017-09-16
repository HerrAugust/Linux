/*
 * Hello world with parameters.
 * Usage: make && sudo insmod helloworld_with_params.ko times=5 mystring="this is the string" myarray=9,8 && cat /var/log/kern.log
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h> /* Permissions */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("GitHub: HerrAugust");

static int times = -1;
static char* mystring = "";
static int myarray[2] = { -1, -1 };
static int count = -1;
module_param(times, int, S_IRUGO);
module_param(mystring, charp, S_IRUGO);
/* module_param_array(name, type, num, perm); where num is set to the number of values supplied. */
module_param_array(myarray, int, &count, 0);

static int hello_init(void)
{
    int i = 0;
    printk(KERN_ALERT "Hello, world\n");
    printk(KERN_INFO  "Mystring is %s\n", mystring);
    printk(KERN_INFO  "Times is %d\n", times);
    for(i = 0; i < count; i++) {
    	printk(KERN_INFO "Array at position %d is %d\n", i, myarray[i]);
    }
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);