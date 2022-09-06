// Assignment 5
// Hands on experience for creating better memory management systems
// Operating Systems Laboratory (CS39002)
// Group 34
// Amartya Mandal 19CS10009
// Divyansh Bhatia 19CS10027

#include "memlab.h"

void fibonacci() {
	newFunc();
	assignArr("arr", INTEGER, 0, 1);
	assignArr("arr", INTEGER, 1, 1);
	createVar("x", INTEGER);
	createVar("y", INTEGER);
	createVar("i", INTEGER);
	
	for(assignVar("i", INTEGER, 2); getVar("i") < getVar("k"); assignVar("i", INTEGER, getVar("i")+1)) {
		assignVar("x", INTEGER, getArrElem("arr", getVar("i")-1));
		assignVar("y", INTEGER, getArrElem("arr", getVar("i")-2));
		assignArr("arr", INTEGER, getVar("i"), getVar("x")+getVar("y"));
	}
	
	freeElem("x");
	freeElem("y");
	freeElem("i");
}

int fibonacciProduct(int K){
	newFunc();
	fibonacci();
	endFunc();

	createVar("i", INTEGER);
	createVar("ans", INTEGER);
	assignVar("ans",INTEGER,1);

	printf("\nFirst %d fibnonacci numbers are: \n", getVar("k"));

	for(assignVar("i", INTEGER, 0); getVar("i") < getVar("k"); assignVar("i", INTEGER, getVar("i")+1)) {
		printf("%d \n", getArrElem("arr", getVar("i")));
	}

	for(assignVar("i", INTEGER, 1); getVar("i") < getVar("k"); assignVar("i", INTEGER, getVar("i")+1)) {
		assignVar("ans", INTEGER, getVar("ans")*getArrElem("arr", getVar("i")));

	}
	freeElem("i");
	freeElem("arr");
	return getVar("ans");
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Invalid argument - value of k required as a command line argument!\n");
		return 0;
	}
	createMem(1000);
	createVar("k", INTEGER);
	assignVar("k", INTEGER, atoi(argv[1]));
	int K = atoi(argv[1]);
	if(getVar("k") < 2 || getVar("k") > 10){
		printf("Argument k must be between 2 and 10 (Upper limit on int value)\n");
		goto end;
	}
	createArr("arr", INTEGER, getVar("k"));
	printf("\nThe product is: %d\n\n", fibonacciProduct(K));
	endFunc();
	end: endFunc();
	freeMem();
}
