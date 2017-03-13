single_cycle:simulator.o instruction.o memory.o regfile.o
	g++ -o single_cycle simulator.o instruction.o memory.o regfile.o
regfile.o:regfile.cpp
	g++ -c regfile.cpp -o regfile.o
memory.o:memory.cpp
	g++ -c memory.cpp -o memory.o
instruction.o:instruction.cpp
	g++ -c instruction.cpp -o instruction.o
single_cycle.o:single_cycle.cpp
	g++ -c simulator.cpp -o simulator.o
clean:
	rm -f single_cycle simulator.o instruction.o memory.o regfile.o
branch:
	./single_cycle ../testcase/open_testcase/branch/iimage.bin ../testcase/open_testcase/branch/dimage.bin
