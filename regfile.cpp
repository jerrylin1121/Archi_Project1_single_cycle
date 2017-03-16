#include <iostream>
#include <iomanip>
#include <fstream>
#include "regfile.h"

using namespace std;

int reg_value[35];
set<int> changing_set;
extern fstream snap;

void show_all_reg(void)
{
	for(unsigned int i=0; i<32; ++i){
		snap << "$" << setfill('0') << setw(2) << dec << i << ": 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[i] << endl;
	}
		snap << "$HI: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[HI] << endl;
		snap << "$LO: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[LO] << endl;
		snap << "PC: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC] << endl;
}

void show_change_reg(void)
{
	for(set<int>::iterator it = changing_set.begin(); it!=changing_set.end(); ++it){
		if(*it <= 31)
			snap << "$" << setfill('0') << setw(2) << dec << *it << ": 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[*it] << endl;
		if(*it==HI)
			snap << "$HI: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[HI] << endl;
		if(*it==LO)
			snap << "$LO: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[LO] << endl;
	}
	snap << "PC: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC] << endl;
	changing_set.clear();
}
