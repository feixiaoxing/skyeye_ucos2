
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 2048

static OS_STK stk1[STK_LEN];

static OS_STK stk2[STK_LEN];

static OS_EVENT* p_sem;

static void test_task1(void* p_arg)
{
	INT8U err;

	p_arg = p_arg;

	while(1) {
		
		OSSemPend(p_sem, 0, &err);

		printk("get ");
		OSTimeDly(5);
	}
}

static void test_task2(void* p_arg)
{
	p_arg = p_arg;

	while(1) {

		OSSemPost(p_sem);

		printk("give ");
		OSTimeDly(10);
	}
}



void test_sem()
{
	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	p_sem = OSSemCreate(2); 

	if(0 == p_sem) {
	
		printk("error in OSSemCreate\n");
	}

	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

	OSTaskCreate( test_task2, 0, &stk2[STK_LEN -1], 6);
	

}




