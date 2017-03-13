#include <iostream>
#include <fstream>
#include <iomanip>
#include "instruction.h"
#include "memory.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream iin(argv[1], ios::in | ios::binary);
    ifstream din(argv[2], ios::in | ios::binary);
	unsigned int Sp_ini;
	Sp_ini = read_4_byte_int(&din);
	load_instruction(&iin);
	load_data(&din);
	for(int i=0; i<num_of_ins; ++i){
		decode_instructions(ins_mem[i+PC_ini]);
	}
	for(int i=0; i<num_of_data; ++i){
		cout << setw(2) << hex << data_mem[i] << endl;
	}
    return 0;
}
