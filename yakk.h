
extern unsigned int YKCtxSwCount;
extern unsigned int YKIdleCount;

//data structure definitions
typedef struct taskblock *TCBptr;
typedef struct taskblock
{
	unsigned int* stackptr;             // task stack
    int state;                      	// task state 0: New, 1: Blocked, 2: Ready, 3: Running
    int priority;                       // task priority 
    int delay;                          // delay count
    TCBptr next;						/* forward ptr for dbl linked list */
    TCBptr prev;						/* backward ptr for dbl linked list */
} TCB;


//function prototypes
void YKInitialize(void);
void YKNewTask(void (*task)(void), void *taskStack, unsigned int priority);
void YKEnterMutex(void);
void YKExitMutex(void);
void YKRun(void);
void YKScheduler(void);
void YKDispatcher(int iSaveContext, TCBptr cTask, TCBptr nextTask); //currently not using this ...
void YKEnterISR();
void YKExitISR();
void YKDelayTask(unsigned int count);
void YKTickHandler();


//#defines
#define NULL 0

//task control #define statements
#define NEW 0
#define BLOCKED 1
#define READY 2
#define RUNNING 3
