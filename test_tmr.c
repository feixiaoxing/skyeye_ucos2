
#include "ucos_ii.h"

extern int test_switch;

#define STK_LEN 2048

static OS_STK stk1[STK_LEN];

static OS_TMR* p_tmr;

static void timer_func(void* tmr, void* arg)
{
	static INT32U data = 0;

	printk("%d ", data ++);

}

static void test_task1(void* p_arg)
{
	INT8U err;

	p_arg = p_arg;

	if(OS_FALSE == OSTmrStart(p_tmr, &err)) {

		printk("error in OSTmrStart");
	}

	while(1) {
	
		OSTimeDly(15);
	}
}


void test_tmr()
{
	INT8U err;

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	p_tmr = OSTmrCreate(10,                     /* first tick      */
			    5,                      /* period tick     */
			    OS_TMR_OPT_PERIODIC,    /* type            */
			    timer_func,             /* func address    */
			    0,                      /* func parameters */
                            "timer1",               /* timer name      */
                            &err                    /* error point     */
			);

	if(0 == p_tmr) {
		
		printk("error in OSTmrCreate\n");
	}


	OSTaskCreate( test_task1, 0, &stk1[STK_LEN -1], 5);

}




