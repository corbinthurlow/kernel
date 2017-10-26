
/****************************APPLICATION CODE FOR LAB 4 part B************************************/



/* 
File: lab4b_app.c
Revision date: 23 December 2003
Description: Application code for EE 425 lab 4B (Kernel essentials B)

#include "clib.h"
#include "yakk.h"

#define ASTACKSIZE 256          /* Size of each stack in words 
#define BSTACKSIZE 256
#define CSTACKSIZE 256

int AStk[ASTACKSIZE];           /* Space for each task's stack 
int BStk[BSTACKSIZE];
int CStk[CSTACKSIZE];

void ATask(void);               /* Function prototypes for task code
void BTask(void);
void CTask(void);

void main(void)
{
    YKInitialize();
    
    printString("Creating task A...\n");
    YKNewTask(ATask, (void *)&AStk[ASTACKSIZE], 5);
    
    printString("Starting kernel...\n");
    YKRun();
}

void ATask(void)
{
    printString("Task A started!\n");
	
	
    printString("Creating low priority task B...\n");
    YKNewTask(BTask, (void *)&BStk[BSTACKSIZE], 7);

    printString("Creating task C...\n");
    YKNewTask(CTask, (void *)&CStk[CSTACKSIZE], 2);

    printString("Task A is still running! Oh no! Task A was supposed to stop.\n");
    exit(0);
}

void BTask(void)
{
    printString("Task B started! Oh no! Task B wasn't supposed to run.\n");
    exit(0);
}

void CTask(void)
{
    int count;
    unsigned numCtxSwitches;

    YKEnterMutex();
    numCtxSwitches = YKCtxSwCount;
    YKExitMutex();

    printString("Task C started after ");
    printUInt(numCtxSwitches);
    printString(" context switches!\n");

    while (1)
    {
	printString("Executing in task C.\n");
        for(count = 0; count < 5000; count++);
    }
}
*/
/****************************************************************/





/*********************************************APPLICATION CODE FOR LAB 4 PART C********************************/



//#include "clib.h"
//#include "yakk.h"

//#define STACKSIZE 256          // Size of task's stack in words 

//int TaskStack[STACKSIZE];      // Space for task's stack 
//int TaskStack1[STACKSIZE];	   // Space for task1's stack

/*void Task(void);               // Function prototype for task code */

/*void Task1(void);

void main(void)
{
    YKInitialize();
    
    printString("Creating task...\n");
    YKNewTask(Task, (void *) &TaskStack[STACKSIZE], 1);
    //YKNewTask(Task1,(void *) &TaskStack1[STACKSIZE],0);

    printString("Starting kernel...\n");
    YKRun();
}

void Task(void)
{
    unsigned idleCount;
    unsigned numCtxSwitches;

    printString("Task started.\n");
    while (1)
    {
        printString("Delaying task...\n");

        YKDelayTask(2);

        YKEnterMutex();
        numCtxSwitches = YKCtxSwCount;
        idleCount = YKIdleCount;
        YKIdleCount = 0;
        YKExitMutex();

        printString("Task running after ");
        printUInt(numCtxSwitches);
        printString(" context switches! YKIdleCount is ");
        printUInt(idleCount);
        printString(".\n");
    }
}*/

/*void Task1(void){

    unsigned idleCount;
    unsigned numCtxSwitches;

    printString("Task1 started.\n");
    while (1)
    {
        printString("Delaying task1...\n");

        YKDelayTask(6);

        YKEnterMutex();
        numCtxSwitches = YKCtxSwCount;
        idleCount = YKIdleCount;
        YKIdleCount = 0;
        YKExitMutex();

        printString("Task1 running after ");
        printUInt(numCtxSwitches);
        printString(" context switches! YKIdleCount is ");
        printUInt(idleCount);
        printString(".\n");
    }

}
*/

/*****************************************************************************/



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



