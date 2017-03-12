#include <iostream>
#include <fstream>
#include <iomanip>
#include "instruction.h"
using namespace std;

unsigned int read_binary_int(ifstream *in)
{
   	unsigned int c=0, rt=0;
    in->read((char*)&c,1);
    rt+=c;
    in->read((char*)&c,1);
    rt=(rt<<8) + c;
    in->read((char*)&c,1);
    rt=(rt<<8) + c;
    in->read((char*)&c,1);
    rt=(rt<<8) + c;
    return rt;
}

int main(int argc, char *argv[])
{
    ifstream iin(argv[1], ios::in | ios::binary);
    ifstream din(argv[2], ios::in | ios::binary);
	unsigned int ins, N;
	ins = read_binary_int(&iin);
	N = read_binary_int(&iin);
	cout << "N = " << N << endl;
	for(int i=0; i<N; ++i){
		ins = read_binary_int(&iin);
		decode_instructions(ins);
	}
    return 0;
}
