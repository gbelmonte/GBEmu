//Bit instructions
int CPU::BIT_0_A() {
	TestBit(this->AF.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "A");
	return 8;
} 

int CPU::BIT_1_A() {
	TestBit(this->AF.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "A");
	return 8;
}

int CPU::BIT_2_A() {
	TestBit(this->AF.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "A");
	return 8;
}

int CPU::BIT_3_A() {
	TestBit(this->AF.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "A");
	return 8;
}

int CPU::BIT_4_A() {
	TestBit(this->AF.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "A");
	return 8;
}

int CPU::BIT_5_A() {
	TestBit(this->AF.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "A");
	return 8;
}

int CPU::BIT_6_A() {
	TestBit(this->AF.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "A");
	return 8;
}

int CPU::BIT_7_A() {
	TestBit(this->AF.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "A");
	return 8;
}

int CPU::BIT_0_B() {
	TestBit(this->BC.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "B");
	return 8;
}

int CPU::BIT_1_B() {
	TestBit(this->BC.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "B");
	return 8;
}

int CPU::BIT_2_B() {
	TestBit(this->BC.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "B");
	return 8;
}

int CPU::BIT_3_B() {
	TestBit(this->BC.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "B");
	return 8;
}

int CPU::BIT_4_B() {
	TestBit(this->BC.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "B");
	return 8;
}

int CPU::BIT_5_B() {
	TestBit(this->BC.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "B");
	return 8;
}

int CPU::BIT_6_B() {
	TestBit(this->BC.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "B");
	return 8;
}

int CPU::BIT_7_B() {
	TestBit(this->BC.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "B");
	return 8;
}

int CPU::BIT_0_C() {
	TestBit(this->BC.lo, BIT0);
	Logger::LogInstruction("Bit", "0", "C");
	return 8;
}

int CPU::BIT_1_C() {
	TestBit(this->BC.lo, BIT1);
	Logger::LogInstruction("Bit", "1", "C");
	return 8;
}

int CPU::BIT_2_C() {
	TestBit(this->BC.lo, BIT2);
	Logger::LogInstruction("Bit", "2", "C");
	return 8;
}

int CPU::BIT_3_C() {
	TestBit(this->BC.lo, BIT3);
	Logger::LogInstruction("Bit", "3", "C");
	return 8;
}

int CPU::BIT_4_C() {
	TestBit(this->BC.lo, BIT4);
	Logger::LogInstruction("Bit", "4", "C");
	return 8;
}

int CPU::BIT_5_C() {
	TestBit(this->BC.lo, BIT5);
	Logger::LogInstruction("Bit", "5", "C");
	return 8;
}

int CPU::BIT_6_C() {
	TestBit(this->BC.lo, BIT6);
	Logger::LogInstruction("Bit", "6", "C");
	return 8;
}

int CPU::BIT_7_C() {
	TestBit(this->BC.lo, BIT7);
	Logger::LogInstruction("Bit", "7", "C");
	return 8;
}

int CPU::BIT_0_D() {
	TestBit(this->DE.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "D");
	return 8;
}

int CPU::BIT_1_D() {
	TestBit(this->DE.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "D");
	return 8;
}

int CPU::BIT_2_D() {
	TestBit(this->DE.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "D");
	return 8;
}

int CPU::BIT_3_D() {
	TestBit(this->DE.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "D");
	return 8;
}

int CPU::BIT_4_D() {
	TestBit(this->DE.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "D");
	return 8;
}

int CPU::BIT_5_D() {
	TestBit(this->DE.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "D");
	return 8;
}

int CPU::BIT_6_D() {
	TestBit(this->DE.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "D");
	return 8;
}

int CPU::BIT_7_D() {
	TestBit(this->DE.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "D");
	return 8;
}
 
int CPU::BIT_0_E() {
	TestBit(this->DE.lo, BIT0);
	Logger::LogInstruction("Bit", "0", "E");
	return 8;
}

int CPU::BIT_1_E() {
	TestBit(this->DE.lo, BIT1);
	Logger::LogInstruction("Bit", "1", "E");
	return 8;
}

int CPU::BIT_2_E() {
	TestBit(this->DE.lo, BIT2);
	Logger::LogInstruction("Bit", "2", "E");
	return 8;
}

int CPU::BIT_3_E() {
	TestBit(this->DE.lo, BIT3);
	Logger::LogInstruction("Bit", "3", "E");
	return 8;
}

int CPU::BIT_4_E() {
	TestBit(this->DE.lo, BIT4);
	Logger::LogInstruction("Bit", "4", "E");
	return 8;
}

int CPU::BIT_5_E() {
	TestBit(this->DE.lo, BIT5);
	Logger::LogInstruction("Bit", "5", "E");
	return 8;
}

int CPU::BIT_6_E() {
	TestBit(this->DE.lo, BIT6);
	Logger::LogInstruction("Bit", "6", "E");
	return 8;
}

int CPU::BIT_7_E() {
	TestBit(this->DE.lo, BIT7);
	Logger::LogInstruction("Bit", "7", "E");
	return 8;
}
 
int CPU::BIT_0_H() {
	TestBit(this->HL.hi, BIT0);
	Logger::LogInstruction("Bit", "0", "H");
	return 8;
}

int CPU::BIT_1_H() {
	TestBit(this->HL.hi, BIT1);
	Logger::LogInstruction("Bit", "1", "H");
	return 8;
}

int CPU::BIT_2_H() {
	TestBit(this->HL.hi, BIT2);
	Logger::LogInstruction("Bit", "2", "H");
	return 8;
}

int CPU::BIT_3_H() {
	TestBit(this->HL.hi, BIT3);
	Logger::LogInstruction("Bit", "3", "H");
	return 8;
}

int CPU::BIT_4_H() {
	TestBit(this->HL.hi, BIT4);
	Logger::LogInstruction("Bit", "4", "H");
	return 8;
}

int CPU::BIT_5_H() {
	TestBit(this->HL.hi, BIT5);
	Logger::LogInstruction("Bit", "5", "H");
	return 8;
}

int CPU::BIT_6_H() {
	TestBit(this->HL.hi, BIT6);
	Logger::LogInstruction("Bit", "6", "H");
	return 8;
}

int CPU::BIT_7_H() {
	TestBit(this->HL.hi, BIT7);
	Logger::LogInstruction("Bit", "7", "H");
	return 8;
}
 
int CPU::BIT_0_L() {
	TestBit(this->HL.lo, BIT0);
	Logger::LogInstruction("Bit", "0", "L");
	return 8;
}

int CPU::BIT_1_L() {
	TestBit(this->HL.lo, BIT1);
	Logger::LogInstruction("Bit", "1", "L");
	return 8;
}

int CPU::BIT_2_L() {
	TestBit(this->HL.lo, BIT2);
	Logger::LogInstruction("Bit", "2", "L");
	return 8;
}

int CPU::BIT_3_L() {
	TestBit(this->HL.lo, BIT3);
	Logger::LogInstruction("Bit", "3", "L");
	return 8;
}

int CPU::BIT_4_L() {
	TestBit(this->HL.lo, BIT4);
	Logger::LogInstruction("Bit", "4", "L");
	return 8;
}

int CPU::BIT_5_L() {
	TestBit(this->HL.lo, BIT5);
	Logger::LogInstruction("Bit", "5", "L");
	return 8;
}

int CPU::BIT_6_L() {
	TestBit(this->HL.lo, BIT6);
	Logger::LogInstruction("Bit", "6", "L");
	return 8;
}

int CPU::BIT_7_L() {
	TestBit(this->HL.lo, BIT7);
	Logger::LogInstruction("Bit", "7", "L");
	return 8;
}

int CPU::BIT_0_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT0);
	Logger::LogInstruction("Bit", "0", "(HL)");
	return 8;
}

int CPU::BIT_1_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT1);
	Logger::LogInstruction("Bit", "1", "(HL)");
	return 8;
}

int CPU::BIT_2_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT2);
	Logger::LogInstruction("Bit", "2", "(HL)");
	return 8;
}

int CPU::BIT_3_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT3);
	Logger::LogInstruction("Bit", "3", "(HL)");
	return 8;
}

int CPU::BIT_4_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT4);
	Logger::LogInstruction("Bit", "4", "(HL)");
	return 8;
}

int CPU::BIT_5_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT5);
	Logger::LogInstruction("Bit", "5", "(HL)");
	return 8;
}

int CPU::BIT_6_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT6);
	Logger::LogInstruction("Bit", "6", "(HL)");
	return 8;
}

int CPU::BIT_7_HL() {
	UpdateCPUCycles(4);
	BYTE byte = this->memory.readByte(this->HL.reg);
	TestBit(byte, BIT7);
	Logger::LogInstruction("Bit", "7", "(HL)");
	return 8;
}

int CPU::SET_0_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "A");
	return 8;
}

int CPU::SET_1_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "A");
	return 8;
}

int CPU::SET_2_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "A");
	return 8;
}

int CPU::SET_3_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "A");
	return 8;
}

int CPU::SET_4_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "A");
	return 8;
}

int CPU::SET_5_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "A");
	return 8;
}

int CPU::SET_6_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "A");
	return 8;
}

int CPU::SET_7_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "A");
	return 8;
}

int CPU::SET_0_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "B");
	return 8;
}

int CPU::SET_1_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "B");
	return 8;
}

int CPU::SET_2_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "B");
	return 8;
}

int CPU::SET_3_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "B");
	return 8;
}

int CPU::SET_4_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "B");
	return 8;
}

int CPU::SET_5_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "B");
	return 8;
}

int CPU::SET_6_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "B");
	return 8;
}

int CPU::SET_7_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "B");
	return 8;
}

int CPU::SET_0_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT0, 1);
	Logger::LogInstruction("SET", "0", "C");
	return 8;
}

int CPU::SET_1_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT1, 1);
	Logger::LogInstruction("SET", "1", "C");
	return 8;
}

int CPU::SET_2_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT2, 1);
	Logger::LogInstruction("SET", "2", "C");
	return 8;
}

int CPU::SET_3_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT3, 1);
	Logger::LogInstruction("SET", "3", "C");
	return 8;
}

int CPU::SET_4_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT4, 1);
	Logger::LogInstruction("SET", "4", "C");
	return 8;
}

int CPU::SET_5_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT5, 1);
	Logger::LogInstruction("SET", "5", "C");
	return 8;
}

int CPU::SET_6_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT6, 1);
	Logger::LogInstruction("SET", "6", "C");
	return 8;
}

int CPU::SET_7_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT7, 1);
	Logger::LogInstruction("SET", "7", "C");
	return 8;
}

int CPU::SET_0_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "D");
	return 8;
}

int CPU::SET_1_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "D");
	return 8;
}

int CPU::SET_2_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "D");
	return 8;
}

int CPU::SET_3_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "D");
	return 8;
}

int CPU::SET_4_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "D");
	return 8;
}

int CPU::SET_5_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "D");
	return 8;
}

int CPU::SET_6_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "D");
	return 8;
}

int CPU::SET_7_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "D");
	return 8;
}

int CPU::SET_0_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT0, 1);
	Logger::LogInstruction("SET", "0", "E");
	return 8;
}

int CPU::SET_1_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT1, 1);
	Logger::LogInstruction("SET", "1", "E");
	return 8;
}

int CPU::SET_2_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT2, 1);
	Logger::LogInstruction("SET", "2", "E");
	return 8;
}

int CPU::SET_3_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT3, 1);
	Logger::LogInstruction("SET", "3", "E");
	return 8;
}

int CPU::SET_4_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT4, 1);
	Logger::LogInstruction("SET", "4", "E");
	return 8;
}

int CPU::SET_5_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT5, 1);
	Logger::LogInstruction("SET", "5", "E");
	return 8;
}

int CPU::SET_6_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT6, 1);
	Logger::LogInstruction("SET", "6", "E");
	return 8;
}

int CPU::SET_7_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT7, 1);
	Logger::LogInstruction("SET", "7", "E");
	return 8;
}

int CPU::SET_0_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT0, 1);
	Logger::LogInstruction("SET", "0", "H");
	return 8;
}

int CPU::SET_1_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT1, 1);
	Logger::LogInstruction("SET", "1", "H");
	return 8;
}

int CPU::SET_2_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT2, 1);
	Logger::LogInstruction("SET", "2", "H");
	return 8;
}

int CPU::SET_3_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT3, 1);
	Logger::LogInstruction("SET", "3", "H");
	return 8;
}

int CPU::SET_4_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT4, 1);
	Logger::LogInstruction("SET", "4", "H");
	return 8;
}

int CPU::SET_5_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT5, 1);
	Logger::LogInstruction("SET", "5", "H");
	return 8;
}

int CPU::SET_6_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT6, 1);
	Logger::LogInstruction("SET", "6", "H");
	return 8;
}

int CPU::SET_7_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT7, 1);
	Logger::LogInstruction("SET", "7", "H");
	return 8;
}

int CPU::SET_0_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT0, 1);
	Logger::LogInstruction("SET", "0", "L");
	return 8;
}

int CPU::SET_1_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT1, 1);
	Logger::LogInstruction("SET", "1", "L");
	return 8;
}

int CPU::SET_2_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT2, 1);
	Logger::LogInstruction("SET", "2", "L");
	return 8;
}

int CPU::SET_3_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT3, 1);
	Logger::LogInstruction("SET", "3", "L");
	return 8;
}

int CPU::SET_4_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT4, 1);
	Logger::LogInstruction("SET", "4", "L");
	return 8;
}

int CPU::SET_5_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT5, 1);
	Logger::LogInstruction("SET", "5", "L");
	return 8;
}

int CPU::SET_6_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT6, 1);
	Logger::LogInstruction("SET", "6", "L");
	return 8;
}

int CPU::SET_7_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT7, 1);
	Logger::LogInstruction("SET", "7", "L");
	return 8;
}

int CPU::SET_0_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT0, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "0", "(HL)");
	return 8;
}

int CPU::SET_1_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT1, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "1", "(HL)");
	return 8;
}

int CPU::SET_2_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT2, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "2", "(HL)");
	return 8;
}

int CPU::SET_3_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT3, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "3", "(HL)");
	return 8;
}

int CPU::SET_4_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT4, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "4", "(HL)");
	return 8;
}

int CPU::SET_5_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT5, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "5", "(HL)");
	return 8;
}

int CPU::SET_6_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT6, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "6", "(HL)");
	return 8;
}

int CPU::SET_7_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT7, 1);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SET", "7", "(HL)");
	return 8;
}

int CPU::RES_0_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "A");
	return 8;
}

int CPU::RES_1_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "A");
	return 8;
}

int CPU::RES_2_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "A");
	return 8;
}

int CPU::RES_3_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "A");
	return 8;
}

int CPU::RES_4_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "A");
	return 8;
}

int CPU::RES_5_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "A");
	return 8;
}

int CPU::RES_6_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "A");
	return 8;
}

int CPU::RES_7_A() {
	this->AF.hi = SetBit(this->AF.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "A");
	return 8;
}

int CPU::RES_0_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "B");
	return 8;
}

int CPU::RES_1_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "B");
	return 8;
}

int CPU::RES_2_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "B");
	return 8;
}

int CPU::RES_3_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "B");
	return 8;
}

int CPU::RES_4_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "B");
	return 8;
}

int CPU::RES_5_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "B");
	return 8;
}

int CPU::RES_6_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "B");
	return 8;
}

int CPU::RES_7_B() {
	this->BC.hi = SetBit(this->BC.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "B");
	return 8;
}

int CPU::RES_0_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT0, 0);
	Logger::LogInstruction("RES", "0", "C");
	return 8;
}

int CPU::RES_1_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT1, 0);
	Logger::LogInstruction("RES", "1", "C");
	return 8;
}

int CPU::RES_2_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT2, 0);
	Logger::LogInstruction("RES", "2", "C");
	return 8;
}

int CPU::RES_3_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT3, 0);
	Logger::LogInstruction("RES", "3", "C");
	return 8;
}

int CPU::RES_4_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT4, 0);
	Logger::LogInstruction("RES", "4", "C");
	return 8;
}

int CPU::RES_5_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT5, 0);
	Logger::LogInstruction("RES", "5", "C");
	return 8;
}

int CPU::RES_6_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT6, 0);
	Logger::LogInstruction("RES", "6", "C");
	return 8;
}

int CPU::RES_7_C() {
	this->BC.lo = SetBit(this->BC.lo, BIT7, 0);
	Logger::LogInstruction("RES", "7", "C");
	return 8;
}

int CPU::RES_0_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "D");
	return 8;
}

int CPU::RES_1_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "D");
	return 8;
}

int CPU::RES_2_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "D");
	return 8;
}

int CPU::RES_3_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "D");
	return 8;
}

int CPU::RES_4_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "D");
	return 8;
}

int CPU::RES_5_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "D");
	return 8;
}

int CPU::RES_6_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "D");
	return 8;
}

int CPU::RES_7_D() {
	this->DE.hi = SetBit(this->DE.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "D");
	return 8;
}

int CPU::RES_0_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT0, 0);
	Logger::LogInstruction("RES", "0", "E");
	return 8;
}

int CPU::RES_1_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT1, 0);
	Logger::LogInstruction("RES", "1", "E");
	return 8;
}

int CPU::RES_2_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT2, 0);
	Logger::LogInstruction("RES", "2", "E");
	return 8;
}

int CPU::RES_3_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT3, 0);
	Logger::LogInstruction("RES", "3", "E");
	return 8;
}

int CPU::RES_4_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT4, 0);
	Logger::LogInstruction("RES", "4", "E");
	return 8;
}

int CPU::RES_5_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT5, 0);
	Logger::LogInstruction("RES", "5", "E");
	return 8;
}

int CPU::RES_6_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT6, 0);
	Logger::LogInstruction("RES", "6", "E");
	return 8;
}

int CPU::RES_7_E() {
	this->DE.lo = SetBit(this->DE.lo, BIT7, 0);
	Logger::LogInstruction("RES", "7", "E");
	return 8;
}

int CPU::RES_0_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT0, 0);
	Logger::LogInstruction("RES", "0", "H");
	return 8;
}

int CPU::RES_1_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT1, 0);
	Logger::LogInstruction("RES", "1", "H");
	return 8;
}

int CPU::RES_2_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT2, 0);
	Logger::LogInstruction("RES", "2", "H");
	return 8;
}

int CPU::RES_3_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT3, 0);
	Logger::LogInstruction("RES", "3", "H");
	return 8;
}

int CPU::RES_4_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT4, 0);
	Logger::LogInstruction("RES", "4", "H");
	return 8;
}

int CPU::RES_5_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT5, 0);
	Logger::LogInstruction("RES", "5", "H");
	return 8;
}

int CPU::RES_6_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT6, 0);
	Logger::LogInstruction("RES", "6", "H");
	return 8;
}

int CPU::RES_7_H() {
	this->HL.hi = SetBit(this->HL.hi, BIT7, 0);
	Logger::LogInstruction("RES", "7", "H");
	return 8;
}

int CPU::RES_0_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT0, 0);
	Logger::LogInstruction("RES", "0", "L");
	return 8;
}

int CPU::RES_1_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT1, 0);
	Logger::LogInstruction("RES", "1", "L");
	return 8;
}

int CPU::RES_2_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT2, 0);
	Logger::LogInstruction("RES", "2", "L");
	return 8;
}

int CPU::RES_3_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT3, 0);
	Logger::LogInstruction("RES", "3", "L");
	return 8;
}

int CPU::RES_4_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT4, 0);
	Logger::LogInstruction("RES", "4", "L");
	return 8;
}

int CPU::RES_5_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT5, 0);
	Logger::LogInstruction("RES", "5", "L");
	return 8;
}

int CPU::RES_6_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT6, 0);
	Logger::LogInstruction("RES", "6", "L");
	return 8;
}

int CPU::RES_7_L() {
	this->HL.lo = SetBit(this->HL.lo, BIT7, 0);
	Logger::LogInstruction("RES", "7", "L");
	return 8;
}

int CPU::RES_0_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT0, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "0", "(HL)");
	return 8;
}

int CPU::RES_1_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT1, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "1", "(HL)");
	return 8;
}

int CPU::RES_2_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT2, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "2", "(HL)");
	return 8;
}

int CPU::RES_3_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT3, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "3", "(HL)");
	return 8;
}

int CPU::RES_4_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT4, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "4", "(HL)");
	return 8;
}

int CPU::RES_5_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT5, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "5", "(HL)");
	return 8;
}

int CPU::RES_6_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT6, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "6", "(HL)");
	return 8;
}

int CPU::RES_7_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SetBit(value, BIT7, 0);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RES", "7", "(HL)");
	return 8;
}

//Swap instructions
int CPU::SWAP_A() {
	this->AF.hi = SWAP(this->AF.hi);
	return 8;
}

int CPU::SWAP_B() {
	this->BC.hi = SWAP(this->BC.hi);
	return 8;
}

int CPU::SWAP_C() {
	this->BC.lo = SWAP(this->BC.lo);
	return 8;
}

int CPU::SWAP_D() {
	this->DE.hi = SWAP(this->DE.hi);
	return 8;
}

int CPU::SWAP_E() {
	this->DE.lo = SWAP(this->DE.lo);
	return 8;
}

int CPU::SWAP_H() {
	this->HL.hi = SWAP(this->HL.hi);
	return 8;
}

int CPU::SWAP_L() {
	this->HL.lo = SWAP(this->HL.lo);
	return 8;
}

int CPU::SWAP_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = SWAP(value);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	return 8;
}

//Rotates
int CPU::RLC_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "A", "");
	return 8;
}

int CPU::RLC_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "B", "");
	return 8;
}

int CPU::RLC_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::left, false);
	Logger::LogInstruction("RLC", "C", "");
	return 8;
}

int CPU::RLC_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "D", "");
	return 8;
}

int CPU::RLC_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::left, false);
	Logger::LogInstruction("RLC", "E", "");
	return 8;
}

int CPU::RLC_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::left, false);
	Logger::LogInstruction("RLC", "H", "");
	return 8;
}

int CPU::RLC_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::left, false);
	Logger::LogInstruction("RLC", "L", "");
	return 8;
}

int CPU::RLC_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::left, false);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RLC", "(HL)", "");
	return 8;
}

int CPU::RLA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, true);
	resetFlag(Flag::z);
	Logger::LogInstruction("RLA", "", "");
	return 4;
}

int CPU::RLCA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left, false);
	resetFlag(Flag::z);
	Logger::LogInstruction("RLCA", "", "");
	return 4;
}

int CPU::RRA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right);
	resetFlag(Flag::z);
	Logger::LogInstruction("RRA", "", "");
	return 4;
}

int CPU::RRCA() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right, false);
	resetFlag(Flag::z);
	Logger::LogInstruction("RRCA", "", "");
	return 4;
}

int CPU::RL_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::left);
	Logger::LogInstruction("RL", "A", "");
	return 8;
}

int CPU::RL_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::left);
	Logger::LogInstruction("RL", "B", "");
	return 8;
}

int CPU::RL_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::left);
	Logger::LogInstruction("RL", "C", "");
	return 8;
}

int CPU::RL_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::left);
	Logger::LogInstruction("RL", "D", "");
	return 8;
}

int CPU::RL_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::left);
	Logger::LogInstruction("RL", "E", "");
	return 8;
}

int CPU::RL_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::left);
	Logger::LogInstruction("RL", "H", "");
	return 8;
}

int CPU::RL_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::left);
	Logger::LogInstruction("RL", "L", "");
	return 8;
}

int CPU::RL_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::left);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RL", "(HL)", "");
	return 8;
}

int CPU::RRC_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "A", "");
	return 8;
}

int CPU::RRC_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "B", "");
	return 8;
}

int CPU::RRC_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::right, false);
	Logger::LogInstruction("RRC", "C", "");
	return 8;
}

int CPU::RRC_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "D", "");
	return 8;
}

int CPU::RRC_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::right, false);
	Logger::LogInstruction("RRC", "E", "");
	return 8;
}

int CPU::RRC_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::right, false);
	Logger::LogInstruction("RRC", "H", "");
	return 8;
}

int CPU::RRC_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::right, false);
	Logger::LogInstruction("RRC", "L", "");
	return 8;
}

int CPU::RRC_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::right, false);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RRC", "(HL)", "");
	return 8;
}

int CPU::RR_A() {
	this->AF.hi = Rotate(this->AF.hi, Direction::right);
	Logger::LogInstruction("RR", "A", "");
	return 8;
}

int CPU::RR_B() {
	this->BC.hi = Rotate(this->BC.hi, Direction::right);
	Logger::LogInstruction("RR", "B", "");
	return 8;
}

int CPU::RR_C() {
	this->BC.lo = Rotate(this->BC.lo, Direction::right);
	Logger::LogInstruction("RR", "C", "");
	return 8;
}

int CPU::RR_D() {
	this->DE.hi = Rotate(this->DE.hi, Direction::right);
	Logger::LogInstruction("RR", "D", "");
	return 8;
}

int CPU::RR_E() {
	this->DE.lo = Rotate(this->DE.lo, Direction::right);
	Logger::LogInstruction("RR", "E", "");
	return 8;
}

int CPU::RR_H() {
	this->HL.hi = Rotate(this->HL.hi, Direction::right);
	Logger::LogInstruction("RR", "H", "");
	return 8;
}

int CPU::RR_L() {
	this->HL.lo = Rotate(this->HL.lo, Direction::right);
	Logger::LogInstruction("RR", "L", "");
	return 8;
}

int CPU::RR_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Rotate(value, Direction::right);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("RR", "(HL)", "");
	return 8;
}

//Shifts
int CPU::SLA_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::left);
	Logger::LogInstruction("SLA", "A", "");
	return 8;
}

int CPU::SLA_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::left);
	Logger::LogInstruction("SLA", "B", "");
	return 8;
}

int CPU::SLA_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::left);
	Logger::LogInstruction("SLA", "C", "");
	return 8;
}

int CPU::SLA_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::left);
	Logger::LogInstruction("SLA", "D", "");
	return 8;
}

int CPU::SLA_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::left);
	Logger::LogInstruction("SLA", "E", "");
	return 8;
}

int CPU::SLA_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::left);
	Logger::LogInstruction("SLA", "H", "");
	return 8;
}

int CPU::SLA_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::left);
	Logger::LogInstruction("SLA", "L", "");
	return 8;
}

int CPU::SLA_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::left);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SLA", "(HL)", "");
	return 8;
}

int CPU::SRA_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "A", "");
	return 8;
}

int CPU::SRA_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "B", "");
	return 8;
}

int CPU::SRA_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::right, false);
	Logger::LogInstruction("SRA", "C", "");
	return 8;
}

int CPU::SRA_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "D", "");
	return 8;
}

int CPU::SRA_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::right, false);
	Logger::LogInstruction("SRA", "E", "");
	return 8;
}

int CPU::SRA_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::right, false);
	Logger::LogInstruction("SRA", "H", "");
	return 8;
}

int CPU::SRA_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::right, false);
	Logger::LogInstruction("SRA", "L", "");
	return 8;
}

int CPU::SRA_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::right, false);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SRA", "(HL)", "");
	return 8;
}

int CPU::SRL_A() {
	this->AF.hi = Shift(this->AF.hi, Direction::right);
	Logger::LogInstruction("SRL", "A", "");
	return 8;
}

int CPU::SRL_B() {
	this->BC.hi = Shift(this->BC.hi, Direction::right);
	Logger::LogInstruction("SRL", "B", "");
	return 8;
}

int CPU::SRL_C() {
	this->BC.lo = Shift(this->BC.lo, Direction::right);
	Logger::LogInstruction("SRL", "C", "");
	return 8;
}

int CPU::SRL_D() {
	this->DE.hi = Shift(this->DE.hi, Direction::right);
	Logger::LogInstruction("SRL", "D", "");
	return 8;
}

int CPU::SRL_E() {
	this->DE.lo = Shift(this->DE.lo, Direction::right);
	Logger::LogInstruction("SRL", "E", "");
	return 8;
}

int CPU::SRL_H() {
	this->HL.hi = Shift(this->HL.hi, Direction::right);
	Logger::LogInstruction("SRL", "H", "");
	return 8;
}

int CPU::SRL_L() {
	this->HL.lo = Shift(this->HL.lo, Direction::right);
	Logger::LogInstruction("SRL", "L", "");
	return 8;
}

int CPU::SRL_HL() {
	UpdateCPUCycles(4);
	BYTE value = this->memory.readByte(this->HL.reg);
	value = Shift(value, Direction::right);
	UpdateCPUCycles(4);
	this->memory.writeByte(this->HL.reg, value);
	Logger::LogInstruction("SRL", "(HL)", "");
	return 8;
}

void CPU::initCBInstructions() {
	for (int i = 0; i < (sizeof((instructions_cb))/sizeof((instructions_cb[0]))); i++ ){
		instructions_cb[i] = NULL;
	}

	//Bit opcodes
	instructions_cb[0x47] = &CPU::BIT_0_A;
	instructions_cb[0x4F] = &CPU::BIT_1_A;
	instructions_cb[0x57] = &CPU::BIT_2_A;
	instructions_cb[0x5F] = &CPU::BIT_3_A;
	instructions_cb[0x67] = &CPU::BIT_4_A;
	instructions_cb[0x6F] = &CPU::BIT_5_A;
	instructions_cb[0x77] = &CPU::BIT_6_A;
	instructions_cb[0x7F] = &CPU::BIT_7_A;
	instructions_cb[0x40] = &CPU::BIT_0_B;
	instructions_cb[0x48] = &CPU::BIT_1_B;
	instructions_cb[0x50] = &CPU::BIT_2_B;
	instructions_cb[0x58] = &CPU::BIT_3_B;
	instructions_cb[0x60] = &CPU::BIT_4_B;
	instructions_cb[0x68] = &CPU::BIT_5_B;
	instructions_cb[0x70] = &CPU::BIT_6_B;
	instructions_cb[0x78] = &CPU::BIT_7_B;
	instructions_cb[0x41] = &CPU::BIT_0_C;
	instructions_cb[0x49] = &CPU::BIT_1_C;
	instructions_cb[0x51] = &CPU::BIT_2_C;
	instructions_cb[0x59] = &CPU::BIT_3_C;
	instructions_cb[0x61] = &CPU::BIT_4_C;
	instructions_cb[0x69] = &CPU::BIT_5_C;
	instructions_cb[0x71] = &CPU::BIT_6_C;
	instructions_cb[0x79] = &CPU::BIT_7_C;
	instructions_cb[0x42] = &CPU::BIT_0_D;
	instructions_cb[0x4A] = &CPU::BIT_1_D;
	instructions_cb[0x52] = &CPU::BIT_2_D;
	instructions_cb[0x5A] = &CPU::BIT_3_D;
	instructions_cb[0x62] = &CPU::BIT_4_D;
	instructions_cb[0x6A] = &CPU::BIT_5_D;
	instructions_cb[0x72] = &CPU::BIT_6_D;
	instructions_cb[0x7A] = &CPU::BIT_7_D;
	instructions_cb[0x43] = &CPU::BIT_0_E;
	instructions_cb[0x4B] = &CPU::BIT_1_E;
	instructions_cb[0x53] = &CPU::BIT_2_E;
	instructions_cb[0x5B] = &CPU::BIT_3_E;
	instructions_cb[0x63] = &CPU::BIT_4_E;
	instructions_cb[0x6B] = &CPU::BIT_5_E;
	instructions_cb[0x73] = &CPU::BIT_6_E;
	instructions_cb[0x7B] = &CPU::BIT_7_E;
	instructions_cb[0x44] = &CPU::BIT_0_H;
	instructions_cb[0x4C] = &CPU::BIT_1_H;
	instructions_cb[0x54] = &CPU::BIT_2_H;
	instructions_cb[0x5C] = &CPU::BIT_3_H;
	instructions_cb[0x64] = &CPU::BIT_4_H;
	instructions_cb[0x6C] = &CPU::BIT_5_H;
	instructions_cb[0x74] = &CPU::BIT_6_H;
	instructions_cb[0x7C] = &CPU::BIT_7_H;
	instructions_cb[0x45] = &CPU::BIT_0_L;
	instructions_cb[0x4D] = &CPU::BIT_1_L;
	instructions_cb[0x55] = &CPU::BIT_2_L;
	instructions_cb[0x5D] = &CPU::BIT_3_L;
	instructions_cb[0x65] = &CPU::BIT_4_L;
	instructions_cb[0x6D] = &CPU::BIT_5_L;
	instructions_cb[0x75] = &CPU::BIT_6_L;
	instructions_cb[0x7D] = &CPU::BIT_7_L;
	instructions_cb[0x46] = &CPU::BIT_0_HL;
	instructions_cb[0x4E] = &CPU::BIT_1_HL;
	instructions_cb[0x56] = &CPU::BIT_2_HL;
	instructions_cb[0x5E] = &CPU::BIT_3_HL;
	instructions_cb[0x66] = &CPU::BIT_4_HL;
	instructions_cb[0x6E] = &CPU::BIT_5_HL;
	instructions_cb[0x76] = &CPU::BIT_6_HL;
	instructions_cb[0x7E] = &CPU::BIT_7_HL;

	instructions_cb[0xC7] = &CPU::SET_0_A;
	instructions_cb[0xCF] = &CPU::SET_1_A;
	instructions_cb[0xD7] = &CPU::SET_2_A;
	instructions_cb[0xDF] = &CPU::SET_3_A;
	instructions_cb[0xE7] = &CPU::SET_4_A;
	instructions_cb[0xEF] = &CPU::SET_5_A;
	instructions_cb[0xF7] = &CPU::SET_6_A;
	instructions_cb[0xFF] = &CPU::SET_7_A;
	instructions_cb[0xC0] = &CPU::SET_0_B;
	instructions_cb[0xC8] = &CPU::SET_1_B;
	instructions_cb[0xD0] = &CPU::SET_2_B;
	instructions_cb[0xD8] = &CPU::SET_3_B;
	instructions_cb[0xE0] = &CPU::SET_4_B;
	instructions_cb[0xE8] = &CPU::SET_5_B;
	instructions_cb[0xF0] = &CPU::SET_6_B;
	instructions_cb[0xF8] = &CPU::SET_7_B;
	instructions_cb[0xC1] = &CPU::SET_0_C;
	instructions_cb[0xC9] = &CPU::SET_1_C;
	instructions_cb[0xD1] = &CPU::SET_2_C;
	instructions_cb[0xD9] = &CPU::SET_3_C;
	instructions_cb[0xE1] = &CPU::SET_4_C;
	instructions_cb[0xE9] = &CPU::SET_5_C;
	instructions_cb[0xF1] = &CPU::SET_6_C;
	instructions_cb[0xF9] = &CPU::SET_7_C;
	instructions_cb[0xC2] = &CPU::SET_0_D;
	instructions_cb[0xCA] = &CPU::SET_1_D;
	instructions_cb[0xD2] = &CPU::SET_2_D;
	instructions_cb[0xDA] = &CPU::SET_3_D;
	instructions_cb[0xE2] = &CPU::SET_4_D;
	instructions_cb[0xEA] = &CPU::SET_5_D;
	instructions_cb[0xF2] = &CPU::SET_6_D;
	instructions_cb[0xFA] = &CPU::SET_7_D;
	instructions_cb[0xC3] = &CPU::SET_0_E;
	instructions_cb[0xCB] = &CPU::SET_1_E;
	instructions_cb[0xD3] = &CPU::SET_2_E;
	instructions_cb[0xDB] = &CPU::SET_3_E;
	instructions_cb[0xE3] = &CPU::SET_4_E;
	instructions_cb[0xEB] = &CPU::SET_5_E;
	instructions_cb[0xF3] = &CPU::SET_6_E;
	instructions_cb[0xFB] = &CPU::SET_7_E;
	instructions_cb[0xC4] = &CPU::SET_0_H;
	instructions_cb[0xCC] = &CPU::SET_1_H;
	instructions_cb[0xD4] = &CPU::SET_2_H;
	instructions_cb[0xDC] = &CPU::SET_3_H;
	instructions_cb[0xE4] = &CPU::SET_4_H;
	instructions_cb[0xEC] = &CPU::SET_5_H;
	instructions_cb[0xF4] = &CPU::SET_6_H;
	instructions_cb[0xFC] = &CPU::SET_7_H;
	instructions_cb[0xC5] = &CPU::SET_0_L;
	instructions_cb[0xCD] = &CPU::SET_1_L;
	instructions_cb[0xD5] = &CPU::SET_2_L;
	instructions_cb[0xDD] = &CPU::SET_3_L;
	instructions_cb[0xE5] = &CPU::SET_4_L;
	instructions_cb[0xED] = &CPU::SET_5_L;
	instructions_cb[0xF5] = &CPU::SET_6_L;
	instructions_cb[0xFD] = &CPU::SET_7_L;
	instructions_cb[0xC6] = &CPU::SET_0_HL;
	instructions_cb[0xCE] = &CPU::SET_1_HL;
	instructions_cb[0xD6] = &CPU::SET_2_HL;
	instructions_cb[0xDE] = &CPU::SET_3_HL;
	instructions_cb[0xE6] = &CPU::SET_4_HL;
	instructions_cb[0xEE] = &CPU::SET_5_HL;
	instructions_cb[0xF6] = &CPU::SET_6_HL;
	instructions_cb[0xFE] = &CPU::SET_7_HL;

	instructions_cb[0x87] = &CPU::RES_0_A;
	instructions_cb[0x8F] = &CPU::RES_1_A;
	instructions_cb[0x97] = &CPU::RES_2_A;
	instructions_cb[0x9F] = &CPU::RES_3_A;
	instructions_cb[0xA7] = &CPU::RES_4_A;
	instructions_cb[0xAF] = &CPU::RES_5_A;
	instructions_cb[0xB7] = &CPU::RES_6_A;
	instructions_cb[0xBF] = &CPU::RES_7_A;
	instructions_cb[0x80] = &CPU::RES_0_B;
	instructions_cb[0x88] = &CPU::RES_1_B;
	instructions_cb[0x90] = &CPU::RES_2_B;
	instructions_cb[0x98] = &CPU::RES_3_B;
	instructions_cb[0xA0] = &CPU::RES_4_B;
	instructions_cb[0xA8] = &CPU::RES_5_B;
	instructions_cb[0xB0] = &CPU::RES_6_B;
	instructions_cb[0xB8] = &CPU::RES_7_B;
	instructions_cb[0x81] = &CPU::RES_0_C;
	instructions_cb[0x89] = &CPU::RES_1_C;
	instructions_cb[0x91] = &CPU::RES_2_C;
	instructions_cb[0x99] = &CPU::RES_3_C;
	instructions_cb[0xA1] = &CPU::RES_4_C;
	instructions_cb[0xA9] = &CPU::RES_5_C;
	instructions_cb[0xB1] = &CPU::RES_6_C;
	instructions_cb[0xB9] = &CPU::RES_7_C;
	instructions_cb[0x82] = &CPU::RES_0_D;
	instructions_cb[0x8A] = &CPU::RES_1_D;
	instructions_cb[0x92] = &CPU::RES_2_D;
	instructions_cb[0x9A] = &CPU::RES_3_D;
	instructions_cb[0xA2] = &CPU::RES_4_D;
	instructions_cb[0xAA] = &CPU::RES_5_D;
	instructions_cb[0xB2] = &CPU::RES_6_D;
	instructions_cb[0xBA] = &CPU::RES_7_D;
	instructions_cb[0x83] = &CPU::RES_0_E;
	instructions_cb[0x8B] = &CPU::RES_1_E;
	instructions_cb[0x93] = &CPU::RES_2_E;
	instructions_cb[0x9B] = &CPU::RES_3_E;
	instructions_cb[0xA3] = &CPU::RES_4_E;
	instructions_cb[0xAB] = &CPU::RES_5_E;
	instructions_cb[0xB3] = &CPU::RES_6_E;
	instructions_cb[0xBB] = &CPU::RES_7_E;
	instructions_cb[0x84] = &CPU::RES_0_H;
	instructions_cb[0x8C] = &CPU::RES_1_H;
	instructions_cb[0x94] = &CPU::RES_2_H;
	instructions_cb[0x9C] = &CPU::RES_3_H;
	instructions_cb[0xA4] = &CPU::RES_4_H;
	instructions_cb[0xAC] = &CPU::RES_5_H;
	instructions_cb[0xB4] = &CPU::RES_6_H;
	instructions_cb[0xBC] = &CPU::RES_7_H;
	instructions_cb[0x85] = &CPU::RES_0_L;
	instructions_cb[0x8D] = &CPU::RES_1_L;
	instructions_cb[0x95] = &CPU::RES_2_L;
	instructions_cb[0x9D] = &CPU::RES_3_L;
	instructions_cb[0xA5] = &CPU::RES_4_L;
	instructions_cb[0xAD] = &CPU::RES_5_L;
	instructions_cb[0xB5] = &CPU::RES_6_L;
	instructions_cb[0xBD] = &CPU::RES_7_L;
	instructions_cb[0x86] = &CPU::RES_0_HL;
	instructions_cb[0x8E] = &CPU::RES_1_HL;
	instructions_cb[0x96] = &CPU::RES_2_HL;
	instructions_cb[0x9E] = &CPU::RES_3_HL;
	instructions_cb[0xA6] = &CPU::RES_4_HL;
	instructions_cb[0xAE] = &CPU::RES_5_HL;
	instructions_cb[0xB6] = &CPU::RES_6_HL;
	instructions_cb[0xBE] = &CPU::RES_7_HL;

	//Swap
	instructions_cb[0x37] = &CPU::SWAP_A;
	instructions_cb[0x30] = &CPU::SWAP_B;
	instructions_cb[0x31] = &CPU::SWAP_C;
	instructions_cb[0x32] = &CPU::SWAP_D;
	instructions_cb[0x33] = &CPU::SWAP_E;
	instructions_cb[0x34] = &CPU::SWAP_H;
	instructions_cb[0x35] = &CPU::SWAP_L;
	instructions_cb[0x36] = &CPU::SWAP_HL;

	//Rotates
	instructions[0x17] = &CPU::RLA;
	instructions[0x07] = &CPU::RLCA;
	instructions[0x1F] = &CPU::RRA;
	instructions[0x0F] = &CPU::RRCA;

	instructions_cb[0x07] = &CPU::RLC_A;
	instructions_cb[0x00] = &CPU::RLC_B;
	instructions_cb[0x01] = &CPU::RLC_C;
	instructions_cb[0x02] = &CPU::RLC_D;
	instructions_cb[0x03] = &CPU::RLC_E;
	instructions_cb[0x04] = &CPU::RLC_H;
	instructions_cb[0x05] = &CPU::RLC_L;
	instructions_cb[0x06] = &CPU::RLC_HL;

	instructions_cb[0x17] = &CPU::RL_A;
	instructions_cb[0x10] = &CPU::RL_B;
	instructions_cb[0x11] = &CPU::RL_C;
	instructions_cb[0x12] = &CPU::RL_D;
	instructions_cb[0x13] = &CPU::RL_E;
	instructions_cb[0x14] = &CPU::RL_H;
	instructions_cb[0x15] = &CPU::RL_L;
	instructions_cb[0x16] = &CPU::RL_HL;

	instructions_cb[0x0F] = &CPU::RRC_A;
	instructions_cb[0x08] = &CPU::RRC_B;
	instructions_cb[0x09] = &CPU::RRC_C;
	instructions_cb[0x0A] = &CPU::RRC_D;
	instructions_cb[0x0B] = &CPU::RRC_E;
	instructions_cb[0x0C] = &CPU::RRC_H;
	instructions_cb[0x0D] = &CPU::RRC_L;
	instructions_cb[0x0E] = &CPU::RRC_HL;

	instructions_cb[0x1F] = &CPU::RR_A;
	instructions_cb[0x18] = &CPU::RR_B;
	instructions_cb[0x19] = &CPU::RR_C;
	instructions_cb[0x1A] = &CPU::RR_D;
	instructions_cb[0x1B] = &CPU::RR_E;
	instructions_cb[0x1C] = &CPU::RR_H;
	instructions_cb[0x1D] = &CPU::RR_L;
	instructions_cb[0x1E] = &CPU::RR_HL;

	instructions_cb[0x27] = &CPU::SLA_A;
	instructions_cb[0x20] = &CPU::SLA_B;
	instructions_cb[0x21] = &CPU::SLA_C;
	instructions_cb[0x22] = &CPU::SLA_D;
	instructions_cb[0x23] = &CPU::SLA_E;
	instructions_cb[0x24] = &CPU::SLA_H;
	instructions_cb[0x25] = &CPU::SLA_L;
	instructions_cb[0x26] = &CPU::SLA_HL;

	instructions_cb[0x2F] = &CPU::SRA_A;
	instructions_cb[0x28] = &CPU::SRA_B;
	instructions_cb[0x29] = &CPU::SRA_C;
	instructions_cb[0x2A] = &CPU::SRA_D;
	instructions_cb[0x2B] = &CPU::SRA_E;
	instructions_cb[0x2C] = &CPU::SRA_H;
	instructions_cb[0x2D] = &CPU::SRA_L;
	instructions_cb[0x2E] = &CPU::SRA_HL;

	instructions_cb[0x3F] = &CPU::SRL_A;
	instructions_cb[0x38] = &CPU::SRL_B;
	instructions_cb[0x39] = &CPU::SRL_C;
	instructions_cb[0x3A] = &CPU::SRL_D;
	instructions_cb[0x3B] = &CPU::SRL_E;
	instructions_cb[0x3C] = &CPU::SRL_H;
	instructions_cb[0x3D] = &CPU::SRL_L;
	instructions_cb[0x3E] = &CPU::SRL_HL;
}