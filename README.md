# ObjectOrientedCPP-
This is an assembly language interpreter for a simple assembly language shown in the following image.
<img width="846" alt="Screen Shot 2022-12-22 at 4 22 49 PM" src="https://user-images.githubusercontent.com/61337965/209235792-b11282e1-9d07-49bd-a435-bed71bbac8f7.png">

This virtual emulated machine has a memory, which stores both the Simple Assembly Language program’s source code and the data that the program uses such as variables, an accumulator register, an additional register, and a Program Counter, which keeps track of the next instruction to be executed. Your ALI can again execute SAL programs one line at a time in a sort of debug mode or all at once until either a halt instruction is encountered or the last line of source code is reached.

The computer hardware that ALI emulates uses 32-bit words and consists of the following components:
    1. Memory. A 32-bit, word-addressable memory (RAM) for data and source code, holding 256 32-bit words. Words are addressed by their location,   starting from location 0 all the way up to location 255. Locations 0 through 127 hold program source code (i.e., a sequence of SAL instructions). Locations 128 through 255 hold program data.
    2. Accumulator. A 32-bit register. It is also known as Register A.
    3. Additional register. A 32-bit register also known as Register B.
    4. Program counter (PC). An 8-bit program counter (PC). The PC holds the address (number in program memory) of the next instruction to be executed. Before the program starts execution, the PC holds the value 0. It is subsequently updated as each instruction is executed. Legal values for this register are unsigned integers from 0 to 127.
    5. A zero-result bit. This bit is set if the last ADD instruction produced a zero result. This bit is cleared if the last ADD instruction produced a result different from zero. The initial value is zero. The bit is changed only after ADD instructions are executed.
    6. An overflow bit. This bit is set whenever an ADD instruction produces an overflow (−2^31 → 2^31 − 1). It is cleared if the ADD instruction did not produce an overflow. The initial value is zero.

The command loop consists of the following three commands:
    s– Execute a single line of code, starting from the instruction at memory address 0; update the PC, the registers and memory according to the instruction; and print the value of the registers, the zero bit, the overflow bit, and only the memory locations that store source code or program data after the line is executed.
    a– Execute all the instructions from the current PC value until a halt instruction is encountered or no more instructions to be executed exist. The program’s source code and data used by the program are printed.
    q– Quit the command loop.
    
USES: Abstract superclass called "Instruction" with a pure virtual function called "execute". The instructions such as DEC, LDA, or ADD are subclasses with a unique implementation of the execute function. Also uses a "Hardware" class to hold the value of the registers, status bits and memory.

USE fib.txt as the input.
