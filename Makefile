tsp:A1.o
	g++ A1.o -o tsp

A1.o: A1.cpp
	g++ -c A1.cpp

clean:
	rm *.o tsp*