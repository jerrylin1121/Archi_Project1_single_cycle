#include <iostream>
#include <fstream>
#include "regfile.h"
#include "memory.h"
#include "error.h"
using namespace std;
unsigned int *ins_mem;
unsigned int num_of_ins;
unsigned int *data_mem;
unsigned int num_of_data;
extern fstream snap;
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
	reg_value[PC] = read_4_byte_int(in);
	num_of_ins = read_4_byte_int(in);
	ins_mem = new unsigned int[256];
	for(int i=0; i<num_of_ins; ++i){
		ins_mem[i+(reg_value[PC]/4)] = read_4_byte_int(in);
	}	
}
void load_data(ifstream *in)
{
	reg_value[29] = read_4_byte_int(in);
	num_of_data = 4*read_4_byte_int(in);
	data_mem = new unsigned int[1024];
	for(int i=0; i<num_of_data; ++i){
		data_mem[i] = read_byte_int(in);
	} 
}
int load_data(int index, int size)
{
	if(index+size-1 > 1023){
		mem_address_overflow();
	}
	if(index % size){
		data_misaligned();
	}
	int rt = data_mem[index];
	if(size>=2) rt = (rt<<8) + data_mem[index+1];
	if(size==4){
		rt = (rt<<16) + (data_mem[index+2]<<8) + data_mem[index+3];
	}
	return rt;
}
void save_data(int index, int size, int value)
{
	if(index % size){
		data_misaligned();
	}
	unsigned int _value = (unsigned int)value;
	if(size==1){
		data_mem[index] = _value & 0x000000ff;
	}else if(size==2){
		data_mem[index] = (_value & 0x0000ff00)>>8;
		data_mem[index+1] = (_value & 0x000000ff);
	}else if(size==4){
		data_mem[index] = (_value & 0xff000000)>>24;
		data_mem[index+1] = (_value & 0x00ff0000)>>16;
		data_mem[index+2] = (_value & 0x0000ff00)>>8;
		data_mem[index+3] = (_value & 0x000000ff);
	}
}
