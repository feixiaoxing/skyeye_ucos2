
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 2048

static OS_STK stk1[STK_LEN];
static OS_STK stk2[STK_LEN];

static OS_EVENT* p_mutex;

static void test_task1(void* p_arg)
{
	INT8U err;

	p_arg = p_arg;

	while(1) {
		
		OSMutexPend(p_mutex, 0, &err);

		printk("consume ");
		OSTimeDly(5);
	}
}

static void test_task2(void* p_arg)
{
	p_arg = p_arg;

	while(1) {

		OSMutexPost(p_mutex);

		printk("produce ");
		OSTimeDly(10);
	}
}



void test_mutex()
{
	INT8U err;

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	p_mutex = OSMutexCreate(4, &err); 

	if(0 == p_mutex) {
	
		printk("error in OSMutexCreate\n");
	}

	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

	OSTaskCreate( test_task2, 0, &stk2[STK_LEN -1], 6);
	

}




