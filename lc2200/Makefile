GCC=g++

Simulator: main.o simulator.o cpu.o
	$(GCC) main.o simulator.o cpu.o -o Simulator

main.o: main.cc simulator.o
	$(GCC) main.cc -c

simulator.o: cpu.o Simulator.h Simulator.cc bit_manipulation.o
	$(GCC) Simulator.cc -c

cpu.o: constants.h CPU.h CPU.cc
	$(GCC) CPU.cc -c

bit_manipulation.o: useful_functions/bit_manipulation.cc useful_functions/bit_manipulation.h constants.h
	$(GCC) useful_functions/bit_manipulation.cc -c

clean:
	rm Simulator *.o *~
