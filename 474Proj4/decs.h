#ifndef UNTITLED1_DECS_H
#define UNTITLED1_DECS_H

#include <iostream>
#include <unordered_map>
using namespace std;

//abstract superclass for all the individual instructions
class Instructions{
public:

    string printString;
    string argValue;

    Instructions(){
    }

    virtual void execute() = 0;

    void print(){cout << printString << ": " << argValue << endl;}
    void setArgValue(string val){this->argValue = val;}
    string getArgValue(){return this->argValue;}
    string getPrintString(){return this->printString;}
    void setPrintString(string val){this->printString = val;}
};

//this is the class that handles all of the hardware and has getters and setters to access variables
class Hardware{

private:
    long pc;
    long dc;
    long accumulator;
    long b;
    long zeroBit;
    long overFlowBit;
    long instructionsExecuted;

public:

    unordered_map<string,long> address_to_val;
    Instructions * memory[128];
    string tempMemory[128];
    int data[128];

    Hardware();
    ~Hardware();
    void setAddressToVal(string val1, long val2){this->address_to_val[val1] = val2;}
    unordered_map<string,long> getAddressToVal(){return this->address_to_val;}
    void setPC(long val){this->pc = val;}
    void incrementPC(){this->pc++;}
    long getPC(){return this->pc;}
    void setDC(long val){this->dc = val;}
    void incrementDC(){this->dc++;}
    long getDC(){return this->dc;}
    void setAccumulator(long val){this->accumulator = val;}
    long getAccumulator(){return this->accumulator;}
    void setB(long val){this->b = val;}
    long getB(){return this->b;}
    void setZeroBit(long val){this->zeroBit = val;}
    long getZeroBit(){return this->zeroBit;}
    void setOverFlowBit(long val){this->overFlowBit = val;}
    long getOverFlowBit(){return this->overFlowBit;}
    void setInstructionExecuted(long val){this->instructionsExecuted = val;}
    void incrementInstructionsExecuted(){this->instructionsExecuted++;}
    long getInstructionExecuted(){return this->instructionsExecuted;}
    void printHardware();

};

class Declare:public Instructions{

public:
    Hardware *tempZ;
    Declare( string s,Hardware *Z) : Instructions() {argValue = s;printString = "DEC";tempZ = Z;}
    void execute();
};

class LDI:public Instructions{

public:
    Hardware *tempZ;
    LDI(string s, Hardware *Z) : Instructions() {argValue = s;printString = "LDI";tempZ = Z;}
    void execute();
};

class STR:public Instructions{

public:
    Hardware * tempZ;
    STR(string s, Hardware * Z) : Instructions() {argValue = s;printString = "STR";tempZ = Z;}
    void execute();
};

class LDA:public Instructions{
public:
    Hardware * tempZ;
    LDA(string s, Hardware * Z) : Instructions(){argValue = s;printString = "LDA";tempZ = Z;}
    void execute();
};

class LDB:public Instructions{
public:
    Hardware * tempZ;
    LDB(string s, Hardware * Z) : Instructions(){argValue = s;printString = "LDB";tempZ = Z;}
    void execute();
};

class XCH:public Instructions{
public:
    Hardware * tempZ;
    XCH(string s, Hardware * Z) : Instructions(){argValue = s;printString = "XCH";tempZ = Z;}
    void execute();
};

class ADD:public Instructions{
public:
    Hardware * tempZ;
    ADD(string s, Hardware * Z) : Instructions(){argValue = s;printString = "ADD";tempZ = Z;}
    void execute();
};

class JMP: public Instructions{
public:
    Hardware * tempZ;
    JMP(string s,Hardware * Z):Instructions(){argValue = s;printString = "JMP";tempZ = Z;}
    void execute();
};

class JZS: public Instructions{
public:
    Hardware * tempZ;
    JZS(string s,Hardware * Z):Instructions(){argValue = s;printString = "JZS";tempZ = Z;}
    void execute();
};

class JVS: public Instructions{
public:
    Hardware * tempZ;
    JVS(string s,Hardware * Z):Instructions(){argValue = s;printString = "JVS";tempZ = Z;}
    void execute();
};

class HLT: public Instructions{
public:
    Hardware * tempZ;
    HLT(Hardware * Z):Instructions(){printString = "HLT";tempZ = Z;}
    void execute(){}
};

#endif //UNTITLED1_DECS_H
