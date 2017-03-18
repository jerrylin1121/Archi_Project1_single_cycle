#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "instruction.h"
#include "regfile.h"
#include "memory.h"
#include "error.h"
using namespace std;
extern fstream snap;
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
//			snap << "R-type Instructions" << endl;
			C = (in << 21) >> 27;
			switch(funct){
				case 0x20:
//					snap << "add $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);
					detect_number_overflow(reg_value[rs]>=0, reg_value[rt]>=0, (reg_value[rs]+reg_value[rt])>=0);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] + reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x21:
//					snap << "addu $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] + reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x22:
//					snap << "sub $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);
					detect_number_overflow(reg_value[rs]>=0, (-reg_value[rt])>=0, (reg_value[rs]-reg_value[rt])>=0);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] - reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x24:
//					snap << "and $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] & reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x25:
//					snap << "or $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);
				
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] | reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x26:
//					snap << "xor $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] ^ reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x27:
//					snap << "nor $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = ~(reg_value[rs] | reg_value[rt]);
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x28:
//					snap << "nand $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = ~(reg_value[rs] & reg_value[rt]);
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x2a:
//					snap << "slt $" << rd << " $" << rs << " $" << rt << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rs] < reg_value[rt];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x00:
//					snap << "sll $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					if(!( rd==0 && rt==0 && C==0 )){
						write_reg0(rd);

						tmp = reg_value[rd];
						reg_value[rd] = (unsigned int)reg_value[rt] << C;
						if(tmp!=reg_value[rd]) show_set.insert(rd);
					}
					break;
				case 0x02:
//					snap << "srl $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = (unsigned int)reg_value[rt] >> C;
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x03:
//					snap << "sra $" << rd << " $" << rs << " " << setfill('0') << setw(4) << hex<< C << endl;
					write_reg0(rd);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[rt] >> C;
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x08:
//					snap << "jr $" << rs << endl;
					reg_value[PC] = reg_value[rs];
					break;
				case 0x18:
//					snap << "mult $" << rs << " $" << rt << endl;
					overwrite_HI_LO(true);

					tmp = reg_value[HI];
					tmp1 = reg_value[LO];
					lli = ((long long int)reg_value[rs] * (long long int)reg_value[rt]);
					reg_value[HI] = lli >> 32;
					reg_value[LO] = lli;
					if(tmp!=reg_value[HI]) show_set.insert(HI);
					if(tmp1!=reg_value[LO]) show_set.insert(LO);
					break;
				case 0x19:
//					snap << "multu $" << rs << " $" << rt << endl;
					overwrite_HI_LO(true);

					tmp = reg_value[HI];
					tmp1 = reg_value[LO];
					ulli = ((unsigned long long int)(unsigned int)reg_value[rs] * (unsigned long long int)(unsigned int)reg_value[rt]);
					reg_value[HI] = ulli >> 32;
					reg_value[LO] = ulli;
					if(tmp!=reg_value[HI]) show_set.insert(HI);
					if(tmp1!=reg_value[LO]) show_set.insert(LO);
					break;
				case 0x10:
//					snap << "mfhi $" << rd << endl;
					write_reg0(rd);
					overwrite_HI_LO(false);
					
					tmp = reg_value[rd];
					reg_value[rd] = reg_value[HI];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				case 0x12:
//					snap << "mflo $" << rd << endl;
					write_reg0(rd);
					overwrite_HI_LO(false);

					tmp = reg_value[rd];
					reg_value[rd] = reg_value[LO];
					if(tmp!=reg_value[rd]) show_set.insert(rd);
					break;
				default:
//					snap << "illegal" << endl;
					cout << "illegal instruction found at 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC]-4 << endl;;
					exit(0);
					break;
			}
			break;
		//I-type Instructions
		case 0x08:
//			snap << "addi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);
			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] + C;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x09:
//			snap << "addiu $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);

			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] + C;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x23:
//			snap << "lw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);
			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);
			
			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,4);
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x21:
//			snap << "lh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);
			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,2);
			reg_value[rt] = (reg_value[rt] << 16) >> 16;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x25:
//	  		snap << "lhu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);
			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,2);
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x20:
//	  		snap << "lb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);
			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,1);
			reg_value[rt] = (reg_value[rt] << 24) >> 24;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x24:
//			snap << "lbu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);
			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			tmp = reg_value[rt];
			reg_value[rt] = load_data(reg_value[rs]+C,1);
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x2b:
//			snap << "sw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			save_data(reg_value[rs]+C, 4, reg_value[rt]);
			break;
		case 0x29:
//			snap << "sh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			save_data(reg_value[rs]+C, 2, reg_value[rt]);
			break;
		case 0x28:
//			snap << "sb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			C = (C << 16) >> 16;

			detect_number_overflow(reg_value[rs]>=0, C>=0, (reg_value[rs]+C)>=0);

			save_data(reg_value[rs]+C, 1, reg_value[rt]);
			break;
		case 0x0f:
//			snap << "lui $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			write_reg0(rt);

			tmp = reg_value[rt];
			reg_value[rt] = C << 16;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x0c:
//			snap << "andi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			write_reg0(rt);

			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] & C;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x0d:
//			snap << "ori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			write_reg0(rt);

			tmp = reg_value[rt];
			reg_value[rt] = reg_value[rs] | C;
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x0e:
//			snap << "nori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			write_reg0(rt);

			tmp = reg_value[rt];
			reg_value[rt] = ~(reg_value[rs] | C);
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x0a:
//			snap << "slti $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			C = (C << 16) >> 16;

			write_reg0(rt);

			tmp = reg_value[rt];
			reg_value[rt] = (reg_value[rs] < C);
			if(tmp!=reg_value[rt]) show_set.insert(rt);
			break;
		case 0x04:
//			snap << "beq $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			C = (C << 16) >> 16;

			detect_number_overflow(reg_value[PC]>=0, 4*C>=0, (reg_value[PC]+4*C)>=0);

			if(reg_value[rs]==reg_value[rt]){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x05:
//			snap << "bne $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			C = (C << 16) >> 16;

			detect_number_overflow(reg_value[PC]>=0, 4*C>=0, (reg_value[PC]+4*C)>=0);

			if(reg_value[rs]!=reg_value[rt]){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x07:
//			snap << "bgtz $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			C = (C << 16) >> 16;

			detect_number_overflow(reg_value[PC]>=0, 4*C>=0, (reg_value[PC]+4*C)>=0);

			if(reg_value[rs]>0){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		//J-type Instructions
		case 0x02:
//			snap << "j " << setfill('0') << setw(4) << hex << C << endl;
			C = (in << 6) >> 6;

			reg_value[PC] = (reg_value[PC] & 0xF0000000) | (4*C);
			break;
		case 0x03:
//			snap << "jal " << setfill('0') << setw(4) << hex << C << endl;
			C = (in << 6) >> 6;

			tmp = reg_value[31];
			reg_value[31] = reg_value[PC];
			if(tmp!=reg_value[31]) show_set.insert(31);
			reg_value[PC] = (reg_value[PC] & 0xF0000000) | (4*C);
			break;
		//Specialized Instruction
		case 0x3f:
//			snap << "halt" << endl;
			exit(0);
			break;
		//illegal Instructions
		default:
//			snap << "illegal" << endl;
			cout << "illegal instruction found at 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC]-4 << endl;
			exit(0);
			break;
	}
	reg_value[0] = 0;
	show_set.erase(0);
}
