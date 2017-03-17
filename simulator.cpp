#include <iostream>
#include <fstream>
#include <iomanip>
#include "instruction.h"
#include "memory.h"
#include "regfile.h"

using namespace std;
fstream snap("_snapshot.rpt", fstream::out);
int cycle = 0;
int main()
{
    ifstream iin("./iimage.bin", ios::in | ios::binary);
    ifstream din("./dimage.bin", ios::in | ios::binary);
	load_instruction(&iin);
	load_data(&din);
	snap << "cycle 0" << endl;
	show_all_reg();
	snap << endl << endl;
	while(++cycle){
		reg_value[PC] += 4;
		decode_instructions(ins_mem[(reg_value[(PC)]/4)-1]);
		snap << "cycle " << dec << cycle << endl;
		show_change_reg();
		snap << endl << endl;
	}
    return 0;
}
