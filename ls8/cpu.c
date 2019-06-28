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




void cpu_load(struct cpu *cpu, int argc, char *argv[]){
  
    // printf("hello cpu load thing");

    FILE *fp;


    char line[128];

    if (argc != 2) {
        printf("usage: ls8 folder/filename\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("file %s does not exist\n", argv[1]);
        exit(1);
    }

    int address = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *endptr;
        unsigned char value = strtoul(line, &endptr, 2);

        if (line == endptr) {
        continue;
        }

        cpu_ram_write(cpu, address, value);
        address++;
    }

    fclose(fp);

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
  switch (op)
  {
  case ALU_MUL:
    // TODO
    cpu->registers[regA] *= cpu->registers[regB];
    break;

  case ALU_ADD:
    cpu->registers[regA] += cpu->registers[regB];
    break;



  case ALU_CMP:
    if (cpu->registers[regA] == cpu->registers[regB])
    {
      cpu->FL = 1;
    }
    else if (cpu->registers[regA] > cpu->registers[regB])
    {
      cpu->FL = 2;
    }
    else
    {
      cpu->FL = 4;
    }
    break;
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
    char IR = ram_read(cpu, cpu->PC);


    // 2. Figure out how many operands this next instruction requires
    int operands = (IR >> 6) + 1;
    
    
    // 3. Get the appropriate value(s) of the operands following this instruction
    char opA = ram_read(cpu, (cpu->PC + 1) & 0xFF);
    char opB = ram_read(cpu, (cpu->PC + 2) & 0xFF);


    swith(instructs) {
      case HLT:
        running = 0;

        break;

      case LDI:
        cpu->registers[opA] = opB;

        break;

      case PRN:
        printf(" %d \n", cpu->registers[opA]);
        break;

      case MUL:
        alu(cpu, ALU_MUL, opA, opB);

        break;

      case POP:
        cpu->registers[opA] = pop(cpu);
        
        break;

      

      case CMP:
        alu(cpu, ALU_CMP, opA, opB);
        break;



      case JMP:
        cpu->PC = cpu->registers[opA];

        operands = 0;
        break;

      case JEQ:
        if (cpu->FL == 0b00000001) {

          cpu->PC = cpu->registers[opA];
          operands = 0;

        }
        break;

      case JNE:
        if ((cpu->FL == 0b00000001) == 0) {

          cpu->PC = cpu->registers[opA];
          operands = 0;

        }
        break;
    
    }
  

}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  
  cpu->PC = 0;

  cpu->FL = 0;

  
  memset(cpu->ram, 0, sizeof(cpu->ram));
  memset(cpu->registers, 0, sizeof(cpu->registers));

  
  cpu->registers[7] = 0xF4;
}
