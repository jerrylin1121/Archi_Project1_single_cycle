#include <iostream>
#include <iomanip>
#include "instruction.h"
using namespace std;
void decode_instructions(unsigned int in)
{
	unsigned int opcode = in >> 26;
	unsigned int rs = (in << 6) >> 27;
	unsigned int rt = (in << 11) >> 27;
	unsigned int rd = (in << 16) >> 27;
	unsigned int funct = (in << 26) >> 26;
	unsigned int C=(in << 16)>>16;
	switch(opcode){
		//R-type Instructions
		case 0x00:
//			cout << "R-type Instructions" << endl;
			C = (in << 21) >> 27;
			switch(funct){
				case 0x20:
					cout << "add $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x21:
					cout << "addu $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x22:
					cout << "sub $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x24:
					cout << "and $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x25:
					cout << "or $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x26:
					cout << "xor $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x27:
					cout << "nor $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x28:
					cout << "nand $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x2a:
					cout << "slt $" << rd << " $" << rs << " $" << rt << endl;
				break;
				case 0x00:
					cout << "sll $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
				break;
				case 0x02:
					cout << "srl $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
				break;
				case 0x03:
					cout << "sra $" << rd << " $" << rs << " " << setfill('0') << setw(4) << hex<< C << endl;
				break;
				case 0x08:
					cout << "jr $" << rs << endl;
				break;
				case 0x18:
					cout << "mult $" << rs << " $" << rt << endl;
				break;
				case 0x19:
					cout << "multu $" << rs << " $" << rt << endl;
				break;
				case 0x10:
					cout << "mfhi $" << rd << endl;
				break;
				case 0x12:
					cout << "mflo $" << rd << endl;
				break;
			}
			break;
		//I-type Instructions
		case 0x08:
			cout << "addi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x09:
			cout << "addiu $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x23:
			cout << "lw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x21:
			cout << "lh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x25:
			cout << "lhu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x20:
			cout << "lb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x24:
			cout << "lbu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x2b:
			cout << "sw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x29:
			cout << "sh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x28:
			cout << "sb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			break;
		case 0x0f:
			cout << "lui $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x0c:
			cout << "andi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x0d:
			cout << "ori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x0e:
			cout << "nori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x0a:
			cout << "slti $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x04:
			cout << "beqi $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x05:
			cout << "bnei $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x07:
			cout << "bgtzi $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			break;
		//J-type Instructions
		case 0x02:
			C = (in << 6) >> 6;
			cout << "j " << setfill('0') << setw(4) << hex << C << endl;
			break;
		case 0x03:
			cout << "jal " << setfill('0') << setw(4) << hex << C << endl;
			break;
		//Specialized Instruction
		case 0x3f:
			cout << "halt" << endl;
			break;
		//illegal Instructions
		default:
			cout << "illegal" << endl;
			break;
	}
}
