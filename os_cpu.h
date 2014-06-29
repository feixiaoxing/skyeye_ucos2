

#ifndef _OS_CPU_H
#define _OS_CPU_H


// type

typedef unsigned char   INT8U;
typedef unsigned short  INT16U;
typedef unsigned int    INT32U;
typedef char            INT8S;


typedef unsigned int   OS_CPU_SR;
typedef unsigned char  BOOLEAN;
typedef unsigned int   OS_STK;


// critical definition

#define OS_CRITICAL_METHOD 3

#define OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();} 
#define OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}

#define OS_STK_GROWTH 1

// timer

#define OS_TASK_TMR_PRIO 40  /* prio of timer task can not be prio of idle task and statistic task */

// switch

#define OS_TASK_SW()  port_task_switch()
#define OSIntCtxSw()  raw_int_switch()

#endif


