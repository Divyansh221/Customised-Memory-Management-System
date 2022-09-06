// Assignment 5
// Hands on experience for creating better memory management systems
// Operating Systems Laboratory (CS39002)
// Group 34
// Amartya Mandal 19CS10009
// Divyansh Bhatia 19CS10027

#include "memlab.h"

int main(){
	createMem(40);
	createArr("s",CHARACTER,10);
	assignArr("s",CHARACTER,0,'a');
	assignArr("s",CHARACTER,1,'b');
	assignArr("s",CHARACTER,2,'c');
	assignArr("s",CHARACTER,3,'d');
	assignArr("s",CHARACTER,4,'e');
	assignArr("s",CHARACTER,5,'f');
	assignArr("s",CHARACTER,6,'g');
	assignArr("s",CHARACTER,7,'h');
	assignArr("s",CHARACTER,8,'i');
	assignArr("s",CHARACTER,9,'j');
	printf("%c\n",getArrElem("s",0));
	printf("%c\n",getArrElem("s",1));
	printf("%c\n",getArrElem("s",2));
	printf("%c\n",getArrElem("s",3));
	printf("%c\n",getArrElem("s",4));
	printf("%c\n",getArrElem("s",5));
	printf("%c\n",getArrElem("s",6));
	printf("%c\n",getArrElem("s",7));
	printf("%c\n",getArrElem("s",8));
	printf("%c\n",getArrElem("s",9));
	endFunc();
	freeMem();
	return 0;
}
