#include "decs.h"
#include <iostream>
#include <math.h>
#include <cmath>

Hardware::Hardware() {
    this->pc = 0;
    setDC(0);
    this->accumulator = 0;
    this->b = 0;
    this->zeroBit = 0;
    this->overFlowBit = 0;
    this->instructionsExecuted = 0;
    for (int i = 0; i < 128; i++) {
        this->data[i] = 0;
    }
    for (int i = 0; i < 128; i++) {
        this->tempMemory[i] = "0";
    }
}

Hardware::~Hardware(){
    for (int i = 0; i < 128; ++i) {
        if(memory[i] != nullptr){
            delete memory[i];
        }
    }
}

void Hardware::printHardware() {
    cout << "Register A: " << getAccumulator() << endl;
    cout << "Register B: " << getB() << endl;
    cout << "Zero Bit: " << getZeroBit() << endl;
    cout << "Overflow Bit: " << getOverFlowBit() << endl;

    for (auto i : address_to_val) {
        if (i.second != -88) {
            cout << "{" << i.first << ": " << i.second << "}\n";
        }
    }
}

void Declare::execute() {
    //sets the data part of the memory to 1 signifying that it is occupied
    tempZ->data[tempZ->getDC()] = 1;
    //it then adds the variable to a hash with the value of nil
    tempZ->address_to_val[argValue] = -88;
}

void LDI::execute() {
    //this loads the argtype which should be an integer into the accumulator
    tempZ->setAccumulator(stol(argValue));
}

void STR::execute() {
    //store contents of accumulator register(a) into the variable argtype which in this case is
    // stored into a hashmap value size given the key
    tempZ->address_to_val[argValue] = tempZ->getAccumulator();
}

void LDA::execute() {
    //store contents of a variable into the accumulator register
    tempZ->setAccumulator(tempZ->address_to_val[argValue]);
}

void LDB::execute() {
    //store contents of a variable into the b register
    tempZ->setB(tempZ->address_to_val[argValue]);
}

void XCH::execute() {
    //this swaps what is in register b for whats in register a
    long temp = tempZ->getAccumulator();
    tempZ->setAccumulator(tempZ->getB());
    tempZ->setB(temp);
}

void ADD::execute(){
    //this adds the contents of register a to b and the result is stored in a
    long temp = tempZ->getAccumulator();
    tempZ->setAccumulator((tempZ->getB() + temp));

    //if the sum of the two registers is equal to 0 then the zero bit is set to 1
    if(tempZ->getAccumulator() == 0){
        tempZ->setZeroBit(1);
    }
    else{
        //otherwise it is set to 0
        tempZ->setZeroBit(0);
    }

    //if the sum of the two registers which is stored in register a is not within -2^31 and (2^31)-1 then
    //the overflow bit is set to one otherwise it is set to zero
    if(tempZ->getAccumulator() < (pow(-2,31)) || tempZ->getAccumulator() > ((pow(2,31))-1)){
        tempZ->setOverFlowBit(1);
        tempZ->setAccumulator(temp);
    }
};

void JMP::execute() {
    //jump to the given instruction by setting the PROGRAM COUNTER to the argtype passed in which is an int
    tempZ->setPC(stol(argValue));
}

void JZS::execute() {
    //jump to the given instruction by setting the PROGRAM COUNTER to the argtype passed in which is an int
    //only if the zero result bit is set to 1 otherwise just go to the next instruction by incrementing the
    //PROGRAM COUNTER by 1
    if(tempZ->getZeroBit() == 1){
        tempZ->setPC(stol(argValue));
    }
    else{
        tempZ->incrementPC();
    }
}

void JVS::execute() {
    //jump to the given instruction by setting the PROGRAM COUNTER to the argtype passed in which is an int
    //only if the overflow  bit is set to 1 otherwise just go to the next instruction by incrementing the
    //PROGRAM COUNTER by 1
    if(tempZ->getOverFlowBit() == 1){
        tempZ->setPC(stol(argValue));
    }
    else{
        tempZ->incrementPC();
    }
}