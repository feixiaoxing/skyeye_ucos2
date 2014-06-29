
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 256

static OS_STK stk1[STK_LEN];

static OS_MEM* p_mem;

static INT8U buffer[1024];


static void test_task1(void* p_arg)
{
	INT8U err;
	void* p_data;
	INT8U count;

	count = 0;

	p_arg = p_arg;

	while(1) {
	
		p_data = OSMemGet(p_mem, &err);	
		
		if(0 != p_data) {

			count ++;

			printk("get %d block memory\n", count);
		}else {

			printk("no memory now\n");
		}

		OSTimeDly(15);
	}
}


void test_m()
{
	INT8U err;

	INT8U* p_addr;

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	/* make address align with sizeof(void*) */

	p_addr = &buffer[0];

	if((INT32U)p_addr & 0x3) {
		
		p_addr =(INT8U*) (((INT32U)p_addr & 0xfffffffc) + 4);
	}
	
	p_mem = OSMemCreate(p_addr,  /* start address */
				30,  /* block number */
				32,  /* block size*/
				&err /* error point  */
			);

	if(0 == p_mem) {

		printk("error in OSMemCreate \n");
	}


	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

}




