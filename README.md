# Instruction-Counter
In this project, ınstruction numbers from a c program are counted with pin and c++. 


The Output:




Total Count (Task1) 721299

Task2

Branch Count: 68083

Memory Count: 340091

Arithmetic Count: 313125

Task3

Freqquency Of RAX 1498

Freqquency Of RBX 388

Freqquency Of RCX 477

Freqquency Of RDX 713

Freqquency Of RSI 556

Freqquency Of RDI 681

Freqquency Of RSP 2403

Freqquency Of RBP 308

Freqquency Of R8 156

Freqquency Of R9 115

Freqquency Of R10 162

Freqquency Of R11 70

Freqquency Of R12 235

Freqquency Of R13 188

Freqquency Of R14 188

Freqquency Of R15 153




General Explanation:




Firstly, I downloaded matmul.c, matmul.h and matmul.sh files from the link. After that I downloaded the pin that a binary instrumentation tool. I customized some settings for pin with the following lines:




set env INTEL_JIT_PROFILER32 <The Pin kit full path>/ia32/bin/libpinjitprofiling.so

set env INTEL_JIT_PROFILER64 <The Pin kit full path>/intel64/bin/libpinjitprofiling.so

make all TARGET=intel64

Then, I opened new folder in pin/source/tools folder and run the c code in this folder. Also I put my cpp codes for pin instrumentation in this folder. After I run the matmul code , I used the output file to count instructions.




TASK -1:




In task 1, the total number of instructions were wanted. Therefore, I used a manual example from pin files which is inscount0.cpp. I used to following methods to calculate total numbers of instructions.







VOID dototalcount() { total++; }

This method just changing the number of total variable.

INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)dototalcount, IARG_END);

This method calls instructions and dototalcount method.




Also, PIN is a CISC architecture but it tries to use advantages of RISC architecture.

TASK-2:

In this task, the number of instructions wanted according to their types. I just used if conditions to find memory and branch instructions like following lines:




if (INS_IsBranch(ins)) {

INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)dobranchcount, IARG_END);

}




for (UINT32 memOp = 0; memOp < memOperands; memOp++)

{




if (INS_MemoryOperandIsWritten(ins,memOp) || INS_MemoryOperandIsRead(ins,memOp)) {

INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)domemcount, IARG_END);

}







}




However, in the memory instructions I checked if an instruction is written to memory or read from memory. If it is one of them I changed counter by 1.

Also, to calculate the arithmetic instructions I used this formula:




total-(branchcount+memcount)




TASK-3:




In this task the frequencies of usage of register in pin were asked. I just used again if conditions to calculate this for each register with different counters(c,c1,c2,c3,…….).




if (INS_RegWContain(ins,REG_RBX)) {

c2++;

}


