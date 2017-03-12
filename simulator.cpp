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
	unsigned int PC_value;
	unsigned int Sp_ini;
	PC_value = read_binary_int(&iin);
	Sp_ini = read_binary_int(&din);
	load_instruction(&iin);
	load_data(&din);
	for(int i=0; i<num_of_ins; ++i){
		decode_instructions(ins_mem[i]);
	}
    return 0;
}
