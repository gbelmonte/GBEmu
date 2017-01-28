int CPU::NOP() {
	Logger::LogInstruction("NOP", "", ""); 
	return 4; 
}

int CPU::STOP() {
	Logger::LogInstruction("STOP", "", ""); 
	return 4;
}

int CPU::HALT() {
	Logger::LogInstruction("HALT", "", ""); 
	halt = true;
	return 4;
}

int CPU::LD_A_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "A", "immediate");
	this->AF.hi = immediate;
	return 8;
}

int CPU::LD_B_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "B", "immediate");
	this->BC.hi = immediate;
	return 8;
} 

int CPU::LD_C_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "C", "immediate");
	this->BC.lo = immediate;
	return 8;
}

int CPU::LD_D_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "D", "immediate");
	this->DE.hi = immediate;
	return 8;
} 

int CPU::LD_E_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "E", "immediate");
	this->DE.lo = immediate;
	return 8;
}

int CPU::LD_H_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "H", "immediate");
	this->HL.hi = immediate;
	return 8;
} 

int CPU::LD_L_n(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("LD", "L", "immediate");
	this->HL.lo = immediate;
	return 8;
}

int CPU::LD_A_A() {
	Logger::LogInstruction("LD", "A", "A");
	return 4;
}

int CPU::LD_A_B() {
	this->AF.hi = this->BC.hi;
	Logger::LogInstruction("LD", "A", "B");
	return 4;
}

int CPU::LD_A_C() {
	this->AF.hi = this->BC.lo;
	Logger::LogInstruction("LD", "A", "C");
	return 4;
}

int CPU::LD_A_D() {
	this->AF.hi = this->DE.hi;
	Logger::LogInstruction("LD", "A", "D");
	return 4;
}

int CPU::LD_A_E() {
	this->AF.hi = this->DE.lo;
	Logger::LogInstruction("LD", "A", "E");
	return 4;
}

int CPU::LD_A_H() {
	this->AF.hi = this->HL.hi;
	Logger::LogInstruction("LD", "A", "H");
	return 4;
}

int CPU::LD_A_L() {
	this->AF.hi = this->HL.lo;
	Logger::LogInstruction("LD", "A", "L");
	return 4;
}

int CPU::LD_A_BC() {
	this->AF.hi = this->memory.readByte(this->BC.reg);
	Logger::LogInstruction("LD", "A", "(BC)");
	return 8;
}

int CPU::LD_A_DE() {
	this->AF.hi = this->memory.readByte(this->DE.reg);
	Logger::LogInstruction("LD", "A", "(DE)");
	return 8;
}

int CPU::LD_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "A", "(HL)");
	return 8;
}

int CPU::LD_A_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	UpdateCPUCycles(8);
	this->AF.hi = this->memory.readByte(address);
	Logger::LogInstruction("LD", "A", "nn");
	return 8;
}

int CPU::LD_B_B() {
	this->BC.hi = this->BC.hi;
	Logger::LogInstruction("LD", "B", "B");
	return 4;
}

int CPU::LD_B_C() {
	this->BC.hi = this->BC.lo;
	Logger::LogInstruction("LD", "B", "C");
	return 4;
}

int CPU::LD_B_D() {
	this->BC.hi = this->DE.hi;
	Logger::LogInstruction("LD", "B", "D");
	return 4;
}

int CPU::LD_B_E() {
	this->BC.hi = this->DE.lo;
	Logger::LogInstruction("LD", "B", "E");
	return 4;
}

int CPU::LD_B_H() {
	this->BC.hi = this->HL.hi;
	Logger::LogInstruction("LD", "B", "H");
	return 4;
}

int CPU::LD_B_L() {
	this->BC.hi = this->HL.lo;
	Logger::LogInstruction("LD", "B", "L");
	return 4;
}

int CPU::LD_B_HL() {
	this->BC.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "B", "(HL)");
	return 8;
}

int CPU::LD_C_B() {
	this->BC.lo = this->BC.hi;
	Logger::LogInstruction("LD", "C", "B");
	return 4;
}

int CPU::LD_C_C() {
	this->BC.lo = this->BC.lo;
	Logger::LogInstruction("LD", "C", "C");
	return 4;
}

int CPU::LD_C_D() {
	this->BC.lo = this->DE.hi;
	Logger::LogInstruction("LD", "C", "D");
	return 4;
}

int CPU::LD_C_E() {
	this->BC.lo = this->DE.lo;
	Logger::LogInstruction("LD", "C", "E");
	return 4;
}

int CPU::LD_C_H() {
	this->BC.lo = this->HL.hi;
	Logger::LogInstruction("LD", "C", "H");
	return 4;
}

int CPU::LD_C_L() {
	this->BC.lo = this->HL.lo;
	Logger::LogInstruction("LD", "C", "L");
	return 4;
}

int CPU::LD_C_HL() {
	this->BC.lo = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "C", "(HL)");
	return 8;
}

int CPU::LD_D_B() {
	this->DE.hi = this->BC.hi;
	Logger::LogInstruction("LD", "D", "B");
	return 4;
}

int CPU::LD_D_C() {
	this->DE.hi = this->BC.lo;
	Logger::LogInstruction("LD", "D", "C");
	return 4;
}

int CPU::LD_D_D() {
	this->DE.hi = this->DE.hi;
	Logger::LogInstruction("LD", "D", "D");
	return 4;
}

int CPU::LD_D_E() {
	this->DE.hi = this->DE.lo;
	Logger::LogInstruction("LD", "D", "E");
	return 4;
}

int CPU::LD_D_H() {
	this->DE.hi = this->HL.hi;
	Logger::LogInstruction("LD", "D", "H");
	return 4;
}

int CPU::LD_D_L() {
	this->DE.hi = this->HL.lo;
	Logger::LogInstruction("LD", "D", "L");
	return 4;
}

int CPU::LD_D_HL() {
	this->DE.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "D", "(HL)");
	return 8;
}


int CPU::LD_E_B() {
	this->DE.lo = this->BC.hi;
	Logger::LogInstruction("LD", "E", "B");
	return 4;
}

int CPU::LD_E_C() {
	this->DE.lo = this->BC.lo;
	Logger::LogInstruction("LD", "E", "C");
	return 4;
}

int CPU::LD_E_D() {
	this->DE.lo = this->DE.hi;
	Logger::LogInstruction("LD", "E", "D");
	return 4;
}

int CPU::LD_E_E() {
	this->DE.lo = this->DE.lo;
	Logger::LogInstruction("LD", "E", "E");
	return 4;
}

int CPU::LD_E_H() {
	this->DE.lo = this->HL.hi;
	Logger::LogInstruction("LD", "E", "H");
	return 4;
}

int CPU::LD_E_L() {
	this->DE.lo = this->HL.lo;
	Logger::LogInstruction("LD", "E", "L");
	return 4;
}

int CPU::LD_E_HL() {
	this->DE.lo = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "E", "(HL)");
	return 8;
}

int CPU::LD_H_B() {
	this->HL.hi = this->BC.hi;
	Logger::LogInstruction("LD", "H", "B");
	return 4;
}

int CPU::LD_H_C() {
	this->HL.hi = this->BC.lo;
	Logger::LogInstruction("LD", "H", "C");
	return 4;
}

int CPU::LD_H_D() {
	this->HL.hi = this->DE.hi;
	Logger::LogInstruction("LD", "H", "D");
	return 4;
}

int CPU::LD_H_E() {
	this->HL.hi = this->DE.lo;
	Logger::LogInstruction("LD", "H", "E");
	return 4;
}

int CPU::LD_H_H() {
	this->HL.hi = this->HL.hi;
	Logger::LogInstruction("LD", "H", "H");
	return 4;
}

int CPU::LD_H_L() {
	this->HL.hi = this->HL.lo;
	Logger::LogInstruction("LD", "H", "L");
	return 4;
}

int CPU::LD_H_HL() {
	this->HL.hi = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "H", "(HL)");
	return 8;
}

int CPU::LD_L_B() {
	this->HL.lo = this->BC.hi;
	Logger::LogInstruction("LD", "L", "B");
	return 4;
}

int CPU::LD_L_C() {
	this->HL.lo = this->BC.lo;
	Logger::LogInstruction("LD", "L", "C");
	return 4;
}

int CPU::LD_L_D() {
	this->HL.lo = this->DE.hi;
	Logger::LogInstruction("LD", "L", "D");
	return 4;
}

int CPU::LD_L_E() {
	this->HL.lo = this->DE.lo;
	Logger::LogInstruction("LD", "L", "E");
	return 4;
}

int CPU::LD_L_H() {
	this->HL.lo = this->HL.hi;
	Logger::LogInstruction("LD", "L", "H");
	return 4;
}

int CPU::LD_L_L() {
	this->HL.lo = this->HL.lo;
	Logger::LogInstruction("LD", "L", "L");
	return 4;
}

int CPU::LD_L_HL() {
	this->HL.lo = this->memory.readByte(this->HL.reg);
	Logger::LogInstruction("LD", "L", "(HL)");
	return 8;
}

int CPU::LD_B_A() {
	this->BC.hi = this->AF.hi;
	Logger::LogInstruction("LD", "B", "A");
	return 4;
}

int CPU::LD_C_A() {
	this->BC.lo = this->AF.hi;
	Logger::LogInstruction("LD", "C", "A");
	return 4;
}

int CPU::LD_D_A() {
	this->DE.hi = this->AF.hi;
	Logger::LogInstruction("LD", "D", "A");
	return 4;
}

int CPU::LD_E_A() {
	this->DE.lo = this->AF.hi;
	Logger::LogInstruction("LD", "E", "A");
	return 4;
}

int CPU::LD_H_A() {
	this->HL.hi = this->AF.hi;
	Logger::LogInstruction("LD", "H", "A");
	return 4;
}

int CPU::LD_L_A() {
	this->HL.lo = this->AF.hi;
	Logger::LogInstruction("LD", "L", "A");
	return 4;
}

int CPU::LD_BC_A() {
	this->memory.writeByte(this->BC.reg, this->AF.hi);
	Logger::LogInstruction("LD", "(BC)", "A");
	return 8;
}

int CPU::LD_DE_A() {
	this->memory.writeByte(this->DE.reg, this->AF.hi);
	Logger::LogInstruction("LD", "(DE)", "A");
	return 8;
}

int CPU::LD_nn_A() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	UpdateCPUCycles(8);
	this->PC.reg+=2;
	this->memory.writeByte(immediate, this->AF.hi);
	Logger::LogInstruction("LD", "(nn)", "A");
	return 8;
}

int CPU::LD_HL_A() {
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	Logger::LogInstruction("LD", "(HL)", "A");
	return 8;
}

int CPU::LD_HL_B() {
	this->memory.writeByte(this->HL.reg, this->BC.hi);
	Logger::LogInstruction("LD", "(HL)", "B");
	return 8;
}

int CPU::LD_HL_C() {
	this->memory.writeByte(this->HL.reg, this->BC.lo);
	Logger::LogInstruction("LD", "(HL)", "C");
	return 8;
}

int CPU::LD_HL_D() {
	this->memory.writeByte(this->HL.reg, this->DE.hi);
	Logger::LogInstruction("LD", "(HL)", "D");
	return 8;
}

int CPU::LD_HL_E() {
	this->memory.writeByte(this->HL.reg, this->DE.lo);
	Logger::LogInstruction("LD", "(HL)", "E");
	return 8;
}

int CPU::LD_HL_H() {
	this->memory.writeByte(this->HL.reg, this->HL.hi);
	Logger::LogInstruction("LD", "(HL)", "H");
	return 8;
}

int CPU::LD_HL_L() {
	this->memory.writeByte(this->HL.reg, this->HL.lo);
	Logger::LogInstruction("LD", "(HL)", "L");
	return 8;
}

int CPU::LD_HL_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	UpdateCPUCycles(4);
	this->PC.reg++;
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("LD", "(HL)", "imm");
	return 8;
}

int CPU::LD_A_FF00_C() {
	WORD address = 0xFF00 + this->BC.lo;
	BYTE value = this->memory.readByte(address);
	this->AF.hi = value;
	Logger::LogInstruction("LD", "A", "(FF00 + C)");
	return 8;
}

int CPU::LD_FF00_C_A(){
	WORD address = 0xFF00 + this->BC.lo;
	this->memory.writeByte(address, this->AF.hi);
	Logger::LogInstruction("LD", "($FF00 + C)", "A");
	return 8;
}

int CPU::LD_FF00_n_A(){
	BYTE immediate = this->memory.readByte(this->PC.reg);
	UpdateCPUCycles(4);
	this->PC.reg++;
	WORD address = 0xFF00 + immediate;
	this->memory.writeByte(address, this->AF.hi);
	Logger::LogInstruction("LD", "($FF00 + imm)", "A");
	return 8;
}

int CPU::LDH_A_FF00_n() {
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	UpdateCPUCycles(4);
	WORD address = 0xFF00 + immediate;
	this->AF.hi = this->memory.readByte(address);
	Logger::LogInstruction("LDH", "A", "($FF00 + imm)");
	return 8;
}

int CPU::LDHL_SP_n() {
	SIGNED_BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->HL.reg = Add16BitSigned(this->SP.reg, immediate);
	Logger::LogInstruction("LDHL", "SP", "n");
	return 12;
}

int CPU::LDD_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg--;
	Logger::LogInstruction("LDD", "(HL)", "A");
	return 8;
}

int CPU::LDD_A_HL(){
	this->AF.hi = this->memory.readByte(this->HL.reg);
	this->HL.reg--;
	Logger::LogInstruction("LDD", "A", "(HL)");
	return 8;
}

int CPU::LDI_HL_A(){
	this->memory.writeByte(this->HL.reg, this->AF.hi);
	this->HL.reg++;
	Logger::LogInstruction("LDI", "HL", "A");
	return 8;
}

int CPU::LDI_A_HL() {
	this->AF.hi = this->memory.readByte(this->HL.reg);
	this->HL.reg++;
	Logger::LogInstruction("LDI", "A", "(HL)");
	return 8;
}

int CPU::LD_SP_HL() {
	this->SP.reg = this->HL.reg;
	Logger::LogInstruction("LD", "SP", "HL");
	return 8;
}

int CPU::LD_BC_nn(){
	this->BC.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "BC", "nn");
	return 12;
}

int CPU::LD_DE_nn(){
	this->DE.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "DE", "nn");
	return 12;
}

int CPU::LD_HL_nn(){
	this->HL.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "HL", "nn");
	return 12;
}

int CPU::LD_SP_nn(){
	this->SP.reg = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("LD", "SP", "nn");
	return 12;
}

int CPU::LD_nn_SP() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	this->memory.writeByte(address, this->SP.lo);
	this->memory.writeByte(address+1, this->SP.hi);
	Logger::LogInstruction("LD", "nn", "SP");
	return 20;
}

//Jump Instructions
int CPU::JR_NZ() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "NZ", "");
	if (getFlag(Flag::z) == 0) {
		this->PC.reg += offset;
		Logger::Log("Jump taken");
		return 12;
	}
	return 8;
}

int CPU::JR_Z() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "Z", "");
	if (getFlag(Flag::z) == 1) {
		this->PC.reg += offset;
		Logger::Log("Jump taken");
		return 12;
	}
	return 8;
}

int CPU::JR_NC() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "NC", "");
	if (getFlag(Flag::c) == 0) {
		this->PC.reg += offset;
		Logger::Log("Jump taken");
		return 12;
	}
	return 8;
}

int CPU::JR_C() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "C", "");
	if (getFlag(Flag::c) == 1) {
		this->PC.reg += offset;
		Logger::Log("Jump taken");
		return 12;
	}
	return 8;
}

int CPU::JR() {
	SIGNED_BYTE offset = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Logger::LogInstruction("JR", "", "");
	this->PC.reg += offset;
	Logger::Log("Jump taken");
	return 12;
}

int CPU::JP_nn() {
	WORD address = this->memory.readWord(this->PC.reg);
	Logger::LogInstruction("JP", "nn", "");
	this->PC.reg = address;
	return 16;
}

int CPU::JP_NZ() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "NZ", "");
	if (getFlag(Flag::z) == 0) {
		this->PC.reg = address;
		Logger::Log("Jump taken");
		return 16;
	}
	return 12;
}

int CPU::JP_Z() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "Z", "");
	if (getFlag(Flag::z) == 1) {
		this->PC.reg = address;
		Logger::Log("Jump taken");
		return 16;
	}
	return 12;
}

int CPU::JP_NC() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "NC", "");
	if (getFlag(Flag::c) == 0) {
		this->PC.reg = address;
		Logger::Log("Jump taken");
		return 16;
	}
	return 12;
}

int CPU::JP_C() {
	WORD address = this->memory.readWord(this->PC.reg);
	this->PC.reg += 2;
	Logger::LogInstruction("JP", "C", "");
	if (getFlag(Flag::c) == 1) {
		this->PC.reg = address;
		Logger::Log("Jump taken");
		return 16;
	}
	return 12;
}


int CPU::JP_HL() {
	Logger::LogInstruction("JP", "HL", "");
	this->PC.reg = this->HL.reg;
	return 4;
}

int CPU::CALL_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	PushReg(this->PC.reg);
	this->PC.reg = immediate;
	Logger::LogInstruction("Call", "nn", "");
	return 24;
}

int CPU::CALL_NZ_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "NZ", "nn");
	if (getFlag(Flag::z) == 0) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		Logger::Log("Call taken");
		return 24;
	}
	return 12;
}

int CPU::CALL_Z_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "Z", "nn");
	if (getFlag(Flag::z) == 1) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		Logger::Log("Call taken");
		return 24;
	}
	return 12;
}

int CPU::CALL_NC_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "NC", "nn");
	if (getFlag(Flag::c) == 0) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		Logger::Log("Call taken");
		return 24;
	}
	return 12;
}

int CPU::CALL_C_nn() {
	WORD immediate = this->memory.readWord(this->PC.reg);
	this->PC.reg+=2;
	Logger::LogInstruction("Call", "C", "nn");
	if (getFlag(Flag::c) == 1) {
		PushReg(this->PC.reg);
		this->PC.reg = immediate;
		Logger::Log("Call taken");
		return 24;
	}
	return 12;
}


int CPU::RET() {
	this->PC.reg = PopReg();
	Logger::LogInstruction("RET", "", "");
	return 16;
}

int CPU::RET_NZ() {
	Logger::LogInstruction("RET", "NZ", "");
	if (getFlag(Flag::z) == 0) {
		this->PC.reg = PopReg();
		Logger::Log("Ret taken");
		return 20;
	}
	return 8;
}

int CPU::RET_Z() {
	Logger::LogInstruction("RET", "Z", "");
	if (getFlag(Flag::z) == 1) {
		this->PC.reg = PopReg();
		Logger::Log("Ret taken");
		return 20;
	}
	return 8;
}

int CPU::RET_NC() {
	Logger::LogInstruction("RET", "NC", "");
	if (getFlag(Flag::c) == 0) {
		this->PC.reg = PopReg();
		Logger::Log("Ret taken");
		return 20;
	}
	return 8;
}

int CPU::RET_C() {
	Logger::LogInstruction("RET", "C", "");
	if (getFlag(Flag::c) == 1) {
		this->PC.reg = PopReg();
		Logger::Log("Ret taken");
		return 20;
	}
	return 8;
}

int CPU::RETI() {
	this->PC.reg = PopReg();
	this->interruptEnabled = true;
	Logger::LogInstruction("RETI", "", "");
	return 16;
}

int CPU::PUSH_AF() {
	PushReg(this->AF.reg);
	Logger::LogInstruction("PUSH", "AF", "");
	return 16;
}

int CPU::PUSH_BC() {
	PushReg(this->BC.reg);
	Logger::LogInstruction("PUSH", "BC", "");
	return 16;
}

int CPU::PUSH_DE() {
	PushReg(this->DE.reg);
	Logger::LogInstruction("PUSH", "DE", "");
	return 16;
}

int CPU::PUSH_HL() {
	PushReg(this->HL.reg);
	Logger::LogInstruction("PUSH", "HL", "");
	return 16;
}

int CPU::POP_AF() {
	this->AF.reg = PopReg();
	//Clear lower nibble of F reg because they can never be set
	this->AF.lo = this->AF.lo & 0xF0;
	Logger::LogInstruction("POP", "AF", "");
	return 12;
}

int CPU::POP_BC() {
	this->BC.reg = PopReg();
	Logger::LogInstruction("POP", "BC", "");
	return 12;
}

int CPU::POP_DE() {
	this->DE.reg = PopReg();
	Logger::LogInstruction("POP", "DE", "");
	return 12;
}

int CPU::POP_HL() {
	this->HL.reg = PopReg();
	Logger::LogInstruction("POP", "HL", "");
	return 12;
}

int CPU::RST_00() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0000;
	Logger::LogInstruction("RST", "00", "");
	return 16;
}

int CPU::RST_08() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0008;
	Logger::LogInstruction("RST", "08", "");
	return 16;
}

int CPU::RST_10() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0010;
	Logger::LogInstruction("RST", "10", "");
	return 16;
}

int CPU::RST_18() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0018;
	Logger::LogInstruction("RST", "18", "");
	return 16;
}

int CPU::RST_20() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0020;
	Logger::LogInstruction("RST", "20", "");
	return 16;
}

int CPU::RST_28() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0028;
	Logger::LogInstruction("RST", "28", "");
	return 16;
}

int CPU::RST_30() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0030;
	Logger::LogInstruction("RST", "30", "");
	return 16;
}

int CPU::RST_38() {
	PushReg(this->PC.reg);
	this->PC.reg = 0x0038;
	Logger::LogInstruction("RST", "38", "");
	return 16;
}

//Add instructions
int CPU::ADD_A() {
	this->AF.hi = Add(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Add", "A", "");
	return 4;
}

int CPU::ADD_B() {
	this->AF.hi = Add(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Add", "B", "");
	return 4;
}

int CPU::ADD_C() {
	this->AF.hi = Add(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Add", "C", "");
	return 4;
}

int CPU::ADD_D() {
	this->AF.hi = Add(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Add", "D", "");
	return 4;
}

int CPU::ADD_E() {
	this->AF.hi = Add(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Add", "E", "");
	return 4;
}

int CPU::ADD_H() {
	this->AF.hi = Add(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Add", "H", "");
	return 4;
}

int CPU::ADD_L() {
	this->AF.hi = Add(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Add", "L", "");
	return 4;
}

int CPU::ADD_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	this->AF.hi = Add(this->AF.hi, value);
	Logger::LogInstruction("Add", "(HL)", "");
	return 8;
}

int CPU::ADD_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Add(this->AF.hi, value);
	Logger::LogInstruction("Add", "imm", "");
	return 8;
}

int CPU::ADD_HL_BC() {
	this->HL.reg = Add16Bit(this->HL.reg, this->BC.reg);
	Logger::LogInstruction("Add", "HL", "BC");
	return 8;
}

int CPU::ADD_HL_DE() {
	this->HL.reg = Add16Bit(this->HL.reg, this->DE.reg);
	Logger::LogInstruction("Add", "HL", "DE");
	return 8;
}

int CPU::ADD_HL_HL() {
	this->HL.reg = Add16Bit(this->HL.reg, this->HL.reg);
	Logger::LogInstruction("Add", "HL", "HL");
	return 8;
}

int CPU::ADD_HL_SP() {
	this->HL.reg = Add16Bit(this->HL.reg, this->SP.reg);
	Logger::LogInstruction("Add", "HL", "SP");
	return 8;
}

int CPU::ADD_SP_n() {
	SIGNED_BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->SP.reg = Add16BitSigned(this->SP.reg, immediate);
	Logger::LogInstruction("Add", "SP", "n");
	return 16; 
}

int CPU::ADC_A() {
	this->AF.hi = Add(this->AF.hi, this->AF.hi, true);
	Logger::LogInstruction("Adc", "A", "");
	return 4;
}

int CPU::ADC_B() {
	this->AF.hi = Add(this->AF.hi, this->BC.hi, true);
	Logger::LogInstruction("Adc", "B", "");
	return 4;
}

int CPU::ADC_C() {
	this->AF.hi = Add(this->AF.hi, this->BC.lo, true);
	Logger::LogInstruction("Adc", "C", "");
	return 4;
}

int CPU::ADC_D() {
	this->AF.hi = Add(this->AF.hi, this->DE.hi, true);
	Logger::LogInstruction("Adc", "D", "");
	return 4;
}

int CPU::ADC_E() {
	this->AF.hi = Add(this->AF.hi, this->DE.lo, true);
	Logger::LogInstruction("Adc", "E", "");
	return 4;
}

int CPU::ADC_H() {
	this->AF.hi = Add(this->AF.hi, this->HL.hi, true);
	Logger::LogInstruction("Adc", "H", "");
	return 4;
}

int CPU::ADC_L() {
	this->AF.hi = Add(this->AF.hi, this->HL.lo, true);
	Logger::LogInstruction("Adc", "L", "");
	return 4;
}

int CPU::ADC_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	this->AF.hi = Add(this->AF.hi, value, true);
	Logger::LogInstruction("Adc", "(HL)", "");
	return 8;
}

int CPU::ADC_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Add(this->AF.hi, value, true);
	Logger::LogInstruction("Adc", "imm", "");
	return 8;	
}

int CPU::SUB_A() {
	this->AF.hi = Subtract(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Sub", "A", "");
	return 4;
}

int CPU::SUB_B() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Sub", "B", "");
	return 4;
}

int CPU::SUB_C() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Sub", "C", "");
	return 4;
}

int CPU::SUB_D() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Sub", "D", "");
	return 4;
}

int CPU::SUB_E() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Sub", "E", "");
	return 4;
}

int CPU::SUB_H() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Sub", "H", "");
	return 4;
}

int CPU::SUB_L() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Sub", "L", "");
	return 4;
}

int CPU::SUB_HL() {
	this->AF.hi = Subtract(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("Sub", "(HL)", "");
	return 8;
}

int CPU::SUB_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Subtract(this->AF.hi, value);
	Logger::LogInstruction("Sub", "imm", "");
	return 8;
}

int CPU::SBC_A() {
	this->AF.hi = Subtract(this->AF.hi, this->AF.hi, true);
	Logger::LogInstruction("Sbc", "A", "");
	return 4;
}

int CPU::SBC_B() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.hi, true);
	Logger::LogInstruction("Sbc", "B", "");
	return 4;
}

int CPU::SBC_C() {
	this->AF.hi = Subtract(this->AF.hi, this->BC.lo, true);
	Logger::LogInstruction("Sbc", "C", "");
	return 4;
}

int CPU::SBC_D() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.hi, true);
	Logger::LogInstruction("Sbc", "D", "");
	return 4;
}

int CPU::SBC_E() {
	this->AF.hi = Subtract(this->AF.hi, this->DE.lo, true);
	Logger::LogInstruction("Sbc", "E", "");
	return 4;
}

int CPU::SBC_H() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.hi, true);
	Logger::LogInstruction("Sbc", "H", "");
	return 4;
}

int CPU::SBC_L() {
	this->AF.hi = Subtract(this->AF.hi, this->HL.lo, true);
	Logger::LogInstruction("Sbc", "L", "");
	return 4;
}

int CPU::SBC_HL() {
	this->AF.hi = Subtract(this->AF.hi, this->memory.readByte(this->HL.reg), true);
	Logger::LogInstruction("Sbc", "(HL)", "");
	return 8;
}

int CPU::SBC_n() {
	BYTE value = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	this->AF.hi = Subtract(this->AF.hi, value, true);
	Logger::LogInstruction("Sbc", "imm", "");
	return 8;
}

int CPU::XOR_A() {
	this->AF.hi = XOR(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Xor", "A", "");
	return 4;
}

int CPU::XOR_B() {
	this->AF.hi = XOR(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Xor", "B", "");
	return 4;
}

int CPU::XOR_C() {
	this->AF.hi = XOR(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Xor", "C", "");
	return 4;
}

int CPU::XOR_D() {
	this->AF.hi = XOR(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Xor", "D", "");
	return 4;
}

int CPU::XOR_E() {
	this->AF.hi = XOR(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Xor", "E", "");
	return 4;
}

int CPU::XOR_H() {
	this->AF.hi = XOR(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Xor", "H", "");
	return 4;
}

int CPU::XOR_L() {
	this->AF.hi = XOR(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Xor", "L", "");
	return 4;
}

int CPU::XOR_HL() {
	this->AF.hi = XOR(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("Xor", "(HL)", "");
	return 8;	
}

int CPU::XOR_n() {
	this->AF.hi = XOR(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	Logger::LogInstruction("Xor", "imm", "");
	return 8;
}

int CPU::AND_A() {
	AND(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("And", "A", "");
	return 4;
}

int CPU::AND_B() {
	this->AF.hi = AND(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("And", "B", "");
	return 4;
}

int CPU::AND_C() {
	this->AF.hi = AND(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("And", "C", "");
	return 4;
}

int CPU::AND_D() {
	this->AF.hi = AND(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("And", "D", "");
	return 4;
}

int CPU::AND_E() {
	this->AF.hi = AND(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("And", "E", "");
	return 4;
}

int CPU::AND_H() {
	this->AF.hi = AND(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("And", "H", "");
	return 4;
}

int CPU::AND_l() {
	this->AF.hi = AND(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("And", "L", "");
	return 4;
}

int CPU::AND_HL() {
	this->AF.hi = AND(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("And", "(HL)", "");
	return 8;
}

int CPU::AND_n() {
	this->AF.hi = AND(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	Logger::LogInstruction("And", "imm", "");
	return 8;
}

int CPU::OR_A() {
	OR(this->AF.hi, this->AF.hi);
	Logger::LogInstruction("Or", "A", "");
	return 4;
}

int CPU::OR_B() {
	this->AF.hi = OR(this->AF.hi, this->BC.hi);
	Logger::LogInstruction("Or", "B", "");
	return 4;
}

int CPU::OR_C() {
	this->AF.hi = OR(this->AF.hi, this->BC.lo);
	Logger::LogInstruction("Or", "C", "");
	return 4;
}

int CPU::OR_D() {
	this->AF.hi = OR(this->AF.hi, this->DE.hi);
	Logger::LogInstruction("Or", "D", "");
	return 4;
}

int CPU::OR_E() {
	this->AF.hi = OR(this->AF.hi, this->DE.lo);
	Logger::LogInstruction("Or", "E", "");
	return 4;
}

int CPU::OR_H() {
	this->AF.hi = OR(this->AF.hi, this->HL.hi);
	Logger::LogInstruction("Or", "H", "");
	return 4;
}

int CPU::OR_L() {
	this->AF.hi = OR(this->AF.hi, this->HL.lo);
	Logger::LogInstruction("Or", "L", "");
	return 4;
}

int CPU::OR_HL() {
	this->AF.hi = OR(this->AF.hi, this->memory.readByte(this->HL.reg));
	Logger::LogInstruction("Or", "(HL)", "");
	return 8;
}

int CPU::OR_n() {
	this->AF.hi = OR(this->AF.hi, this->memory.readByte(this->PC.reg));
	this->PC.reg++;
	Logger::LogInstruction("Or", "imm", "");
	return 8;
}

int CPU::DAA() {

	WORD acc = this->AF.hi;

	if (getFlag(Flag::n) == 1) {
		if (getFlag(Flag::h) == 1) {
			acc = (acc - 0x06) & 0xFF;
		}

		if (getFlag(Flag::c) == 1) {
			acc -= 0x60;
		} 
	}
	else {
		if (getFlag(Flag::h) == 1 || (acc & 0x0F) > 9) {
			acc += 0x06;
		}

		if (getFlag(Flag::c) == 1 || (acc > 0x9F)) {
			acc += 0x60;
		}
	}

	this->AF.hi = acc;

	resetFlag(Flag::h);

	if (acc >= 0x100) {
		setFlag(Flag::c);
	}

	if (this->AF.hi == 0) {
		setFlag(Flag::z);
	}
	else {
		resetFlag(Flag::z);
	}

	return 4;
}

int CPU::CPL() {
	this->AF.hi = ~(this->AF.hi);
	setFlag(Flag::n);
	setFlag(Flag::h);
	Logger::LogInstruction("CPL", "", "");
	return 4;
}

int CPU::SCF() {
	setFlag(Flag::c);
	resetFlag(Flag::n);
	resetFlag(Flag::h);
	Logger::LogInstruction("SCF", "", "");
	return 4;
}

int CPU::CCF() {
	if (getFlag(Flag::c) == 1) {
		resetFlag(Flag::c);
	}
	else {
		setFlag(Flag::c);
	}

	resetFlag(Flag::n);
	resetFlag(Flag::h);
	Logger::LogInstruction("CCF", "", "");
	return 4;
}

int CPU::CP_A() {
	Compare(this->AF.hi);
	Logger::LogInstruction("Cp", "A", "");
	return 4;
}

int CPU::CP_B() {
	Compare(this->BC.hi);
	Logger::LogInstruction("Cp", "B", "");
	return 4;
}

int CPU::CP_C() {
	Compare(this->BC.lo);
	Logger::LogInstruction("Cp", "C", "");
	return 4;
}

int CPU::CP_D() {
	Compare(this->DE.hi);
	Logger::LogInstruction("Cp", "D", "");
	return 4;
}

int CPU::CP_E() {
	Compare(this->DE.lo);
	Logger::LogInstruction("Cp", "E", "");
	return 4;
}

int CPU::CP_H() {
	Compare(this->HL.hi);
	Logger::LogInstruction("Cp", "H", "");
	return 4;
}

int CPU::CP_L() {
	Compare(this->HL.lo);
	Logger::LogInstruction("Cp", "L", "");
	return 4;
}

int CPU::CP_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	Compare(value);
	Logger::LogInstruction("Cp", "(HL)", "");
	return 8;
}

int CPU::CP_n() {
	BYTE immediate = this->memory.readByte(this->PC.reg);
	this->PC.reg++;
	Compare(immediate);
	Logger::LogInstruction("Cp", "imm", "");
	return 8;
}

int CPU::INC_A() {
	this->AF.hi = RegInc(this->AF.hi);
	Logger::LogInstruction("Inc", "A", "");
	return 4;
}

int CPU::INC_B() {
	this->BC.hi = RegInc(this->BC.hi);
	Logger::LogInstruction("Inc", "B", "");
	return 4;
}

int CPU::INC_C() {
	this->BC.lo = RegInc(this->BC.lo);
	Logger::LogInstruction("Inc", "C", "");
	return 4;
}

int CPU::INC_D() {
	this->DE.hi = RegInc(this->DE.hi);
	Logger::LogInstruction("Inc", "D", "");
	return 4;
}

int CPU::INC_E() {
	this->DE.lo = RegInc(this->DE.lo);
	Logger::LogInstruction("Inc", "E", "");
	return 4;
}

int CPU::INC_H() {
	this->HL.hi = RegInc(this->HL.hi);
	Logger::LogInstruction("Inc", "H", "");
	return 4;
}

int CPU::INC_L() {
	this->HL.lo = RegInc(this->HL.lo);
	Logger::LogInstruction("Inc", "L", "");
	return 4;
}

int CPU::INC_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegInc(value);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("Inc", "(HL)", "");
	return 8;
}

int CPU::INC_BC() {
	this->BC.reg++;
	Logger::LogInstruction("Inc", "BC", "");
	return 8;
}

int CPU::INC_DE() {
	this->DE.reg++;
	Logger::LogInstruction("Inc", "DE", "");
	return 8;
}

int CPU::INC_HL() {
	this->HL.reg++;
	Logger::LogInstruction("Inc", "HL", "");
	return 8;
}

int CPU::INC_SP() {
	this->SP.reg++;
	Logger::LogInstruction("Inc", "SP", "");
	return 8;
}

int CPU::DEC_A() {
	this->AF.hi = RegDec(this->AF.hi);
	Logger::LogInstruction("Dec", "A", "");
	return 4;
}

int CPU::DEC_B() {
	this->BC.hi = RegDec(this->BC.hi);
	Logger::LogInstruction("Dec", "B", "");
	return 4;
}

int CPU::DEC_C() {
	this->BC.lo = RegDec(this->BC.lo);
	Logger::LogInstruction("Dec", "C", "");
	return 4;
}

int CPU::DEC_D() {
	this->DE.hi = RegDec(this->DE.hi);
	Logger::LogInstruction("Dec", "D", "");
	return 4;
}

int CPU::DEC_E() {
	this->DE.lo = RegDec(this->DE.lo);
	Logger::LogInstruction("Dec", "E", "");
	return 4;
}

int CPU::DEC_H() {
	this->HL.hi = RegDec(this->HL.hi);
	Logger::LogInstruction("Dec", "H", "");
	return 4;
}

int CPU::DEC_L() {
	this->HL.lo = RegDec(this->HL.lo);
	Logger::LogInstruction("Dec", "L", "");
	return 4;
}

int CPU::DEC_MEM_HL() {
	BYTE value = this->memory.readByte(this->HL.reg);
	value = RegDec(value);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("Dec", "(HL)", "");
	return 8;
}

int CPU::DEC_BC() {
	this->BC.reg--;
	Logger::LogInstruction("Dec", "BC", "");
	return 8;
}

int CPU::DEC_DE() {
	this->DE.reg--;
	Logger::LogInstruction("Dec", "DE", "");
	return 8;
}

int CPU::DEC_HL() {
	this->HL.reg--;
	Logger::LogInstruction("Dec", "HL", "");
	return 8;
}

int CPU::DEC_SP() {
	this->SP.reg--;
	Logger::LogInstruction("Dec", "SP", "");
	return 8;
}

//Interrupt instructions
int CPU::DI() {
	this->interruptEnabled = false;
	Logger::LogInstruction("DI", "", "");
	return 4;
}

int CPU::EI() {
	this->interruptEnabled = true;
	Logger::LogInstruction("EI", "", "");
	return 4;
}

void CPU::initInstructions() {
	for (int i = 0; i < (sizeof((instructions))/sizeof((instructions[0]))); i++ ){
		instructions[i] = NULL;
	}

	instructions[0x00] = &CPU::NOP;
	instructions[0x10] = &CPU::STOP;
	instructions[0x76] = &CPU::HALT;

	instructions[0x3e] = &CPU::LD_A_n;
	instructions[0x06] = &CPU::LD_B_n;
	instructions[0x0E] = &CPU::LD_C_n;
	instructions[0x16] = &CPU::LD_D_n;
	instructions[0x1E] = &CPU::LD_E_n;
	instructions[0x26] = &CPU::LD_H_n;
	instructions[0x2E] = &CPU::LD_L_n;

	instructions[0x7F] = &CPU::LD_A_A;
	instructions[0x78] = &CPU::LD_A_B;
	instructions[0x79] = &CPU::LD_A_C;
	instructions[0x7A] = &CPU::LD_A_D;
	instructions[0x7B] = &CPU::LD_A_E;
	instructions[0x7C] = &CPU::LD_A_H;
	instructions[0x7D] = &CPU::LD_A_L;
	instructions[0x0A] = &CPU::LD_A_BC;
	instructions[0x1A] = &CPU::LD_A_DE;
	instructions[0x7E] = &CPU::LD_A_HL;
	instructions[0xFA] = &CPU::LD_A_nn;

	instructions[0x40] = &CPU::LD_B_B;
	instructions[0x41] = &CPU::LD_B_C;
	instructions[0x42] = &CPU::LD_B_D;
	instructions[0x43] = &CPU::LD_B_E;
	instructions[0x44] = &CPU::LD_B_H;
	instructions[0x45] = &CPU::LD_B_L;
	instructions[0x46] = &CPU::LD_B_HL;

	instructions[0x48] = &CPU::LD_C_B;
	instructions[0x49] = &CPU::LD_C_C;
	instructions[0x4A] = &CPU::LD_C_D;
	instructions[0x4B] = &CPU::LD_C_E;
	instructions[0x4C] = &CPU::LD_C_H;
	instructions[0x4D] = &CPU::LD_C_L;
	instructions[0x4E] = &CPU::LD_C_HL;

	instructions[0x50] = &CPU::LD_D_B;
	instructions[0x51] = &CPU::LD_D_C;
	instructions[0x52] = &CPU::LD_D_D;
	instructions[0x53] = &CPU::LD_D_E;
	instructions[0x54] = &CPU::LD_D_H;
	instructions[0x55] = &CPU::LD_D_L;
	instructions[0x56] = &CPU::LD_D_HL;

	instructions[0x58] = &CPU::LD_E_B;
	instructions[0x59] = &CPU::LD_E_C;
	instructions[0x5A] = &CPU::LD_E_D;
	instructions[0x5B] = &CPU::LD_E_E;
	instructions[0x5C] = &CPU::LD_E_H;
	instructions[0x5D] = &CPU::LD_E_L;
	instructions[0x5E] = &CPU::LD_E_HL;

	instructions[0x60] = &CPU::LD_H_B;
	instructions[0x61] = &CPU::LD_H_C;
	instructions[0x62] = &CPU::LD_H_D;
	instructions[0x63] = &CPU::LD_H_E;
	instructions[0x64] = &CPU::LD_H_H;
	instructions[0x65] = &CPU::LD_H_L;
	instructions[0x66] = &CPU::LD_H_HL;

	instructions[0x68] = &CPU::LD_L_B;
	instructions[0x69] = &CPU::LD_L_C;
	instructions[0x6A] = &CPU::LD_L_D;
	instructions[0x6B] = &CPU::LD_L_E;
	instructions[0x6C] = &CPU::LD_L_H;
	instructions[0x6D] = &CPU::LD_L_L;
	instructions[0x6E] = &CPU::LD_L_HL;

	instructions[0x47] = &CPU::LD_B_A;
	instructions[0x4F] = &CPU::LD_C_A;
	instructions[0x57] = &CPU::LD_D_A;
	instructions[0x5F] = &CPU::LD_E_A;
	instructions[0x67] = &CPU::LD_H_A;
	instructions[0x6F] = &CPU::LD_L_A;
	instructions[0x02] = &CPU::LD_BC_A;
	instructions[0x12] = &CPU::LD_DE_A;
	instructions[0xEA] = &CPU::LD_nn_A;

	instructions[0x77] = &CPU::LD_HL_A;
	instructions[0x70] = &CPU::LD_HL_B;
	instructions[0x71] = &CPU::LD_HL_C;
	instructions[0x72] = &CPU::LD_HL_D;
	instructions[0x73] = &CPU::LD_HL_E;
	instructions[0x74] = &CPU::LD_HL_H;
	instructions[0x75] = &CPU::LD_HL_L;
	instructions[0x36] = &CPU::LD_HL_n;

	instructions[0xF2] = &CPU::LD_A_FF00_C;
	instructions[0xe2] = &CPU::LD_FF00_C_A;
	instructions[0xe0] = &CPU::LD_FF00_n_A;
	instructions[0xF0] = &CPU::LDH_A_FF00_n;
	instructions[0xF8] = &CPU::LDHL_SP_n;

	//Load Dec/Inc
	instructions[0x32] = &CPU::LDD_HL_A;
	instructions[0x22] = &CPU::LDI_HL_A;
	instructions[0x3A] = &CPU::LDD_A_HL;
	instructions[0x2A] = &CPU::LDI_A_HL;

	//16 bit load immediate
	instructions[0xF9] = &CPU::LD_SP_HL;
	instructions[0x01] = &CPU::LD_BC_nn;
	instructions[0x11] = &CPU::LD_DE_nn;
	instructions[0x21] = &CPU::LD_HL_nn;
	instructions[0x31] = &CPU::LD_SP_nn;
	instructions[0x08] = &CPU::LD_nn_SP;

	//Add
	instructions[0x87] = &CPU::ADD_A;
	instructions[0x80] = &CPU::ADD_B;
	instructions[0x81] = &CPU::ADD_C;
	instructions[0x82] = &CPU::ADD_D;
	instructions[0x83] = &CPU::ADD_E;
	instructions[0x84] = &CPU::ADD_H;
	instructions[0x85] = &CPU::ADD_L;
	instructions[0x86] = &CPU::ADD_HL;
	instructions[0xC6] = &CPU::ADD_n;

	instructions[0x09] = &CPU::ADD_HL_BC;
	instructions[0x19] = &CPU::ADD_HL_DE;
	instructions[0x29] = &CPU::ADD_HL_HL;
	instructions[0x39] = &CPU::ADD_HL_SP;
	instructions[0xE8] = &CPU::ADD_SP_n;

	instructions[0x8F] = &CPU::ADC_A;
	instructions[0x88] = &CPU::ADC_B;
	instructions[0x89] = &CPU::ADC_C;
	instructions[0x8A] = &CPU::ADC_D;
	instructions[0x8B] = &CPU::ADC_E;
	instructions[0x8C] = &CPU::ADC_H;
	instructions[0x8D] = &CPU::ADC_L;
	instructions[0x8E] = &CPU::ADC_HL;
	instructions[0xCE] = &CPU::ADC_n;

	//Sub
	instructions[0x97] = &CPU::SUB_A;
	instructions[0x90] = &CPU::SUB_B;
	instructions[0x91] = &CPU::SUB_C;
	instructions[0x92] = &CPU::SUB_D;
	instructions[0x93] = &CPU::SUB_E;
	instructions[0x94] = &CPU::SUB_H;
	instructions[0x95] = &CPU::SUB_L;
	instructions[0x96] = &CPU::SUB_HL;
	instructions[0xD6] = &CPU::SUB_n;

	instructions[0x9F] = &CPU::SBC_A;
	instructions[0x98] = &CPU::SBC_B;
	instructions[0x99] = &CPU::SBC_C;
	instructions[0x9A] = &CPU::SBC_D;
	instructions[0x9B] = &CPU::SBC_E;
	instructions[0x9C] = &CPU::SBC_H;
	instructions[0x9D] = &CPU::SBC_L;
	instructions[0x9E] = &CPU::SBC_HL;
	instructions[0xDE] = &CPU::SBC_n;

	//XORs
	instructions[0xAF] = &CPU::XOR_A;
	instructions[0xA8] = &CPU::XOR_B;
	instructions[0xA9] = &CPU::XOR_C;
	instructions[0xAA] = &CPU::XOR_D;
	instructions[0xAB] = &CPU::XOR_E;
	instructions[0xAC] = &CPU::XOR_H;
	instructions[0xAD] = &CPU::XOR_L;
	instructions[0xAE] = &CPU::XOR_HL;
	instructions[0xEE] = &CPU::XOR_n;

	//ANDs
	instructions[0xA7] = &CPU::AND_A;
	instructions[0xA0] = &CPU::AND_B;
	instructions[0xA1] = &CPU::AND_C;
	instructions[0xA2] = &CPU::AND_D;
	instructions[0xA3] = &CPU::AND_E;
	instructions[0xA4] = &CPU::AND_H;
	instructions[0xA5] = &CPU::AND_l;
	instructions[0xA6] = &CPU::AND_HL;
	instructions[0xE6] = &CPU::AND_n;

	//ORs
	instructions[0xB7] = &CPU::OR_A;
	instructions[0xB0] = &CPU::OR_B;
	instructions[0xB1] = &CPU::OR_C;
	instructions[0xB2] = &CPU::OR_D;
	instructions[0xB3] = &CPU::OR_E;
	instructions[0xB4] = &CPU::OR_H;
	instructions[0xB5] = &CPU::OR_L;
	instructions[0xB6] = &CPU::OR_HL;
	instructions[0xF6] = &CPU::OR_n;

	//Complement
	instructions[0x27] = &CPU::DAA;
	instructions[0x2F] = &CPU::CPL;

	instructions[0x37] = &CPU::SCF;
	instructions[0x3F] = &CPU::CCF;

	instructions[0xBF] = &CPU::CP_A;
	instructions[0xB8] = &CPU::CP_B;
	instructions[0xB9] = &CPU::CP_C;
	instructions[0xBA] = &CPU::CP_D;
	instructions[0xBB] = &CPU::CP_E;
	instructions[0xBC] = &CPU::CP_H;
	instructions[0xBD] = &CPU::CP_L;
	instructions[0xBE] = &CPU::CP_MEM_HL;
	instructions[0xFE] = &CPU::CP_n;

	//Incs
	instructions[0x3C] = &CPU::INC_A;
	instructions[0x04] = &CPU::INC_B;
	instructions[0x0C] = &CPU::INC_C;
	instructions[0x14] = &CPU::INC_D;
	instructions[0x1C] = &CPU::INC_E;
	instructions[0x24] = &CPU::INC_H;
	instructions[0x2C] = &CPU::INC_L;
	instructions[0x34] = &CPU::INC_MEM_HL;

	instructions[0x03] = &CPU::INC_BC;
	instructions[0x13] = &CPU::INC_DE;
	instructions[0x23] = &CPU::INC_HL;
	instructions[0x33] = &CPU::INC_SP;

	instructions[0x3D] = &CPU::DEC_A;
	instructions[0x05] = &CPU::DEC_B;
	instructions[0x0D] = &CPU::DEC_C;
	instructions[0x15] = &CPU::DEC_D;
	instructions[0x1D] = &CPU::DEC_E;
	instructions[0x25] = &CPU::DEC_H;
	instructions[0x2D] = &CPU::DEC_L;
	instructions[0x35] = &CPU::DEC_MEM_HL;

	instructions[0x0B] = &CPU::DEC_BC;
	instructions[0x1B] = &CPU::DEC_DE;
	instructions[0x2B] = &CPU::DEC_HL;
	instructions[0x3B] = &CPU::DEC_SP;

	//Jumps
	instructions[0x20] = &CPU::JR_NZ;
	instructions[0x28] = &CPU::JR_Z;
	instructions[0x30] = &CPU::JR_NC;
	instructions[0x38] = &CPU::JR_C;
	instructions[0x18] = &CPU::JR;
	instructions[0xc3] = &CPU::JP_nn;
	instructions[0xC2] = &CPU::JP_NZ;
	instructions[0xCA] = &CPU::JP_Z;
	instructions[0xD2] = &CPU::JP_NC;
	instructions[0xDA] = &CPU::JP_C;
	instructions[0xE9] = &CPU::JP_HL;

	//Stack
	instructions[0xCD] = &CPU::CALL_nn;
	instructions[0xC4] = &CPU::CALL_NZ_nn;
	instructions[0xCC] = &CPU::CALL_Z_nn; 
	instructions[0xD4] = &CPU::CALL_NC_nn;
	instructions[0xDC] = &CPU::CALL_C_nn; 
	instructions[0xC9] = &CPU::RET;
	instructions[0xC0] = &CPU::RET_NZ;
	instructions[0xC8] = &CPU::RET_Z;
	instructions[0xD0] = &CPU::RET_NC;
	instructions[0xD8] = &CPU::RET_C;
	instructions[0xD9] = &CPU::RETI;
	instructions[0xF5] = &CPU::PUSH_AF;
	instructions[0xC5] = &CPU::PUSH_BC;
	instructions[0xD5] = &CPU::PUSH_DE;
	instructions[0xE5] = &CPU::PUSH_HL;

	instructions[0xF1] = &CPU::POP_AF;
	instructions[0xC1] = &CPU::POP_BC;
	instructions[0xD1] = &CPU::POP_DE;
	instructions[0xE1] = &CPU::POP_HL;

	//RSTs
	instructions[0xC7] = &CPU::RST_00;
	instructions[0xCF] = &CPU::RST_08;
	instructions[0xD7] = &CPU::RST_10;
	instructions[0xDF] = &CPU::RST_18;
	instructions[0xE7] = &CPU::RST_20;
	instructions[0xEF] = &CPU::RST_28;
	instructions[0xF7] = &CPU::RST_30;
	instructions[0xFF] = &CPU::RST_38;

	instructions[0xF3] = &CPU::DI;
	instructions[0xFB] = &CPU::EI;
}