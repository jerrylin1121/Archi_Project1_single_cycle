single_cycle:simulator.o instruction.o memory.o
	g++ -o single_cycle simulator.o instruction.o memory.o
memory.o:memory.cpp
	g++ -c memory.cpp -o memory.o
instruction.o:instruction.cpp
	g++ -c instruction.cpp -o instruction.o
single_cycle.o:single_cycle.cpp
	g++ -c simulator.cpp -o simulator.o
clean:
	rm -f single_cycle simulator.o instruction.o memory.o
open_testcase:
	./single_cycle ../testcase/open_testcase/branch/iimage.bin ../testcase/open_testcase/branch/dimage.bin
