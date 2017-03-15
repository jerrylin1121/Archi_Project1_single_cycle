#include <iostream>
#include <fstream>
#include <iomanip>
#include "instruction.h"
#include "memory.h"
#include "regfile.h"

using namespace std;
fstream snap("snapshot.rpt", fstream::out);

int main(int argc, char *argv[])
{
    ifstream iin(argv[1], ios::in | ios::binary);
    ifstream din(argv[2], ios::in | ios::binary);
	load_instruction(&iin);
	load_data(&din);
	snap << "cycle 0" << endl;
	show_all_reg();
	snap << endl << endl;
	for(int i=0; ;++i){
		reg_value[PC] += 4;
		decode_instructions(ins_mem[(reg_value[(PC)]/4)-1]);
		snap << "cycle " << dec << i+1 << endl;
		show_change_reg();
		snap << endl << endl;
	}
    return 0;
}
