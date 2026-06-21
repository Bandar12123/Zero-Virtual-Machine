ZVM (Z Virtual Machine)

A lightweight 8-bit Virtual Machine (VM) written in C that simulates a simple CPU architecture. It features its own registers, memory segmentation, a program stack, and supports 32 custom assembly instructions ranging from arithmetic and logic operations to conditional branching and function calls.
 Architecture & Features

    Registers: Built with 4 general-purpose registers (R0, R1, R2, R3).

    Control Flow: Utilizes a FLAGS register to handle comparisons and conditional jumps (JE, JNE, JG, JL, etc.).

    Stack & Subroutines: Full stack support (PUSH, POP) along with function calling mechanics (CALL, RET).

    Memory Management: Direct reading and writing capabilities to the default data segment.

    Exception System: Built-in runtime protection that catches errors during the Fetch-Decode-Execute pipeline (e.g., division by zero, stack overflow/underflow).

 Project Structure

The source code is divided into modular files for easy maintenance:

    zvm.c / zvm.h: Main execution loop, VM state initialization, and the Fetch-Decode-Execute cycle.

    zvm_instruction.c / zvm_instruction.h: Core instruction set handlers (32 instructions) and metadata array mapping.

    zvm_exception.c / zvm_exception.h: Exception definitions and handlers.

    zvm_program.h: Defines memory block constraints (Code, Data, and Stack segment sizes).

 Compilation & Execution

You can compile all the source modules and run the virtual machine using a single terminal command:
Bash

gcc zvm.c zvm_instruction.c zvm_exception.c -o zvm_vm && ./zvm_vm
