#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ahmed Adel Wafdy");
MODULE_DESCRIPTION("A hello world LKM");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	pr_info("Hello,Wafdunix Sicky Micky Kernel\n");
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit my_exit(void) {
	pr_info("Goodbye,Wafdunix Sicky Micky Kernel\n");
}

module_init(my_init);
module_exit(my_exit);
