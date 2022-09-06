// Assignment 5
// Hands on experience for creating better memory management systems
// Operating Systems Laboratory (CS39002)
// Group 34
// Amartya Mandal 19CS10009
// Divyansh Bhatia 19CS10027

#include "memlab.h"

void func1(int x, int y) {
	newFunc();
	createArr("a0", INTEGER, 50000);
	createVar("i0", INTEGER);
	
	for(assignVar("i0", INTEGER, 0); getVar("i0") < 50000; assignVar("i0", INTEGER, getVar("i0") + 1)) {
		assignArr("a0", INTEGER, getVar("i0"), rand()%10000);
	}
}

void func2(int x, int y) {
	newFunc();
	createArr("a1", MEDIUM_INT, 50000);
	createVar("i1", INTEGER);
	
	for(assignVar("i1", INTEGER, 0); getVar("i1") < 50000; assignVar("i1", INTEGER, getVar("i1") + 1)) {
		assignArr("a1", MEDIUM_INT, getVar("i1"), rand()%10000);
	}
}

void func3(int x, int y) {
	newFunc();
	createArr("a2", CHARACTER, 50000);
	createVar("i2", INTEGER);
	
	for(assignVar("i2", INTEGER, 0); getVar("i2") < 50000; assignVar("i2", INTEGER, getVar("i2") + 1)) {
		assignArr("a2", CHARACTER, getVar("i2"), rand()%26 + 'a');
	}
}

void func4(int x, int y) {
	newFunc();
	createArr("a3", BOOLEAN, 50000);
	createVar("i3", INTEGER);
	
	for(assignVar("i3", INTEGER, 0); getVar("i3") < 50000; assignVar("i3", INTEGER, getVar("i3") + 1)) {
		assignArr("a3", BOOLEAN, getVar("i3"), rand()%2);
	}
}

void func5(int x, int y) {
	newFunc();
	createArr("a4", INTEGER, 50000);
	createVar("i4", INTEGER);
	
	for(assignVar("i4", INTEGER, 0); getVar("i4") < 50000; assignVar("i4", INTEGER, getVar("i4") + 1)) {
		assignArr("a4", INTEGER, getVar("i4"), rand()%10000);
	}
}

void func6(int x, int y) {
	newFunc();
	createArr("a5", MEDIUM_INT, 50000);
	createVar("i5", INTEGER);
	
	for(assignVar("i5", INTEGER, 0); getVar("i5") < 50000; assignVar("i5", INTEGER, getVar("i5") + 1)) {
		assignArr("a5", MEDIUM_INT, getVar("i5"), rand()%10000);
	}
}

void func7(int x, int y) {
	newFunc();
	createArr("a6", CHARACTER, 50000);
	createVar("i6", INTEGER);
	
	for(assignVar("i6", INTEGER, 0); getVar("i6") < 50000; assignVar("i6", INTEGER, getVar("i6") + 1)) {
		assignArr("a6", CHARACTER, getVar("i6"), rand()%26 + 'a');
	}
}

void func8(int x, int y) {
	newFunc();
	createArr("a7", BOOLEAN, 50000);
	createVar("i7", INTEGER);
	
	for(assignVar("i7", INTEGER, 0); getVar("i7") < 50000; assignVar("i7", INTEGER, getVar("i7") + 1)) {
		assignArr("a7", BOOLEAN, getVar("i7"), rand()%2);
	}
}

void func9(int x, int y) {
	newFunc();
	createArr("a8", INTEGER, 50000);
	createVar("i8", INTEGER);
	
	for(assignVar("i8", INTEGER, 0); getVar("i8") < 50000; assignVar("i8", INTEGER, getVar("i8") + 1)) {
		assignArr("a8", INTEGER, getVar("i8"), rand()%10000);
	}
}

void func10(int x, int y) {
	newFunc();
	createArr("a9", MEDIUM_INT, 50000);
	createVar("i9", INTEGER);
	
	for(assignVar("i9", INTEGER, 0); getVar("i9") < 50000; assignVar("i9", INTEGER, getVar("i9") + 1)) {
		assignArr("a9", MEDIUM_INT, getVar("i9"), rand()%10000);
	}
}


int main() {
	int sz = 250000000;
	int x = 5, y = 10;
	createMem(sz);
	createVar("x1", INTEGER);
	createVar("y1", INTEGER);
	createVar("x2", MEDIUM_INT);
	createVar("y2", MEDIUM_INT);
	createVar("x3", CHARACTER);
	createVar("y3", CHARACTER);
	createVar("x4", BOOLEAN);
	createVar("y4", BOOLEAN);

	func1(x, y);
	endFunc();
	func2(x, y);
	endFunc();
	func3(x, y);
	endFunc();
	func4(x, y);
	endFunc();
	func5(x, y);
	endFunc();
	func6(x, y);
	endFunc();
	func7(x, y);
	endFunc();
	func8(x, y);
	endFunc();
	func9(x, y);
	endFunc();
	func10(x, y);
	endFunc();
	endFunc();
	freeMem();
}
