#include <iostream>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>
#include "decs.h"
using namespace std;

int main() {
    //instantiate hardware class to call default constructor
    //declare variables as well
    Hardware *z = new Hardware();
    string filename;
    string sourceCode;
    string wantToContinue;
    char command;
    string instruction;
    string seperatedInstruction[2];
    //print string and get desired file name from user
    cout << "Enter a file name in the current directory." << endl;
    cin >> filename;
    int counter = 0;

    //read from filename given line by line and execute while statements for each line
    ifstream infile(filename);
    while(getline(infile,sourceCode)){
        z->tempMemory[counter] = sourceCode;
        counter++;
    }
    infile.close();

    //first we get all the instructions out of the file into a string array which we will now use to convert
    //to the actual memory which is an array of type instructions pointers

    int w = 0;
    while(z->tempMemory[w] != "0"){

        instruction = z->tempMemory[w];
        int p = 0;
        //break string up into an array to separate instruction name and instruction value
        stringstream ssin(instruction);
        while (ssin.good() && p < 2){
            ssin >> seperatedInstruction[p];
            ++p;
        }

        if(seperatedInstruction[0] == "DEC"){
            Declare * a = new Declare(seperatedInstruction[1], z);
            z->memory[w] = a;
            z->memory[w]->setPrintString("DEC");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "LDI"){
            LDI * b = new LDI(seperatedInstruction[1], z);
            z->memory[w] = b;
            z->memory[w]->setPrintString("LDI");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "STR"){
            STR * c = new STR(seperatedInstruction[1], z);
            z->memory[w] = c;
            z->memory[w]->setPrintString("STR");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "LDA"){
            LDA * d = new LDA(seperatedInstruction[1], z);
            z->memory[w] = d;
            z->memory[w]->setPrintString("LDA");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "LDB"){
            LDB * e = new LDB(seperatedInstruction[1], z);
            z->memory[w] = e;
            z->memory[w]->setPrintString("LDB");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "XCH"){
            XCH * f = new XCH(seperatedInstruction[1], z);
            z->memory[w] = f;
            z->memory[w]->setPrintString("XCH");
        }
        else if(seperatedInstruction[0] == "ADD"){
            ADD * g = new ADD(seperatedInstruction[1], z);
            z->memory[w] = g;
            z->memory[w]->setPrintString("ADD");
        }
        else if(seperatedInstruction[0] == "JMP"){
            JMP * h = new JMP(seperatedInstruction[1], z);
            z->memory[w] = h;
            z->memory[w]->setPrintString("JMP");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "JVS"){
            JVS * i = new JVS(seperatedInstruction[1], z);
            z->memory[w] = i;
            z->memory[w]->setPrintString("JVS");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "JZS"){
            JZS * j = new JZS(seperatedInstruction[1], z);
            z->memory[w] = j;
            z->memory[w]->setPrintString("JZS");
            z->memory[w]->setArgValue(seperatedInstruction[1]);
        }
        else if(seperatedInstruction[0] == "HLT"){
            HLT * k = new HLT(z);
            z->memory[w] = k;
            z->memory[w]->setPrintString("HLT");
        }

        w++;
    }

    //loop will run indefinitely until eof or halted by program instruction
    while(true){

        //if 1000 insturctions ask user if they want to continue or not
        if(z->getInstructionExecuted() == 1000) {
            cout << "1000 instruction have been executed would you like to continue? Answer Yes or No" << endl;
            cin >> wantToContinue;
        }

        if( wantToContinue == "No"){
            exit(1);
        }

        cout << "Enter command a, s, or q" << endl;
        cin >> command;

        //get desired command from user and execute it in switch statement
        switch (command) {
            case 'a':{
                //because of while loop use a bool that only prints out instructions once
                //after one run it is set to false
                bool once = true;

                //while there is an instruction and there are less than the 128 instructions possible continue loop
                while(z->memory[z->getPC()]->printString != "0" && z->getPC() < 128){

                    if(z->getInstructionExecuted() == 1000) {
                        cout << "1000 instruction have been executed would you like to continue? Answer Yes or No" << endl;
                        cin >> wantToContinue;
                    }

                    if( wantToContinue == "No"){
                        exit(1);
                    }

                    //if there are none print out data and registers and bits and exit
                    if(z->memory[z->getPC()]->printString == "0"){
                        cout << "Register A: " << z->getAccumulator() << endl;
                        cout << "Register B: " << z->getB() << endl;
                        cout << "Zero Bit: " << z->getZeroBit() << endl;
                        cout << "Overflow Bit: " << z->getOverFlowBit() << endl;

                        for (auto i : z->address_to_val) {
                                cout << "{" << i.first << ": " << i.second << "}\n";
                        }
                        //}
                        exit(8);
                    }


                    //each instruction in if statements that execute its corresponding subclass
                    if(z->memory[z->getPC()]->printString == "DEC"){

                        z->incrementInstructionsExecuted();
                        //execute the instance of the class
                        z->memory[z->getPC()]->execute();
                        //increment program counter
                        z->incrementPC();
                        z->incrementDC();
                    }
                    else if(z->memory[z->getPC()]->printString == "LDI"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                        z->incrementPC();
                    }
                    else if(z->memory[z->getPC()]->printString == "STR"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                        z->incrementPC();
                    }
                    else if(z->memory[z->getPC()]->printString == "LDA"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                        z->incrementPC();
                    }
                    else if(z->memory[z->getPC()]->printString == "LDB"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                        z->incrementPC();
                    }
                    else if(z->memory[z->getPC()]->printString == "XCH"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                        z->incrementPC();
                    }
                    else if(z->memory[z->getPC()]->printString == "ADD"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                        z->incrementPC();
                    }
                    else if(z->memory[z->getPC()]->printString == "JMP"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                    }
                    else if(z->memory[z->getPC()]->printString == "JZS"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                    }
                    else if(z->memory[z->getPC()]->printString == "JVS"){
                        z->incrementInstructionsExecuted();
                        //send through the instruction value to use it in the function
                        z->memory[z->getPC()]->execute();
                    }
                    else if(z->memory[z->getPC()]->printString == "HLT"){
                        HLT * k = new HLT(z);
                        z->incrementInstructionsExecuted();
                        z->memory[z->getPC()]->execute();
                        cout << "Register A: " << z->getAccumulator() << endl;
                        cout << "Register B: " << z->getB() << endl;
                        cout << "Zero Bit: " << z->getZeroBit() << endl;
                        cout << "Overflow Bit: " << z->getOverFlowBit() << endl;

                        for (auto i : z->address_to_val) {
                                cout << "{" << i.first << ": " << i.second << "}\n";
                        }


                        exit(9);
                    }
                }

                break;
            }
            case 's':{

                if(z->memory[z->getPC()]->printString == "0"){
                    cout << "Register A: " << z->getAccumulator() << endl;
                    cout << "Register B: " << z->getB() << endl;
                    cout << "Zero Bit: " << z->getZeroBit() << endl;
                    cout << "Overflow Bit: " << z->getOverFlowBit() << endl;

                    //prints out everything that has been initialized in the unordered set hash type thing
                    for (auto i : z->address_to_val) {
                        if (i.second != (-88)) {
                            cout << i.second << endl;
                            cout << "{" << i.first << ": " << i.second << "}\n";
                        }
                    }

                    exit(8);
                }

                if(z->memory[z->getPC()]->printString == "DEC"){

                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->incrementDC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "LDI"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "STR"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "LDA"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "LDB"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "XCH"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "ADD"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->incrementPC();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "JMP"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "JZS"){
                    z->memory[z->getPC()]->execute();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "JVS"){
                    z->incrementInstructionsExecuted();
                    //send through the instruction value to use it in the function
                    z->memory[z->getPC()]->execute();
                    z->printHardware();
                }
                else if(z->memory[z->getPC()]->printString == "HLT"){
                    HLT * k = new HLT(z);
                    z->memory[z->getPC()]->execute();
                    z->incrementInstructionsExecuted();
                    cout << "Register A: " << z->getAccumulator() << endl;
                    cout << "Register B: " << z->getB() << endl;
                    cout << "Zero Bit: " << z->getZeroBit() << endl;
                    cout << "Overflow Bit: " << z->getOverFlowBit() << endl;

                    for (auto i : z->address_to_val) {
                        if (i.second != -88) {
                            cout << "{" << i.first << ": " << i.second << "}\n";
                        }
                    }


                    exit(11);
                }

                break;
            }
            case 'q':{
                exit(3);
            }
            default:
                assert(0);
        }

    }

    return 0;
}
