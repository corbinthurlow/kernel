
/* -------------------------------------------------------------------- */
/* ---------------------------- LAB 4 --------------------------------- */
/* -------------------------------------------------------------------- */

//#define RUN_LAB_4_APP 
#ifdef RUN_LAB_4_APP
/* 
File: lab4d_app.c
Revision date: 23 December 2003
Description: Application code for EE 425 lab 4D (Kernel essentials D)
*/

#include "clib.h"
#include "yakk.h"

#define ASTACKSIZE 256          /* Size of task's stack in words */
#define BSTACKSIZE 256
#define CSTACKSIZE 256
#define DSTACKSIZE 256

int AStk[ASTACKSIZE];           /* Space for each task's stack  */
int BStk[BSTACKSIZE];
int CStk[CSTACKSIZE];
int DStk[CSTACKSIZE];

void ATask(void);               /* Function prototypes for task code */
void BTask(void);
void CTask(void);
void DTask(void);

void main(void)
{
    YKInitialize();
    
    printString("Creating tasks...\n");
    YKNewTask(ATask, (void *) &AStk[ASTACKSIZE], 3);
    YKNewTask(BTask, (void *) &BStk[BSTACKSIZE], 5);
    YKNewTask(CTask, (void *) &CStk[CSTACKSIZE], 7);
    YKNewTask(DTask, (void *) &DStk[DSTACKSIZE], 8);
    
    printString("Starting kernel...\n");
    YKRun();
}

void ATask(void)
{
    printString("Task A started.\n");
    while (1)
    {
        printString("Task A, delaying 2.\n");
        YKDelayTask(2);
    }
}

void BTask(void)
{
    printString("Task B started.\n");
    while (1)
    {
        printString("Task B, delaying 3.\n");
        YKDelayTask(3);
    }
}

void CTask(void)
{
    printString("Task C started.\n");
    while (1)
    {
        printString("Task C, delaying 5.\n");
        YKDelayTask(5);
    }
}

void DTask(void)
{
    printString("Task D started.\n");
    while (1)
    {
        printString("Task D, delaying 10.\n");
        YKDelayTask(10);
    }
}
#endif


/* -------------------------------------------------------------------- */
/* ---------------------------- LAB 5 --------------------------------- */
/* -------------------------------------------------------------------- */

//#define RUN_LAB_5_APP 
#ifdef RUN_LAB_5_APP
/*
File: lab5app.c
Revision date: 13 November 2009
Description: Application code for EE 425 lab 5 (Semaphores)
*/

#include "clib.h"
#include "yakk.h"

#define TASK_STACK_SIZE 512           /* stack size in words */

int TaskWStk[TASK_STACK_SIZE];        /* stacks for each task */
int TaskSStk[TASK_STACK_SIZE];
int TaskPStk[TASK_STACK_SIZE];
int TaskStatStk[TASK_STACK_SIZE];
int TaskPRMStk[TASK_STACK_SIZE];

YKSEM *PSemPtr;                        /* YKSEM must be defined in yakk.h */
YKSEM *SSemPtr;
YKSEM *WSemPtr;
YKSEM *NSemPtr;

void TaskWord(void)
{
    while (1)
    {
        YKSemPend(WSemPtr);
        printString("Hey");
        YKSemPost(PSemPtr);
                
        YKSemPend(WSemPtr); 
        printString("it");
        YKSemPost(SSemPtr);
                
        YKSemPend(WSemPtr); 
        printString("works");
        YKSemPost(PSemPtr);
    }
}

void TaskSpace(void)
{
    while (1)
    {
        YKSemPend(SSemPtr);
        printChar(' ');
        YKSemPost(WSemPtr);
    }
}

void TaskPunc(void)
{
    while (1)
    {
        YKSemPend(PSemPtr);
        printChar('"');
        YKSemPost(WSemPtr);
                
        YKSemPend(PSemPtr);
        printChar(',');
        YKSemPost(SSemPtr);
                
        YKSemPend(PSemPtr);
        printString("!\"\r\n");
        YKSemPost(PSemPtr);
                
        YKDelayTask(6);
    }
}

void TaskPrime(void)            /* task that actually computes primes */
{
    int curval = 1001;
    int j,flag,lncnt;
    int endval;
    
    while (1)
    {
        YKSemPend(NSemPtr);
	
        /* compute next range of primes */
        lncnt = 0;
        endval = curval + 500;
        for ( ; curval < endval; curval += 2)
        {
            flag = 0;
            for (j = 3; (j*j) < curval; j += 2)
            {
                if (curval % j == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                printChar(' ');
                printInt(curval);
                lncnt++;
                if (lncnt > 9)
                {
                    printNewLine();
                    lncnt = 0;
                }
            }
        }
        printNewLine();
    }
}

void TaskStat(void)                /* a task to track statistics */
{
    unsigned max, switchCount, idleCount;
    int tmp;
        
    YKDelayTask(1);
    printString("Welcome to the YAK kernel\r\n");
    printString("Determining CPU capacity\r\n");
    YKDelayTask(1);
    YKIdleCount = 0;
    YKDelayTask(5);
    max = YKIdleCount / 25;
    YKIdleCount = 0;

    YKNewTask(TaskPrime, (void *) &TaskPRMStk[TASK_STACK_SIZE], 32);
    YKNewTask(TaskWord,  (void *) &TaskWStk[TASK_STACK_SIZE], 10);
    YKNewTask(TaskSpace, (void *) &TaskSStk[TASK_STACK_SIZE], 11);
    YKNewTask(TaskPunc,  (void *) &TaskPStk[TASK_STACK_SIZE], 12);
    
    while (1)
    {
        YKDelayTask(20);
        
        YKEnterMutex();
        switchCount = YKCtxSwCount;
        idleCount = YKIdleCount;
        YKExitMutex();
        
        printString ("<<<<< Context switches: ");
        printInt((int)switchCount);
        printString(", CPU usage: ");
        tmp = (int) (idleCount/max);
        printInt(100-tmp);
        printString("% >>>>>\r\n");
        
        YKEnterMutex();
        YKCtxSwCount = 0;
        YKIdleCount = 0;
        YKExitMutex();
    }
}   

void main(void)
{
    YKInitialize();
    
    /* create all semaphores, at least one user task, etc. */
    PSemPtr = YKSemCreate(1);
    SSemPtr = YKSemCreate(0);
    WSemPtr = YKSemCreate(0);
    NSemPtr = YKSemCreate(0);
    YKNewTask(TaskStat, (void *) &TaskStatStk[TASK_STACK_SIZE], 30);
    
    YKRun();
}
#endif


/* -------------------------------------------------------------------- */
/* ---------------------------- LAB 6 --------------------------------- */
/* -------------------------------------------------------------------- */

//#define RUN_LAB_6_APP 
#ifdef RUN_LAB_6_APP
/* 
File: lab6app.c
Revision date: 4 November 2009
Description: Application code for EE 425 lab 6 (Message queues)
*/

#include "clib.h"
#include "yakk.h"                   /* contains kernel definitions */
#include "lab6defs.h"               /* contains definitions for this lab */

#define TASK_STACK_SIZE   512       /* stack size in words */
#define MSGQSIZE          10

struct msg MsgArray[MSGARRAYSIZE];  /* buffers for message content */

int ATaskStk[TASK_STACK_SIZE];      /* a stack for each task */
int BTaskStk[TASK_STACK_SIZE];
int STaskStk[TASK_STACK_SIZE];

int GlobalFlag;

void *MsgQ[MSGQSIZE];           /* space for message queue */
YKQ *MsgQPtr;                   /* actual name of queue */

void ATask(void)                /* processes data in messages */
{
    struct msg *tmp;
    int min, max, count;
        
    min = 100;
    max = 0;
    count = 0;
    
    while (1)
    {
        tmp = (struct msg *) YKQPend(MsgQPtr); /* get next msg */
                
        /* check sequence count in msg; were msgs dropped? */
        if (tmp->tick != count+1)
        {
            print("! Dropped msgs: tick ", 21);
            if (tmp->tick - (count+1) > 1) {
                printInt(count+1);
                printChar('-');
                printInt(tmp->tick-1);
                printNewLine();
            }
            else {
                printInt(tmp->tick-1);
                printNewLine();
            }
        }
                
        /* update sequence count */
        count = tmp->tick;
                
        /* process data; update statistics for this sample */
        if (tmp->data < min)
            min = tmp->data;
        if (tmp->data > max)
            max = tmp->data;
                
        /* output min, max, tick values */
        print("Ticks: ", 7);
        printInt(count);
        print("\t", 1);
        print("Min: ", 5);
        printInt(min);
        print("\t", 1);
        print("Max: ", 5);
        printInt(max);
        printNewLine();
    }
}

void BTask(void)                /* saturates the CPU for 5 ticks */
{
    int busycount, curval, j, flag, chcount;
    unsigned tickNum;
        
    curval = 1001;
    chcount = 0;
    
    while (1)
    {
        YKDelayTask(2);
        
        if (GlobalFlag == 1)
        {                           /* flag set -- loop for 5 ticks */
            YKEnterMutex();
            busycount = YKTickNum;
            YKExitMutex();
            
            while (1)
            {
                YKEnterMutex();
                tickNum = YKTickNum;
                YKExitMutex();
                if(tickNum >= busycount + 5) break;                
                
                curval += 2;        /* evaluate next number */
                flag = 0;
                for (j = 3; (j*j) < curval; j += 2)
                {
                    if (curval % j == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (!flag)
                {
                    printChar('.'); /* output a marker for each prime */
                    if (++chcount > 75)
                    {
                        printNewLine();
                        chcount = 0;
                    }
                }
            }
            printNewLine();
            chcount = 0;
            GlobalFlag = 0;        /* clear flag */
        }
    }
}

void STask(void)                /* tracks statistics */
{
    unsigned max, switchCount, idleCount;
    int tmp;

    YKDelayTask(1);
    printString("Welcome to the YAK kernel\r\n");
    printString("Determining CPU capacity\r\n");
    YKDelayTask(1);
    YKIdleCount = 0;
    YKDelayTask(5);
    max = YKIdleCount / 25;
    YKIdleCount = 0;

    YKNewTask(BTask, (void *) &BTaskStk[TASK_STACK_SIZE], 10);
    YKNewTask(ATask, (void *) &ATaskStk[TASK_STACK_SIZE], 20);
    
    while (1)
    {
        YKDelayTask(20);
        
        YKEnterMutex();
        switchCount = YKCtxSwCount;
        idleCount = YKIdleCount;
        YKExitMutex();
        
        printString("<<<<< Context switches: ");
        printInt((int)switchCount);
        printString(", CPU usage: ");
        tmp = (int) (idleCount/max);
        printInt(100-tmp);
        printString("% >>>>>\r\n");
        
        YKEnterMutex();
        YKCtxSwCount = 0;
        YKIdleCount = 0;
        YKExitMutex();
    }
}   

void main(void)
{
    YKInitialize();
    
    /* create queue, at least one user task, etc. */
    GlobalFlag = 0;
    MsgQPtr = YKQCreate(MsgQ, MSGQSIZE);
    YKNewTask(STask, (void *) &STaskStk[TASK_STACK_SIZE], 30);
    
    YKRun();
}
#endif
 
/* -------------------------------------------------------------------- */
/* ---------------------------- LAB 7 --------------------------------- */
/* -------------------------------------------------------------------- */

#define RUN_LAB_7_APP 
#ifdef RUN_LAB_7_APP
/* 
File: lab7app.c
Revision date: 10 November 2005
Description: Application code for EE 425 lab 7 (Event flags)
*/

#include "clib.h"
#include "yakk.h"                     /* contains kernel definitions */
#include "lab7defs.h"

#define TASK_STACK_SIZE   512         /* stack size in words */



YKEVENT *charEvent;
YKEVENT *numEvent;

int CharTaskStk[TASK_STACK_SIZE];     /* a stack for each task */
int AllCharsTaskStk[TASK_STACK_SIZE];
int AllNumsTaskStk[TASK_STACK_SIZE];
int STaskStk[TASK_STACK_SIZE];



void CharTask(void)        /* waits for any events triggered by letter keys */
{
    unsigned events;

    printString("Started CharTask     (2)\n");

    while(1) {
        events = YKEventPend(charEvent, 
                             EVENT_A_KEY | EVENT_B_KEY | EVENT_C_KEY,
                             EVENT_WAIT_ANY);
        
        if(events == 0) {
            printString("Oops! At least one event should be set "
                        "in return value!\n");
        }

        if(events & EVENT_A_KEY) {
            printString("CharTask     (A)\n");
            YKEventReset(charEvent, EVENT_A_KEY);
        }
        
        if(events & EVENT_B_KEY) {
            printString("CharTask     (B)\n");
            YKEventReset(charEvent, EVENT_B_KEY);
        }
        
        if(events & EVENT_C_KEY) {
            printString("CharTask     (C)\n");
            YKEventReset(charEvent, EVENT_C_KEY);
        }
    }
}


void AllCharsTask(void)    /* waits for all events triggered by letter keys */
{
    unsigned events;

    printString("Started AllCharsTask (3)\n");

    while(1) {
        events = YKEventPend(charEvent, 
                             EVENT_A_KEY | EVENT_B_KEY | EVENT_C_KEY,
                             EVENT_WAIT_ALL);
        // To be reset by WaitForAny task
        
        if(events != 0) {
            printString("Oops! Char events weren't reset by CharTask!\n");
        }

        printString("AllCharsTask (D)\n");
    }
}


void AllNumsTask(void)     /* waits for events triggered by number keys */
{
    unsigned events;

    printString("Started AllNumsTask  (1)\n");

    while(1) {
        events = YKEventPend(numEvent, 
                             EVENT_1_KEY | EVENT_2_KEY | EVENT_3_KEY,
                             EVENT_WAIT_ALL);
        
        if(events != (EVENT_1_KEY | EVENT_2_KEY | EVENT_3_KEY)) {
            printString("Oops! All events should be set in return value!\n");
        }

        printString("AllNumsTask  (123)\n");

        YKEventReset(numEvent, EVENT_1_KEY | EVENT_2_KEY | EVENT_3_KEY);
    }
}


void STask(void)           /* tracks statistics */
{
    unsigned max, switchCount, idleCount;
    int tmp;

    YKDelayTask(1);
    printString("Welcome to the YAK kernel\r\n");
    printString("Determining CPU capacity\r\n");
    YKDelayTask(1);
    YKIdleCount = 0;
    YKDelayTask(5);
    max = YKIdleCount / 25;
    YKIdleCount = 0;

    YKNewTask(CharTask, (void *) &CharTaskStk[TASK_STACK_SIZE], 2);
    YKNewTask(AllNumsTask, (void *) &AllNumsTaskStk[TASK_STACK_SIZE], 1);
    YKNewTask(AllCharsTask, (void *) &AllCharsTaskStk[TASK_STACK_SIZE], 3);
    
    while (1)
    {
        YKDelayTask(20);
        
        YKEnterMutex();
        switchCount = YKCtxSwCount;
        idleCount = YKIdleCount;
        YKExitMutex();
        
        printString("<<<<< Context switches: ");
        printInt((int)switchCount);
        printString(", CPU usage: ");
        tmp = (int) (idleCount/max);
        printInt(100-tmp);
        printString("% >>>>>\r\n");
        
        YKEnterMutex();
        YKCtxSwCount = 0;
        YKIdleCount = 0;
        YKExitMutex();
    }
}   


void main(void)
{
    YKInitialize();

    charEvent = YKEventCreate(0);
    numEvent = YKEventCreate(0);
    YKNewTask(STask, (void *) &STaskStk[TASK_STACK_SIZE], 0);
    
    YKRun();
}
#endif

