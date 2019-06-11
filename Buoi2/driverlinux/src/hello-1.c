/*  
 *  hello-1.c - The simplest kernel module.
 */
#include "../module/hello-1.h"

#ifndef __hello_1__
#define __hello_1__



int init_module(void)
{
	printk(KERN_INFO "Hello world 1.\n");

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}

#endif
