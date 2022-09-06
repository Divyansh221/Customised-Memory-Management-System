// Assignment 5
// Hands on experience for creating better memory management systems
// Operating Systems Laboratory (CS39002)
// Group 34
// Amartya Mandal 19CS10009
// Divyansh Bhatia 19CS10027

#include "memlab.h"

int main(){
	createMem(1000);
	createArr("s",CHARACTER,10);
	assignArr("s",INTEGER,0,5);
	assignArr("s",CHARACTER,1,'b');
	assignArr("a",CHARACTER,0,'b');
	getArrElem("a",0);
	getVar("s");
	createArr("s",INTEGER,10);
	createArr("s",INTEGER,500);
	endFunc();
	freeMem();
	return 0;
}
