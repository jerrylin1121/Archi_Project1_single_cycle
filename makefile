single_cycle:simulator.o instruction.o
	g++ -o single_cycle simulator.o instruction.o
instruction.o:instruction.cpp
	g++ -c instruction.cpp -o instruction.o
single_cycle.o:single_cycle.cpp
	g++ -c simulator.cpp -o simulator.o
clean:
	rm -f single_cycle simulator.o instruction.o
open_testcase:
	./single_cycle ../testcase/open_testcase/branch/iimage.bin ../testcase/open_testcase/branch/dimage.bin
