/*
    Hackssembler
    started on 18/10/21
    
    "why does my back hurt?" - Cinders21

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// opcodes for destination
unordered_map<string, int> destOpCodes = {
    {""   , 0b000},
    {"M"  , 0b001},
    {"D"  , 0b010},
    {"MD" , 0b011},
    {"A"  , 0b100},
    {"AM" , 0b101},
    {"AD" , 0b110},
    {"AMD", 0b111},
};
// Opcodes for registers
unordered_map<string, int> RegOpCodes = {
    {"R0"    , 0b000},
    {"R1"    , 0b001},
    {"R2"    , 0b010},
    {"R3"    , 0b011},
    {"R4"    , 0b100},
    {"R5"    , 0b101},
    {"R6"    , 0b110},
    {"R7"    , 0b111},
    {"R8"    , 0b1000},
    {"R9"    , 0b1001},
    {"R10"   , 0b1010},
    {"R11"   , 0b1011},
    {"R12"   , 0b1100},
    {"R13"   , 0b1101},
    {"R14"   , 0b1110},
    {"R15"   , 0b1111},
    {"SCREEN", 0b11111110110000},
    {"KBD"   , 0b110000000000000}
};

// opcodes for jump instructions
unordered_map<string, int> jumpOpCodes = {
    {""   , 0b000},
    {"JGT", 0b001},
    {"JEQ", 0b010},
    {"JGE", 0b011},
    {"JLT", 0b100},
    {"JNE", 0b101},
    {"JLE", 0b110},
    {"JMP", 0b111},
};

// opcodes for arithmetic instructions
unordered_map<string, int> compOpCodes = {
    {"0"  , 0b101010},
    {"1"  , 0b111111},
    {"-1" , 0b111010},
    {"D"  , 0b001100},
    {"A"  , 0b110000},
    {"M"  , 0b110000},
    {"!D" , 0b001111},
    {"!A" , 0b110001},
    {"!M" , 0b110001},
    {"-D" , 0b001111},
    {"-A" , 0b110011},
    {"-M" , 0b110011},
    {"D+1", 0b011111},
    {"A+1", 0b110111},
    {"M+1", 0b110111},
    {"D-1", 0b001110},
    {"A-1", 0b110010},
    {"M-1", 0b110010},
    {"D+A", 0b000010},
    {"D+M", 0b000010},
    {"D-A", 0b010011},
    {"D-M", 0b010011},
    {"A-D", 0b000111},
    {"M-D", 0b000111},
    {"D&A", 0b000000},
    {"D&M", 0b000000},
    {"D|A", 0b010101},
    {"D|M", 0b010101},
};

int main(int argc, char * argv[])
{
    // No file attached
    if (argc < 2)
    {
        cout << "Usage: assemble <filename>" << std::endl;
        return -1;
    }
    
    vector<string> program; // Vector to store the program
    ifstream infile(argv[1]);
    string line; 
    unordered_map<string, int> variables;
    while(getline(infile, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            line.erase(remove(line.begin(), line.end(), ' '), line.end()); // remove whitespaces
            if (line[i] == '/' && line[i + 1] == '/' ) // remove comments
            {
                line.erase(i, line.size());
                break;
            }
            if (line[i] == '@') // store variables
            {
                string var = line.substr(i + 1, line.size());
                variables[var] = 0;
            }
        }
        if (line != "")
        {
            program.push_back(line);
        }
    }
    infile.close();

    for(int i = 0; i < program.size(); i++)
    {
        cout<<i << ": " << program[i] << endl;
    }
    return 0;
}