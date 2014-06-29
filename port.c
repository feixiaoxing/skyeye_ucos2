

#include "ucos_ii.h"

OS_STK *OSTaskStkInit (void (*p_task)(void *pd), void *p_arg, OS_STK *ptos, INT16U opt)
{
        INT32U *stk;
        INT32U temp = (INT32U)(ptos);
        stk = (INT32U  *)temp;

        *(stk)    = (INT32U)p_task;       /* Entry Point                                        */
        *(--stk)  = (INT32U)0;             /* LR                                                 */
        *(--stk)  = (INT32U)0;             /* R12                                                */
        *(--stk)  = (INT32U)0;             /* R11                                                */
        *(--stk)  = (INT32U)0;             /* R10                                                */
        *(--stk)  = (INT32U)0;             /* R9                                                 */
        *(--stk)  = (INT32U)0;             /* R8                                                 */
        *(--stk)  = (INT32U)0;             /* R7 :                                               */
        *(--stk)  = (INT32U)0;             /* R6                                                 */
        *(--stk)  = (INT32U)0;             /* R5                                                 */
        *(--stk)  = (INT32U)0;             /* R4                                                 */
        *(--stk)  = (INT32U)0;             /* R3                                                 */
        *(--stk)  = (INT32U)0;             /* R2                                                 */
        *(--stk)  = (INT32U)0;             /* R1                                                 */
        *(--stk)  = (INT32U)p_arg;         /* R0 argument                                        */
        *(--stk)  = (INT32U)0x00000013L;   /* CPSR                                               */

        return stk;
}

void OSTaskCreateHook(OS_TCB* p_tcb )
{
	printk("task create here\n");
}

void OSTaskDelHook(OS_TCB* p_tcb)
{}

void OSTaskIdleHook()
{}

void OSTimeTickHook()
{}

void OSTCBInitHook(OS_TCB* p_tcb)
{}

void OSInitHookBegin()
{}

void OSInitHookEnd()
{}

void OSTaskStatHook()
{}

void OSTaskSwHook()
{}

