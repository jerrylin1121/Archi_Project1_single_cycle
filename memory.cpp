#include <iostream>
#include <fstream>
#include "memory.h"
using namespace std;
unsigned int PC_ini;
unsigned int *ins_mem;
unsigned int num_of_ins;
unsigned int *data_mem;
unsigned int num_of_data;
unsigned int read_4_byte_int(ifstream *in)
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
unsigned int read_byte_int(ifstream *in)
{
	unsigned int rt=0;
	in->read((char*)&rt,1);
	return rt;	
}
void load_instruction(ifstream *in)
{
	PC_ini = read_4_byte_int(in);
	num_of_ins = read_4_byte_int(in);
	ins_mem = new unsigned int[1024];
	for(int i=0; i<num_of_ins; ++i){
		ins_mem[i+PC_ini] = read_4_byte_int(in);
	}	
}
void load_data(ifstream *in)
{
	num_of_data = 4*read_4_byte_int(in);
	data_mem = new unsigned int[num_of_data];
	for(int i=0; i<num_of_data; ++i){
		data_mem[i] = read_byte_int(in);
	} 
}
