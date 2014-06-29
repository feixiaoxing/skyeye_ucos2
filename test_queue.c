
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 2048
#define QUEUE_SIZE 5

static OS_STK stk1[STK_LEN];
static OS_STK stk2[STK_LEN];

static OS_EVENT* p_queue = 0;

static void* queue[QUEUE_SIZE] = {0};

static INT32U data = 0;

static void test_task1(void* p_arg)
{

	p_arg = p_arg;

	while(1) {

		while(OS_NO_ERR != OSQPost(p_queue, (void*)(data))){

			OSTimeDly(5);
		}

		printk("give %d ", data);
		data ++;
	}
}

static void test_task2(void* p_arg)
{
	INT8U err;
	INT32U val;

	p_arg = p_arg;

	while(1) {
		
		val = (INT32U) OSQPend(p_queue, 0, &err);

		printk("get %d ", val);
		OSTimeDly(50);
	}
}


void test_q()
{
	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	p_queue = OSQCreate(queue, QUEUE_SIZE); 

	if(0 == p_queue) {
	
		printk("error in OSQCreate\n");
	}

	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

	OSTaskCreate( test_task2, 0, &stk2[STK_LEN -1], 6);
	

}




