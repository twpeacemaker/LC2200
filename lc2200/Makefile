GCC=g++

Simulator: main.o simulator.o cpu.o memory.o
	$(GCC) main.o simulator.o cpu.o memory.o -o Simulator

main.o: main.cc simulator.o
	$(GCC) main.cc -c

simulator.o: cpu.o Simulator.h Simulator.cc bit_manipulation.o
	$(GCC) Simulator.cc -c

cpu.o: constants.h CPU.h CPU.cc
	$(GCC) CPU.cc -c

memory.o: constants.h Memory.cc Memory.h
		$(GCC) Memory.cc -c

bit_manipulation.o: useful_functions/bit_manipulation.cc useful_functions/bit_manipulation.h constants.h
	$(GCC) useful_functions/bit_manipulation.cc -c



clean:
	rm Simulator *.o *~
