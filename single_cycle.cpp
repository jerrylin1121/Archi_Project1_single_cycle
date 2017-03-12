#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int read_binary_int(ifstream *in)
{
    int c=0, rt=0;
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
    while(!iin.eof()){
        cout << setfill('0') << setw(8) << hex << read_binary_int(&iin) << endl;
    }
    return 0;
}
