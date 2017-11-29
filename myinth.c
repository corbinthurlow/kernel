

#include "clib.h"
#include "yakk.h"
#include "lab6defs.h"
#include "lab7defs.h"


extern int KeyBuffer;
void InterruptTicker();
void InterruptReseter();
void InterruptKeyboarder();

//extern YKQ *MsgQPtr;
//extern struct msg MsgArray[];
extern int GlobalFlag;
extern unsigned int YKTickNum;

void InterruptTicker(){
	
	/*static int next = 0;
	static int data = 0;
     create a message with tick (sequence #) and pseudo-random data 
    MsgArray[next].tick = YKTickNum;
    data = (data + 89) % 100;
    MsgArray[next].data = data;
    if (YKQPost(MsgQPtr, (void *) &(MsgArray[next])) == 0)
	printString("  TickISR: queue overflow! \n");
    else if (++next >= MSGARRAYSIZE)
	next = 0;
*/
}

void InterruptReseter(){
	printNewLine();
	printString("Reset Pressed");
	exit(0);
}

void InterruptKeyboarder(){
	//GlobalFlag = 1;
char c;
    c = KeyBuffer;

    if(c == 'a') YKEventSet(charEvent, EVENT_A_KEY);
    else if(c == 'b') YKEventSet(charEvent, EVENT_B_KEY);
    else if(c == 'c') YKEventSet(charEvent, EVENT_C_KEY);
    else if(c == 'd') YKEventSet(charEvent, EVENT_A_KEY | EVENT_B_KEY | EVENT_C_KEY);
    else if(c == '1') YKEventSet(numEvent, EVENT_1_KEY);
    else if(c == '2') YKEventSet(numEvent, EVENT_2_KEY);
    else if(c == '3') YKEventSet(numEvent, EVENT_3_KEY);
    else {
        print("\nKEYPRESS (", 11);
        printChar(c);
        print(") IGNORED\n", 10);
    }
}
/*

// pre lab6 hander code

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
