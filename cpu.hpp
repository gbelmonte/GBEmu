#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "common.hpp"
#include "memory.hpp"
#include "gpu.hpp"
#include "logger.hpp"

using namespace std;

class CPU{

	public:
		CPU();
		~CPU();

		void LoadCartridge(char* path);
		void Run();

		static Uint32 ExecuteFrame(Uint32 interval, void *param);

	private:
		Register AF;
		Register BC;
		Register DE;
		Register HL;
		
		Register SP;
		Register PC;

		Memory memory;
		GPU gpu;

		int cyclesThisFrame;
		int cycleCounter;
		int dividerCounter;
		int timerCounter;
		int timerFrequency;
		
		bool interruptEnabled;
		bool halt;
		bool quit;
		bool debug;

		SDL_TimerID timerID;

		int (CPU::*instructions[300])();
		int (CPU::*instructions_cb[300])();

		BYTE Fetch();
		int DecodeExecute(BYTE opcode);
		void UpdateScreen(int cycles);
		void RenderScreen();
		bool CheckInput();
		void HandleInterrupt();
		void UpdateTimers(int cycles);
		void UpdateCPUCycles(int cycles);
		bool IsOn();

		void DrawLine();
		void updateDividerTimer(int cycles);
		void updateTimerFrequency();

		Interrupt getInterrupt(BYTE interruptFlag, BYTE enabled);
		void requestInterrupt(Interrupt interrupt);
		
		BYTE getFlag(Flag flag);
		void setFlag(Flag flag);
		void resetFlag(Flag flag);

		//instructions
		int NOP();
		int STOP();
		int HALT();

		//load immediates
		int LD_A_n();
		int LD_B_n();
		int LD_C_n();
		int LD_D_n();
		int LD_E_n();
		int LD_H_n();
		int LD_L_n();

		int LD_A_A();
		int LD_A_B();
		int LD_A_C();
		int LD_A_D();
		int LD_A_E();
		int LD_A_H();
		int LD_A_L();
		int LD_A_BC();
		int LD_A_DE();
		int LD_A_HL();
		int LD_A_nn();

		int LD_B_B();
		int LD_B_C();
		int LD_B_D();
		int LD_B_E();
		int LD_B_H();
		int LD_B_L();
		int LD_B_HL();

		int LD_C_B();
		int LD_C_C();
		int LD_C_D();
		int LD_C_E();
		int LD_C_H();
		int LD_C_L();
		int LD_C_HL();

		int LD_D_B();
		int LD_D_C();
		int LD_D_D();
		int LD_D_E();
		int LD_D_H();
		int LD_D_L();
		int LD_D_HL();

		int LD_E_B();
		int LD_E_C();
		int LD_E_D();
		int LD_E_E();
		int LD_E_H();
		int LD_E_L();
		int LD_E_HL();

		int LD_H_B();
		int LD_H_C();
		int LD_H_D();
		int LD_H_E();
		int LD_H_H();
		int LD_H_L();
		int LD_H_HL();

		int LD_L_B();
		int LD_L_C();
		int LD_L_D();
		int LD_L_E();
		int LD_L_H();
		int LD_L_L();
		int LD_L_HL();

		int LD_B_A();
		int LD_C_A();
		int LD_D_A();
		int LD_E_A();
		int LD_H_A();
		int LD_L_A();
		int LD_BC_A();
		int LD_DE_A();
		int LD_nn_A();

		int LD_HL_A();
		int LD_HL_B();
		int LD_HL_C();
		int LD_HL_D();
		int LD_HL_E();
		int LD_HL_H();
		int LD_HL_L();
		int LD_HL_n();

		int LD_A_FF00_C();
		int LD_FF00_C_A();
		int LD_FF00_n_A();
		int LDH_A_FF00_n();
		int LDHL_SP_n();

		//Load Dec/Inc
		int LDD_HL_A();
		int LDI_HL_A();
		int LDD_A_HL();
		int LDI_A_HL();

		//16 bit loads
		int LD_SP_HL();
		int LD_BC_nn();
		int LD_DE_nn();
		int LD_HL_nn();
		int LD_SP_nn();
		int LD_nn_SP();

		//ADD
		BYTE Add(BYTE operand1, BYTE operand2, bool addCarryFlag = false);
		int ADD_A();
		int ADD_B();
		int ADD_C();
		int ADD_D();
		int ADD_E();
		int ADD_H();
		int ADD_L();
		int ADD_HL();
		int ADD_n();

		int ADD_SP_n();

		WORD Add16Bit(WORD operand1, WORD operand2);
		WORD Add16BitSigned(WORD operand1, SIGNED_BYTE operand2);
		int ADD_HL_BC();
		int ADD_HL_DE();
		int ADD_HL_HL();
		int ADD_HL_SP();

		int ADC_A();
		int ADC_B();
		int ADC_C();
		int ADC_D();
		int ADC_E();
		int ADC_H();
		int ADC_L();
		int ADC_HL();
		int ADC_n();

		//SUB
		BYTE Subtract(BYTE from, BYTE sub, bool subCarryFlag = false);
		int SUB_A();
		int SUB_B();
		int SUB_C();
		int SUB_D();
		int SUB_E();
		int SUB_H();
		int SUB_L();
		int SUB_HL();
		int SUB_n();

		int SBC_A();
		int SBC_B();
		int SBC_C();
		int SBC_D();
		int SBC_E();
		int SBC_H();
		int SBC_L();
		int SBC_HL();
		int SBC_n();

		//XOR
		BYTE XOR(BYTE operand1, BYTE operand2);
		int XOR_A();
		int XOR_B();
		int XOR_C();
		int XOR_D();
		int XOR_E();
		int XOR_H();
		int XOR_L();
		int XOR_HL();
		int XOR_n();

		//And
		BYTE AND(BYTE operand1, BYTE operand2);
		int AND_A();
		int AND_B();
		int AND_C();
		int AND_D();
		int AND_E();
		int AND_H();
		int AND_l();
		int AND_HL();
		int AND_n();

		//Or
		BYTE OR(BYTE operand1, BYTE operand2);
		int OR_A();
		int OR_B();
		int OR_C();
		int OR_D();
		int OR_E();
		int OR_H();
		int OR_L();
		int OR_HL();
		int OR_n();

		int DAA();
		int CPL();

		int SCF();
		int CCF();

		//CP
		void Compare(BYTE value);
		int CP_A();
		int CP_B();
		int CP_C();
		int CP_D();
		int CP_E();
		int CP_H();
		int CP_L();
		int CP_MEM_HL();
		int CP_n();

		//Jumps
		int JR_NZ();
		int JR_Z();
		int JR_NC();
		int JR_C();
		int JR();
		int JP_nn();
		int JP_NZ();
		int JP_Z();
		int JP_NC();
		int JP_C();
		int JP_HL();

		//Stack instructions
		void PushReg(WORD reg);
		WORD PopReg();
		void PushByte(BYTE value);
		BYTE PopByte();

		int CALL_nn();
		int CALL_NZ_nn();
		int CALL_Z_nn();
		int CALL_NC_nn();
		int CALL_C_nn(); 
		int RET();
		int RET_NZ();
		int RET_Z();
		int RET_NC();
		int RET_C();
		int RETI();
		int PUSH_AF();
		int PUSH_BC();
		int PUSH_DE();
		int PUSH_HL();
		int POP_AF();
		int POP_BC();
		int POP_DE();
		int POP_HL();

		int RST_00();
		int RST_08();
		int RST_10();
		int RST_18();
		int RST_20();
		int RST_28();
		int RST_30();
		int RST_38();

		//Increments
		BYTE RegInc(BYTE value);
		int INC_A();
		int INC_B();
		int INC_C();
		int INC_D();
		int INC_E();
		int INC_H();
		int INC_L();
		int INC_MEM_HL();

		int INC_BC();
		int INC_DE();
		int INC_HL();
		int INC_SP();

		BYTE RegDec(BYTE value);
		int DEC_A();
		int DEC_B();
		int DEC_C();
		int DEC_D();
		int DEC_E();
		int DEC_H();
		int DEC_L();
		int DEC_MEM_HL();

		int DEC_BC();
		int DEC_DE();
		int DEC_HL();
		int DEC_SP();

		//Bit
		BYTE GetBit(BYTE value, int bitPos);
		void TestBit(BYTE byte, BYTE mask);

		int BIT_0_A();
		int BIT_1_A();
		int BIT_2_A();
		int BIT_3_A();
		int BIT_4_A();
		int BIT_5_A();
		int BIT_6_A();
		int BIT_7_A();

		int BIT_0_B();
		int BIT_1_B();
		int BIT_2_B();
		int BIT_3_B();
		int BIT_4_B();
		int BIT_5_B();
		int BIT_6_B();
		int BIT_7_B();

		int BIT_0_C();
		int BIT_1_C();
		int BIT_2_C();
		int BIT_3_C();
		int BIT_4_C();
		int BIT_5_C();
		int BIT_6_C();
		int BIT_7_C();

		int BIT_0_D();
		int BIT_1_D();
		int BIT_2_D();
		int BIT_3_D();
		int BIT_4_D();
		int BIT_5_D();
		int BIT_6_D();
		int BIT_7_D();

		int BIT_0_E();
		int BIT_1_E();
		int BIT_2_E();
		int BIT_3_E();
		int BIT_4_E();
		int BIT_5_E();
		int BIT_6_E();
		int BIT_7_E();

		int BIT_0_H();
		int BIT_1_H();
		int BIT_2_H();
		int BIT_3_H();
		int BIT_4_H();
		int BIT_5_H();
		int BIT_6_H();
		int BIT_7_H();

		int BIT_0_L();
		int BIT_1_L();
		int BIT_2_L();
		int BIT_3_L();
		int BIT_4_L();
		int BIT_5_L();
		int BIT_6_L();
		int BIT_7_L();

		int BIT_0_HL();
		int BIT_1_HL();
		int BIT_2_HL();
		int BIT_3_HL();
		int BIT_4_HL();
		int BIT_5_HL();
		int BIT_6_HL();
		int BIT_7_HL();

		BYTE SetBit(BYTE byte, BYTE bitMask, BYTE value);
		int SET_0_A();
		int SET_1_A();
		int SET_2_A();
		int SET_3_A();
		int SET_4_A();
		int SET_5_A();
		int SET_6_A();
		int SET_7_A();

		int SET_0_B();
		int SET_1_B();
		int SET_2_B();
		int SET_3_B();
		int SET_4_B();
		int SET_5_B();
		int SET_6_B();
		int SET_7_B();

		int SET_0_C();
		int SET_1_C();
		int SET_2_C();
		int SET_3_C();
		int SET_4_C();
		int SET_5_C();
		int SET_6_C();
		int SET_7_C();

		int SET_0_D();
		int SET_1_D();
		int SET_2_D();
		int SET_3_D();
		int SET_4_D();
		int SET_5_D();
		int SET_6_D();
		int SET_7_D();

		int SET_0_E();
		int SET_1_E();
		int SET_2_E();
		int SET_3_E();
		int SET_4_E();
		int SET_5_E();
		int SET_6_E();
		int SET_7_E();

		int SET_0_H();
		int SET_1_H();
		int SET_2_H();
		int SET_3_H();
		int SET_4_H();
		int SET_5_H();
		int SET_6_H();
		int SET_7_H();

		int SET_0_L();
		int SET_1_L();
		int SET_2_L();
		int SET_3_L();
		int SET_4_L();
		int SET_5_L();
		int SET_6_L();
		int SET_7_L();

		int SET_0_HL();
		int SET_1_HL();
		int SET_2_HL();
		int SET_3_HL();
		int SET_4_HL();
		int SET_5_HL();
		int SET_6_HL();
		int SET_7_HL();

		int RES_0_A();
		int RES_1_A();
		int RES_2_A();
		int RES_3_A();
		int RES_4_A();
		int RES_5_A();
		int RES_6_A();
		int RES_7_A();

		int RES_0_B();
		int RES_1_B();
		int RES_2_B();
		int RES_3_B();
		int RES_4_B();
		int RES_5_B();
		int RES_6_B();
		int RES_7_B();

		int RES_0_C();
		int RES_1_C();
		int RES_2_C();
		int RES_3_C();
		int RES_4_C();
		int RES_5_C();
		int RES_6_C();
		int RES_7_C();

		int RES_0_D();
		int RES_1_D();
		int RES_2_D();
		int RES_3_D();
		int RES_4_D();
		int RES_5_D();
		int RES_6_D();
		int RES_7_D();

		int RES_0_E();
		int RES_1_E();
		int RES_2_E();
		int RES_3_E();
		int RES_4_E();
		int RES_5_E();
		int RES_6_E();
		int RES_7_E();

		int RES_0_H();
		int RES_1_H();
		int RES_2_H();
		int RES_3_H();
		int RES_4_H();
		int RES_5_H();
		int RES_6_H();
		int RES_7_H();

		int RES_0_L();
		int RES_1_L();
		int RES_2_L();
		int RES_3_L();
		int RES_4_L();
		int RES_5_L();
		int RES_6_L();
		int RES_7_L();

		int RES_0_HL();
		int RES_1_HL();
		int RES_2_HL();
		int RES_3_HL();
		int RES_4_HL();
		int RES_5_HL();
		int RES_6_HL();
		int RES_7_HL();

		//Swap
		BYTE SWAP(BYTE value);
		int SWAP_A();
		int SWAP_B();
		int SWAP_C();
		int SWAP_D();
		int SWAP_E();
		int SWAP_H();
		int SWAP_L();
		int SWAP_HL();

		//Rotates
		BYTE Rotate(BYTE value, Direction direction, bool fromC = true);
		BYTE Shift(BYTE value, Direction direction, bool resetSB = true);

		int RLA();
		int RLCA();
		int RRA();
		int RRCA();

		int RLC_A();
		int RLC_B();
		int RLC_C();
		int RLC_D();
		int RLC_E();
		int RLC_H();
		int RLC_L();
		int RLC_HL();

		int RL_A();
		int RL_B();
		int RL_C();
		int RL_D();
		int RL_E();
		int RL_H();
		int RL_L();
		int RL_HL();

		int RRC_A();
		int RRC_B();
		int RRC_C();
		int RRC_D();
		int RRC_E();
		int RRC_H();
		int RRC_L();
		int RRC_HL();

		int RR_A();
		int RR_B();
		int RR_C();
		int RR_D();
		int RR_E();
		int RR_H();
		int RR_L();
		int RR_HL();

		int SLA_A();
		int SLA_B();
		int SLA_C();
		int SLA_D();
		int SLA_E();
		int SLA_H();
		int SLA_L();
		int SLA_HL();

		int SRA_A();
		int SRA_B();
		int SRA_C();
		int SRA_D();
		int SRA_E();
		int SRA_H();
		int SRA_L();
		int SRA_HL();

		int SRL_A();
		int SRL_B();
		int SRL_C();
		int SRL_D();
		int SRL_E();
		int SRL_H();
		int SRL_L();
		int SRL_HL();

		int DI();
		int EI();
};