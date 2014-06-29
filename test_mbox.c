
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 2048

static OS_STK stk1[STK_LEN];
static OS_STK stk2[STK_LEN];

static OS_EVENT* p_mbox;

static INT32U data = 0;

static void test_task1(void* p_arg)
{
	INT8U err;
	INT32U* p_data;

	p_arg = p_arg;

	while(1) {
		
		p_data = (INT32U*) OSMboxPend(p_mbox, 0, &err);

		printk("receive %d ", *p_data);
		OSTimeDly(5);
	}
}

static void test_task2(void* p_arg)
{
	p_arg = p_arg;

	while(1) {

		data += 1;
		printk("send %d ", data);
		
		OSMboxPost(p_mbox, &data);
		OSTimeDly(10);
	}
}



void test_mbox()
{
	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	p_mbox = OSMboxCreate(0); 

	if(0 == p_mbox) {
	
		printk("error in OSMboxCreate\n");
	}

	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

	OSTaskCreate( test_task2, 0, &stk2[STK_LEN -1], 6);
	

}




