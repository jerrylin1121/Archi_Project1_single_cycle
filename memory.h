#include <iostream>
#include <fstream>
using namespace std;
extern unsigned int PC_ini;
extern unsigned int ins_mem[256];
extern unsigned int num_of_ins;
extern unsigned int data_mem[1024];
extern unsigned int num_of_data;

void load_instruction(ifstream*);
void load_data(ifstream*);
unsigned int read_4_byte_int(ifstream*);
unsigned int read_byte_int(ifstream*);
int load_data(int, int);
void save_data(int, int, int);
