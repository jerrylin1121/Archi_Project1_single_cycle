single_cycle:simulator.o instruction.o memory.o regfile.o
	g++ -o single_cycle simulator.o instruction.o memory.o regfile.o
regfile.o:regfile.cpp
	g++ -c regfile.cpp -o regfile.o
memory.o:memory.cpp
	g++ -c memory.cpp -o memory.o
instruction.o:instruction.cpp
	g++ -std=c++11 -c instruction.cpp -o instruction.o
simulator.o:simulator.cpp
	g++ -c simulator.cpp -o simulator.o
clean:
	rm -f single_cycle simulator.o instruction.o memory.o regfile.o snapshot.rpt
branch:
	./single_cycle ../testcase/open_testcase/branch/iimage.bin ../testcase/open_testcase/branch/dimage.bin
	diff ~/Archi2017_Project1/archiTA/testcase/open_testcase/branch/snapshot.rpt ./snapshot.rpt
fib_dp:
	./single_cycle ../testcase/open_testcase/fib_dp/iimage.bin ../testcase/open_testcase/fib_dp/dimage.bin
	diff ~/Archi2017_Project1/archiTA/testcase/open_testcase/fib_dp/snapshot.rpt ./snapshot.rpt
func:
	./single_cycle ../testcase/open_testcase/func/iimage.bin ../testcase/open_testcase/func/dimage.bin
	diff ~/Archi2017_Project1/archiTA/testcase/open_testcase/func/snapshot.rpt ./snapshot.rpt
mult:
	./single_cycle ../testcase/open_testcase/mult/iimage.bin ../testcase/open_testcase/mult/dimage.bin
	diff ~/Archi2017_Project1/archiTA/testcase/open_testcase/mult/snapshot.rpt ./snapshot.rpt
recur:
	./single_cycle ../testcase/open_testcase/recur/iimage.bin ../testcase/open_testcase/recur/dimage.bin
	diff ~/Archi2017_Project1/archiTA/testcase/open_testcase/recur/snapshot.rpt ./snapshot.rpt
all: single_cycle branch fib_dp func recur mult
