single_cycle:single_cycle.o
	g++ -o single_cycle single_cycle.o
single_cycle.o:single_cycle.cpp
	g++ -c single_cycle.cpp -o single_cycle.o
clean:
	rm -f single_cycle single_cycle.o
open_testcase:
	./single_cycle ../testcase/open_testcase/branch/iimage.bin ../testcase/open_testcase/branch/dimage.bin
