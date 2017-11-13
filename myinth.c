

#include "clib.h"
#include "yakk.h"
#include "lab6defs.h"


extern int KeyBuffer;
void InterruptTicker();
void InterruptReseter();
void InterruptKeyboarder();

extern YKQ *MsgQPtr;
extern struct msg MsgArray[];
extern int GlobalFlag;

void InterruptTicker(){
	
	static int next = 0;
	static int data = 0;
    /* create a message with tick (sequence #) and pseudo-random data */
    MsgArray[next].tick = YKTickNum;
    data = (data + 89) % 100;
    MsgArray[next].data = data;
    if (YKQPost(MsgQPtr, (void *) &(MsgArray[next])) == 0)
	printString("  TickISR: queue overflow! \n");
    else if (++next >= MSGARRAYSIZE)
	next = 0;
}

void InterruptReseter(){
	printNewLine();
	printString("Reset Pressed");
	exit(0);
}

void InterruptKeyboarder(){
	GlobalFlag = 1;
}

/* pre lab6 hander code

#include "clib.h"
#include "yakk.h"


int counter = 0;
extern int KeyBuffer;
void InterruptTicker();
void InterruptReseter();
void InterruptKeyboarder();


void InterruptTicker(){




printNewLine();
counter++; 
printString("TICK ");
printInt(counter);
printNewLine();

}

void InterruptReseter(){
	printNewLine();
	printString("Reset Pressed");
	exit(0);
}

void InterruptKeyboarder(){
	int j = 0;
	if(KeyBuffer == 'd' || KeyBuffer == 'D'){
		printNewLine();
		printString("DELAY KEY PRESSED");
		printNewLine();
		
		for(j = 0; j < 7000; j++){
		
		}
		printNewLine();
		printString("DELAY COMPLETE");
		printNewLine();
	} else if(KeyBuffer == 'p' || KeyBuffer == 'P') {
		YKSemPost(NSemPtr);
	}else{
		printNewLine();
		printString("KEYPRESS (");
		printChar(KeyBuffer);
		printString(") IGNORED");
		printNewLine();
	}
}
*/
