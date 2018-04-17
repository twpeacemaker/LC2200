GCC=g++

Machine: Terminal.o main.o Machine.o CPU.o Memory.o MyString.o bit_manipulation.o char_arrays.o PCB.o Freemem.o FileSystem.o
	$(GCC) main.o Machine.o CPU.o Memory.o Terminal.o MyString.o bit_manipulation.o char_arrays.o PCB.o Freemem.o FileSystem.o -o Simulator
	rm Disk

Terminal.o: constants.h Exception.h Terminal.h Terminal.cc useful_classes/MyString.h Machine.h  useful_functions/char_arrays.h
	$(GCC) Terminal.cc -c

MyString.o: useful_classes/MyString.cc useful_classes/MyString.h useful_classes/LList.h Exception.h
	$(GCC) useful_classes/MyString.cc -c

main.o: main.cc Terminal.h useful_classes/Queue.h
	$(GCC) main.cc -c

Machine.o: Machine.h Machine.cc FileSystem.h CPU.h Memory.h Freemem.h constants.h Exception.h PCB.h useful_classes/LList.h useful_classes/MyString.h useful_classes/Queue.h useful_functions/bit_manipulation.h useful_functions/char_arrays.h
	$(GCC) Machine.cc -c

CPU.o: constants.h CPU.h CPU.cc Exception.h PCB.h useful_classes/MyString.h
	$(GCC) CPU.cc -c

Memory.o: constants.h Memory.cc Memory.h useful_classes/MyString.h useful_functions/char_arrays.h Exception.h
	$(GCC) Memory.cc -c

Freemem.o: constants.h Freemem.h Freemem.cc
	$(GCC) Freemem.cc -c

bit_manipulation.o: useful_functions/bit_manipulation.cc useful_functions/bit_manipulation.h constants.h Exception.h
	$(GCC) useful_functions/bit_manipulation.cc -c

char_arrays.o: useful_functions/char_arrays.cc useful_functions/char_arrays.h Exception.h constants.h
	$(GCC) useful_functions/char_arrays.cc -c

PCB.o: PCB.h PCB.cc constants.h CPU.h
	$(GCC) PCB.cc -c

FileSystem.o: FileSystem.cc FileSystem.cc constants.h useful_functions/bit_manipulation.h useful_classes/MyString.h useful_functions/char_arrays.h
	$(GCC) FileSystem.cc -c

clean:
	rm *.o *~ Simulator
