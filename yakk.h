
extern unsigned int YKCtxSwCount;
extern unsigned int YKIdleCount;
extern int GlobalFlag;


// struct that holds semaphores
typedef struct semaphore
{
	int value;							//value of the semaphore
	int isTaken;

} YKSEM;

extern YKSEM *NSemPtr;

typedef struct queue
{
	void **MsgQ;	//array with pointers in it
	int length;		//length of the Queue
	void *TailMsgQ;
	void *HeadMsgQ;
} YKQ;


//data structure definitions
typedef struct taskblock *TCBptr;
typedef struct taskblock
{
	unsigned int* stackptr;             // task stack
    int state;                      	// task state 0: New, 1: Blocked, 2: Ready, 3: Running
    int priority;                       // task priority 
    int delay;                          // delay count
    YKSEM* sem;							// pointer to a semaphore struct
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
YKSEM* YKSemCreate(int value);
void YKSemPend(YKSEM *semaphore);
void YKSemPost(YKSEM *semaphore);
YKQ *YKQCreate(void **start, unsigned int size);


//#defines
#define NULL 0

//task control #define statements
#define NEW 0
#define BLOCKED 1
#define READY 2
#define RUNNING 3
