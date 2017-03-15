#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "instruction.h"
#include "regfile.h"
#include "memory.h"
using namespace std;
void decode_instructions(unsigned int in)
{
	unsigned int opcode = in >> 26;
	unsigned int rs = (in << 6) >> 27;
	unsigned int rt = (in << 11) >> 27;
	unsigned int rd = (in << 16) >> 27;
	unsigned int funct = (in << 26) >> 26;
	int C=(in << 16)>>16;
	long long int lli=0;
	unsigned long long int ulli=0;
	int tmp, tmp1;
	switch(opcode){
		//R-type Instructions
		case 0x00:
//			cout << "R-type Instructions" << endl;
			C = (in << 21) >> 27;
			switch(funct){
				case 0x20:
//					cout << "add $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] + reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x21:
//					cout << "addu $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = (unsigned int)reg_value[rs] + (unsigned int)reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x22:
//					cout << "sub $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] - reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x24:
//					cout << "and $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] & reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x25:
//					cout << "or $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] | reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x26:
//					cout << "xor $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] ^ reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x27:
//					cout << "nor $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = ~(reg_value[rs] | reg_value[rt]);
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x28:
//					cout << "nand $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = ~(reg_value[rs] & reg_value[rt]);
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x2a:
//					cout << "slt $" << rd << " $" << rs << " $" << rt << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] < reg_value[rt];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x00:
//					cout << "sll $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					tmp = reg_value[rd];
					reg_value[rd] = (unsigned int)reg_value[rt] << C;
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x02:
//					cout << "srl $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					tmp = reg_value[rd];
					reg_value[rd] = (unsigned int)reg_value[rt] >> C;
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x03:
//					cout << "sra $" << rd << " $" << rs << " " << setfill('0') << setw(4) << hex<< C << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rt] >> C;
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x08:
//					cout << "jr $" << rs << endl;
					reg_value[PC] = reg_value[rs];
				break;
				case 0x18:
//					cout << "mult $" << rs << " $" << rt << endl;
					tmp = reg_value[HI];
					tmp1 = reg_value[LO];
					lli = (long long int)reg_value[rs] * (long long int)reg_value[rt];
					reg_value[HI] = (unsigned long long int)lli >> 32;
					reg_value[LO] = ( (unsigned long long int)lli << 32) >> 32;
					if(tmp!=reg_value[HI]) changing_set.insert(HI);
					if(tmp1!=reg_value[LO]) changing_set.insert(LO);
				break;
				case 0x19:
//					cout << "multu $" << rs << " $" << rt << endl;
					tmp = reg_value[HI];
					tmp1 = reg_value[LO];
					ulli = (unsigned long long int)reg_value[rs] * (unsigned long long int)reg_value[rt];
					reg_value[HI] = ulli >> 32;
					reg_value[LO] = (ulli << 32) >> 32;
					if(tmp!=reg_value[HI]) changing_set.insert(HI);
					if(tmp1!=reg_value[LO]) changing_set.insert(LO);
				break;
				case 0x10:
//					cout << "mfhi $" << rd << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[HI];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
				case 0x12:
//					cout << "mflo $" << rd << endl;
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[LO];
					if(tmp!=reg_value[rd]) changing_set.insert(rd);
				break;
			}
			break;
		//I-type Instructions
		case 0x08:
//			cout << "addi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			if( C & 0x00008000){
				C = C | 0xFFFF0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] + C;
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x09:
//			cout << "addiu $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			tmp = reg_value[rt];
			reg_value[rt] = (unsigned int)reg_value[rs] + (unsigned int)C;
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x23:
//			cout << "lw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xffff0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,4);
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x21:
//			cout << "lh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xffff0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,2);
			if( reg_value[rt] & 0x00008000 ){
				reg_value[rt] = reg_value[rt] | 0xffff0000;
			}
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x25:
//			cout << "lhu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xffff0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,2);
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x20:
//			cout << "lb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xffff0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,1);
			if( reg_value[rt] & 0x00000080 ){
				reg_value[rt] = reg_value[rt] | 0xffffff00;
			}
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x24:
//			cout << "lbu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xFFFF0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,1);
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x2b:
//			cout << "sw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xFFFF0000;
			}
			break;
			save_data(reg_value[rs]+C, 4, reg_value[rt]);
		case 0x29:
//			cout << "sh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xFFFF0000;
			}
			save_data(reg_value[rs]+C, 2, reg_value[rt]);
			break;
		case 0x28:
//			cout << "sb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			if( C & 0x00008000){
				C = C | 0xFFFF0000;
			}
			save_data(reg_value[rs]+C, 1, reg_value[rt]);
			break;
		case 0x0f:
//			cout << "lui $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			tmp = reg_value[rt];
			reg_value[rt] = C << 16;
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x0c:
//			cout << "andi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] & C;
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x0d:
//			cout << "ori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] | C;
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x0e:
//			cout << "nori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			tmp = reg_value[rt];
			reg_value[rt] = ~(reg_value[rs] | C);
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x0a:
//			cout << "slti $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			if( C & 0x00008000 ){
				C = C | 0xffff0000;
			}
			tmp = reg_value[rt];
			reg_value[rt] = (reg_value[rs] < C);
			if(tmp!=reg_value[rt]) changing_set.insert(rt);
			break;
		case 0x04:
//			cout << "beq $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			if(reg_value[rs]==reg_value[rt]){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x05:
//			cout << "bne $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			if(reg_value[rs]!=reg_value[rt]){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x07:
//			cout << "bgtz $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			if(reg_value[rs]>0){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		//J-type Instructions
		case 0x02:
			C = (in << 6) >> 6;
//			cout << "j " << setfill('0') << setw(4) << hex << C << endl;
			reg_value[PC] = (reg_value[PC] & 0xF0000000) | (4*C);
			break;
		case 0x03:
			C = (in << 6) >> 6;
//			cout << "jal " << setfill('0') << setw(4) << hex << C << endl;
			tmp = reg_value[31];
			reg_value[31] = reg_value[PC];
			if(tmp!=reg_value[31]) changing_set.insert(31);
			reg_value[PC] = (reg_value[PC] & 0xF0000000) | (4*C);
			break;
		//Specialized Instruction
		case 0x3f:
//			cout << "halt" << endl;
			exit(0);
			break;
		//illegal Instructions
		default:
//			cout << "illegal" << endl;
			break;
	}
}
