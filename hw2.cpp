/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::ofstream;
using std::ios;
using std::string;
using std::endl;

ofstream OutFile;

// The running count of instructions is kept here
// make it static to help the compiler optimize docount
static UINT64 memcount=0;
static UINT64 total=0;
static UINT64 branchcount = 0;
static UINT64 c= 0;
static UINT64 c2 = 0;
static UINT64 c3 = 0;
static UINT64 c4 = 0;
static UINT64 c5= 0;
static UINT64 c6 = 0;
static UINT64 c7 = 0;
static UINT64 c8 = 0;
static UINT64 c9= 0;
static UINT64 c10 = 0;
static UINT64 c11 = 0;
static UINT64 c12 = 0;
static UINT64 c13= 0;
static UINT64 c14 = 0;
static UINT64 c15 = 0;
static UINT64 c16 = 0;


// This function is called before every instruction is executed
VOID dobranchcount() { branchcount++; }
VOID domemcount() { memcount++; }
VOID dototalcount() { total++; }
    
// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{

INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)dototalcount, IARG_END);
UINT32 memOperands = INS_MemoryOperandCount(ins);
    // Iterate over each memory operand of the instruction.
if (INS_RegWContain(ins,REG_RAX)) {
    c++;
}
if (INS_RegWContain(ins,REG_RBX)) {
    c2++;
}

if (INS_RegWContain(ins,REG_RCX)) {
    c3++;
}
if (INS_RegWContain(ins,REG_RDX)) {
    c4++;
}
if (INS_RegWContain(ins,REG_RSI)) {
    c5++;
}
if (INS_RegWContain(ins,REG_RDI)) {
    c6++;
}
if (INS_RegWContain(ins,REG_RSP)) {
    c7++;
}
if (INS_RegWContain(ins,REG_RBP)) {
    c8++;
}
if (INS_RegWContain(ins,REG_R8)) {
    c9++;
}
if (INS_RegWContain(ins,REG_R9)) {
    c10++;
}
if (INS_RegWContain(ins,REG_R10)) {
    c11++;
}
if (INS_RegWContain(ins,REG_R11)) {
    c12++;
}
if (INS_RegWContain(ins,REG_R12)) {
    c13++;
}
if (INS_RegWContain(ins,REG_R13)) {
    c14++;
}
if (INS_RegWContain(ins,REG_R14)) {
    c15++;
}
if (INS_RegWContain(ins,REG_R15)) {
    c16++;
}

if (INS_IsBranch(ins)) {
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)dobranchcount, IARG_END);
}
  for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {
   
 if (INS_MemoryOperandIsWritten(ins,memOp) || INS_MemoryOperandIsRead(ins,memOp)) {
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)domemcount, IARG_END);
}

  
}
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "output.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);
  OutFile << "Total Count (Task1) " << total << endl;
OutFile << "Task2 " <<   endl;
    OutFile << "Branch Count: " << branchcount << endl;
    OutFile << "Memory Count: " << memcount << endl;
  OutFile << "Arithmetic Count: " << total-(branchcount+memcount) << endl;
OutFile << "Task3 " <<   endl;
OutFile << "Freqquency Of RAX " << c << endl;
OutFile << "Freqquency Of RBX " << c2 << endl;
OutFile << "Freqquency Of RCX " << c3<< endl;
OutFile << "Freqquency Of RDX " << c4 << endl;
OutFile << "Freqquency Of RSI " << c5 << endl;
OutFile << "Freqquency Of RDI " << c6 << endl;
OutFile << "Freqquency Of RSP " << c7 << endl;
OutFile << "Freqquency Of RBP " << c8 << endl;
OutFile << "Freqquency Of R8 " << c9 << endl;
OutFile << "Freqquency Of R9 " << c10 << endl;
OutFile << "Freqquency Of R10 " << c11 << endl;
OutFile << "Freqquency Of R11 " << c12 << endl;
OutFile << "Freqquency Of R12 " << c13 << endl;
OutFile << "Freqquency Of R13 " << c14 << endl;
OutFile << "Freqquency Of R14 " << c15 << endl;
OutFile << "Freqquency Of R15 " << c16 << endl;

    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
