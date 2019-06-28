#include "cpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATA_LEN 6


#define SP 7

unsigned char ram_read(struct cpu *cpu, char address) {
  return cpu->ram[address];
}

char ram_write(struct cpu *cpu, char address, char value) {
  return cpu->ram[address] = value;
}

char pop(struct cpu *cpu) {

  char value = cpu->ram[cpu->registers[SP]];

  cpu->registers[SP]++;

  return value;
}




void cpu_load(struct cpu *cpu)
{
  
    printf("hello cpu load thing");

}





void push(struct cpu *cpu, char val) {
    //
    cpu->registers[SP]--;

    ram_write(cpu, cpu->registers[SP], val );
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
    

}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
}
