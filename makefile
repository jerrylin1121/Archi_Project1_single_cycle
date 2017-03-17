single_cycle:simulator.o instruction.o memory.o regfile.o error.o
	g++ -o single_cycle simulator.o instruction.o memory.o regfile.o error.o
error.o:error.cpp
	g++ -c error.cpp -o error.o
regfile.o:regfile.cpp
	g++ -c regfile.cpp -o regfile.o
memory.o:memory.cpp
	g++ -c memory.cpp -o memory.o
instruction.o:instruction.cpp
	g++ -c instruction.cpp -o instruction.o
simulator.o:simulator.cpp
	g++ -c simulator.cpp -o simulator.o
clean:
	rm -f single_cycle simulator.o instruction.o memory.o regfile.o error.o snapshot.rpt error_dump.rpt
clean_test:
	rm -f snapshot.rpt _snapshot.rpt error_dump.rpt _error_dump.rpt makefile
test:
	~/Archi2017_Project1/single_cycle/simulator/single_cycle
	~/Archi2017_Project1/archiTA/simulator/single_cycle
	diff ./snapshot.rpt ./_snapshot.rpt
	diff ./error_dump.rpt ./_error_dump.rpt
