dict3: driver.o data.o point.o array.o quadtree.o rectangle.o
	gcc -o dict3 driver.o data.o point.o array.o quadtree.o rectangle.o

dict4: driver.o point.o data.o array.o quadtree.o rectangle.o
	gcc -o dict4 driver.o data.o point.o array.o quadtree.o rectangle.o

driver.o: driver.c point.o data.o array.o quadtree.o rectangle.o
	gcc -c driver.c

data.o: point.o data.c data.h
	gcc -c data.c

point.o: point.c point.h
	gcc -c point.c

array.o: point.o data.o array.c array.h
	gcc -c array.c

quadtree.o: data.o array.o rectangle.o point.o quadtree.c quadtree.h
	gcc -c quadtree.c

rectangle.o: data.o point.o rectangle.c rectangle.h
	gcc -c rectangle.c

clean: 
	rm -f *.o
