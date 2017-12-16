Simulator: main.o
	g++ main.o -o Simulator

main.o: main.cc
	g++ main.cc -c

clean:
	rm Simulator *.o *~
