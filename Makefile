demo: libmemlab.a
	gcc demo1.c -L. -l memlab -o demo1 -lpthread
	gcc demo2.c -L. -l memlab -o demo2 -lpthread
	gcc demo3.c -L. -l memlab -o demo3 -lpthread
	gcc demoE.c -L. -l memlab -o demoE -lpthread
libmemlab.a: memlab.o
	ar rcs libmemlab.a memlab.o
memlab.o: memlab.c
	gcc -o memlab.o -c memlab.c
clean:
	rm *.a *.o demo1 demo2 demo3 demoE