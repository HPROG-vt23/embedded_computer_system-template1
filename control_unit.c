/********************************************************************************
* control_unit.c: Contains static variables and function definitions for 
*                 implementation of an 8-bit control unit.
********************************************************************************/
#include "control_unit.h"

/* Static variables: */
static uint32_t ir; /* Instruction register, stores next instruction to execute. */
static uint8_t pc;  /* Program counter, stores address to next instruction to fetch. */
static uint8_t mar; /* Memory address register, stores address for current instruction. */
static uint8_t sr;  /* Status register, stores status bits ISNZVC. */

static uint8_t op_code; /* Stores OP-code, for example LDI, OUT, JMP etc. */
static uint8_t op1;     /* Stores first operand, most often a destination. */
static uint8_t op2;     /* Stores second operand, most often a value or read address. */

static enum cpu_state state;                    /* Stores current state. */
static uint8_t reg[CPU_REGISTER_ADDRESS_WIDTH]; /* CPU-registers R0 - R31. */

/* Temporary memories: */
static uint8_t data_memory[2000]; /* Contains I/O-addresses and stores static variables. */

const static uint32_t program_memory[] = /* Program memory, stores code. */
{
   0x160500, /* JMP 0x05 */
   0x000000, /* NOP */
   0x000000, /* NOP */
   0x000000, /* NOP */
   0x000000, /* NOP */
   0x011001, /* LDI R16, 0x01 */
   0x030010, /* OUT DDRB, R16 */
   0x021110, /* MOV R17, R16 */
   0x011020, /* LDI R16, 0x20 */
   0x030110, /* OUT PORTB, R16 */
   0x030211, /* OUT PINB, R17 */
   0x041002, /* IN R16, PINB */
   0x160500  /* JMP 0x05 */
};

/********************************************************************************
* control_unit_reset: Resets control unit registers and corresponding program.
********************************************************************************/
void control_unit_reset(void)
{
   return;
}

/********************************************************************************
* control_unit_run_next_state: Runs next state in the CPU instruction cycle:
********************************************************************************/
void control_unit_run_next_state(void)
{
   switch (state)
   {
      case CPU_STATE_FETCH:
      {
  
      }
      case CPU_STATE_DECODE:
      {        
         
      }
      case CPU_STATE_EXECUTE:
      {
       
      }
      default: /* System reset if error occurs. */
      {
         control_unit_reset();
         break;
      }
   }
   return;
}

/********************************************************************************
* control_unit_run_next_state: Runs next CPU instruction cycle, i.e. fetches
*                              a new instruction from program memory, decodes
*                              and executes it.
********************************************************************************/
void control_unit_run_next_instruction_cycle(void)
{
   do
   {
      control_unit_run_next_state();
   } while (state != CPU_STATE_EXECUTE);
   return;
}

/********************************************************************************
* control_unit_print: Prints information about the processor, for instance
*                     current subroutine, instruction, state, content in
*                     CPU-registers and I/O registers DDRB, PORTB and PINB.
********************************************************************************/
void control_unit_print(void)
{
   printf("--------------------------------------------------------------------------------\n");
   /* printf("Current subroutine:\t\t\t\t%s\n", program_memory_subroutine_name(mar)); */
   printf("Current instruction:\t\t\t\t%s\n", cpu_instruction_name(op_code));
   printf("Current state:\t\t\t\t\t%s\n", cpu_state_name(state));

   printf("Program counter:\t\t\t\t%hu\n", pc);

   printf("Instruction register:\t\t\t\t%s ", get_binary((ir >> 16) & 0xFF, 8));
   printf("%s ", get_binary((ir >> 8) & 0xFF, 8));
   printf("%s\n", get_binary(ir & 0xFF, 8));

   printf("Status register (ISNZVC):\t\t\t%s\n\n", get_binary(sr, 6));

   printf("Content in CPU register R16:\t\t\t%s\n", get_binary(reg[R16], 8));
   printf("Content in CPU register R24:\t\t\t%s\n\n", get_binary(reg[R24], 8));

   printf("Content in data direction register DDRB:\t%s\n", get_binary(data_memory[DDRB], 8));
   printf("Content in data register PORTB:\t\t\t%s\n", get_binary(data_memory[PORTB], 8));
   printf("Content in pin input register PINB:\t\t%s\n", get_binary(data_memory[PINB], 8));

   printf("--------------------------------------------------------------------------------\n\n");
   return;
}


