#include "cpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATA_LEN 6




void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  unsigned int a;
  unsigned int b;
  unsigned char instructs;
  
  int v;
  int rob;
  int riner;

  int equals = 0;
  int less = 0;
  int greater = 0;

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    instructs = cpu->ram[cpu->pc];


    // 2. Figure out how many operands this next instruction requires
    int numberof = (instructs >> 6) +1;
    
    
    // 3. Get the appropriate value(s) of the operands following this instruction
    if (numberof > 1) {
      a = cpu->ram[cpu->pc +1];
    }

    elif (numberof > 2) {
      b = cpu->ram[cpu->pc +2];

    }



    // 4. switch() over it to decide on a course of action.
    swith(instructs) {
      case JEP:
      if (equals) {
        //printf("BOB \n");
        rob = cpu->ram[cpu->pc +1];
        cpu->pc = cpu->registers[rob];

      }
      else {
        cpu -> pc= pc + numberof;
      }

      break;

      
    
      
    
    }
    


    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
}
