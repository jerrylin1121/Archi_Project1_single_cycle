#include <iostream>
#include <iomanip>
#include "regfile.h"

unsigned int reg_value[35];

using namespace std;

void show_all_reg(void)
{
	for(unsigned int i=0; i<32; ++i){
		cout << "$" << setfill('0') << setw(2) << dec << i << ": 0x" << setfill('0') << setw(8) << hex << reg_value[i] << endl;
	}
		cout << "$HI: 0x" << setfill('0') << setw(8) << hex << reg_value[32] << endl;
		cout << "$LO: 0x" << setfill('0') << setw(8) << hex << reg_value[33] << endl;
		cout << "PC: 0x" << setfill('0') << setw(8) << hex << reg_value[34] << endl;
}

int read_reg_value(unsigned int index)
{
	return reg_value[index];
}

void set_reg_value(unsigned int index,unsigned int value)
{
	reg_value[index] = value;
}
