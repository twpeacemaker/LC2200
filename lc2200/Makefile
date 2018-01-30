GCC=g++

Simulator: terminal.o main.o simulator.o cpu.o memory.o MyString.o bit_manipulation.o char_arrays.o
	$(GCC) main.o simulator.o cpu.o memory.o terminal.o MyString.o bit_manipulation.o char_arrays.o -o Simulator

terminal.o: Exception.h Terminal.h Terminal.cc MyString.o simulator.o  useful_functions/char_arrays.h
	$(GCC) Terminal.cc -c

MyString.o: useful_classes/MyString.cc useful_classes/MyString.h useful_classes/LList.h
	$(GCC) useful_classes/MyString.cc -c

main.o: main.cc terminal.o
	$(GCC) main.cc -c

simulator.o: cpu.o Simulator.h Simulator.cc Exception.h useful_functions/bit_manipulation.h useful_functions/char_arrays.h
	$(GCC) Simulator.cc -c

cpu.o: constants.h CPU.h CPU.cc MyString.o
	$(GCC) CPU.cc -c

memory.o: constants.h Memory.cc Memory.h MyString.o useful_functions/char_arrays.h Exception.h MyString.o
		$(GCC) Memory.cc -c

bit_manipulation.o: useful_functions/bit_manipulation.cc useful_functions/bit_manipulation.h constants.h
	$(GCC) useful_functions/bit_manipulation.cc -c

char_arrays.o: useful_functions/char_arrays.cc useful_functions/char_arrays.h Exception.h constants.h
	$(GCC) useful_functions/char_arrays.cc -c



clean:
	rm Simulator *.o *~
