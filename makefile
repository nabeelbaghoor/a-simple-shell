a.out: main.o
	g++ main.o -o a.out
	
main.o: main.cpp
	g++ main.cpp -c
	
clean:
	rm -fr *o main
	
	

