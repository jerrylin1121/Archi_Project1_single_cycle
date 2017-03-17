#include <iostream>
#include <fstream>
#include <iomanip>
#include "instruction.h"
#include "memory.h"
#include "regfile.h"

using namespace std;
fstream snap("_snapshot.rpt", fstream::out);
int cycle = 0;
bool halt = false;

int main()
{
    ifstream iin("./iimage.bin", ios::in | ios::binary);
    ifstream din("./dimage.bin", ios::in | ios::binary);
	load_instruction(&iin);
	load_data(&din);
	for(int i=0; i<34; ++i){
		show_set.insert(i);
	}
	while(!halt){
		snap << "cycle " << dec << cycle << endl;
		show_reg();
		snap << endl << endl;
		++cycle;
		reg_value[PC] += 4;
		decode_instructions(ins_mem[(reg_value[(PC)]/4)-1]);
	}
    return 0;
}
