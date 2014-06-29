
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 1024

static OS_STK stk1[STK_LEN];
static OS_STK stk2[STK_LEN];
static OS_STK stk3[STK_LEN];

static void test_task1(void* p_arg)
{
	p_arg = p_arg;

	while(1) {

		printk("a ");
		OSTimeDly(5);
	}
}

static void test_task2(void* p_arg)
{
	p_arg = p_arg;

	while(1) {

		printk("b ");
		OSTimeDly(2);

	}
}

static void test_task3(void* p_arg)
{
	p_arg = p_arg;

	while(1) {

		printk("c ");
		OSTimeDly(4);

	}
}

void test_task()
{
	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

	OSTaskCreate( test_task2, 0, &stk2[STK_LEN -1], 6);
	
	OSTaskCreate( test_task3, 0, &stk3[STK_LEN -1], 3);

}




