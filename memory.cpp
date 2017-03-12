#include <iostream>
#include <fstream>
#include "memory.h"
using namespace std;
unsigned int *ins_mem;
unsigned int num_of_ins;
unsigned int *data_mem;
unsigned int num_of_data;
unsigned int read_binary_int(ifstream *in)
{
	unsigned int c=0, rt=0;
	in->read((char*)&c,1);
	rt+=c;
	in->read((char*)&c,1);
	rt=(rt<<8)+c;
	in->read((char*)&c,1);
	rt=(rt<<8)+c;
	in->read((char*)&c,1);
	rt=(rt<<8)+c;
	return rt;	
}
void load_instruction(ifstream *in)
{
	num_of_ins = read_binary_int(in);
	ins_mem = new unsigned int[num_of_ins];
	for(int i=0; i<num_of_ins; ++i){
		ins_mem[i] = read_binary_int(in);
	}	
}
void load_data(ifstream *in)
{
	num_of_data = read_binary_int(in);
	data_mem = new unsigned int[num_of_data];
	for(int i=0; i<num_of_data; ++i){
		data_mem[i] = read_binary_int(in);
	} 
}
