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
