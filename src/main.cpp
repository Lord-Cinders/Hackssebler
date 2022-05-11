/*
    Hackssembler
    started on 18/10/21
    Finished on 12/05/22
    "why does my back hurt?" - Cinders21
    "maybe because you kept procrastinating for 7 months"(you deserve it) - Cinders22 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>

using namespace std;

// utility functions
void printProgram(vector<string> program)
{
    for(int i = 0; i < program.size(); i++)
    {
        cout<<i << " " << program[i] << endl;
    }
}

void printVariables(unordered_map<string, string> var)
{
    for(auto i: var)
    {
        cout<< i.first << " " << i.second << endl;
    }
}

bool isDigits(const string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

// opcodes for destination
unordered_map<string, string> destOpCodes = {
    {""   , "000"},
    {"M"  , "001"},
    {"D"  , "010"},
    {"MD" , "011"},
    {"A"  , "100"},
    {"AM" , "101"},
    {"AD" , "110"},
    {"AMD", "111"},
};
// Opcodes for registers
unordered_map<string, string> regOpCodes = {
    {"R0"    , "0"},
    {"SP"    , "0"},
    {"R1"    , "1"},
    {"LCL"   , "1"},
    {"R2"    , "2"},
    {"ARG"   , "2"},
    {"R3"    , "3"},
    {"THIS"  , "3"},
    {"R4"    , "4"},
    {"THAT"  , "4"},
    {"R5"    , "5"},
    {"R6"    , "6"},
    {"R7"    , "7"},
    {"R8"    , "8"},
    {"R9"    , "9"},
    {"R10"   , "10"},
    {"R11"   , "11"},
    {"R12"   , "12"},
    {"R13"   , "13"},
    {"R14"   , "14"},
    {"R15"   , "15"},
    {"SCREEN", "16384"},
    {"KBD"   , "24576"}
};

// opcodes for jump instructions
unordered_map<string, string> jumpOpCodes = {
    {""   , "000"},
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"},
};

// opcodes for arithmetic instructions
unordered_map<string, string> compOpCodes = {
    {"0"  , "101010"},
    {"1"  , "111111"},
    {"-1" , "111010"},
    {"D"  , "001100"},
    {"A"  , "110000"},
    {"M"  , "110000"},
    {"!D" , "001111"},
    {"!A" , "110001"},
    {"!M" , "110001"},
    {"-D" , "001111"},
    {"-A" , "110011"},
    {"-M" , "110011"},
    {"D+1", "011111"},
    {"A+1", "110111"},
    {"M+1", "110111"},
    {"D-1", "001110"},
    {"A-1", "110010"},
    {"M-1", "110010"},
    {"D+A", "000010"},
    {"D+M", "000010"},
    {"A+D", "000010"},
    {"M+D", "000010"},
    {"D-A", "010011"},
    {"D-M", "010011"},
    {"A-D", "000111"},
    {"M-D", "000111"},
    {"D&A", "000000"},
    {"D&M", "000000"},
    {"D|A", "010101"},
    {"D|M", "010101"},
};

int main(int argc, char * argv[])
{
    // No file attached
    if (argc < 2)
    {
        cout << "Usage: assemble <filename>" << std::endl;
        return -1;
    }
    
    
    ifstream infile(argv[1]);
    string line; 
    vector<string> program; // Vector to store the program
    unordered_map<string, string> variables; // hash map to store variables with its corresponsing register address
    vector<string> orderofvar; //keeps track of the order of the variables
    int lineNo = 0;
    while(getline(infile, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            // remove whitespaces
            line.erase(remove(line.begin(), line.end(), ' '), line.end()); 

            // remove comments
            size_t compos = line.find("//");
            if (compos != string::npos)
            {  
                line.erase(compos); 
            }

            //store variables
            if (line[i] == '@') 
            {
                string var = line.substr(i + 1, line.size());
                if(isDigits(line.substr(1, line.size())))
                {
                    break;
                }
                if(regOpCodes.find(var) != regOpCodes.end())
                {
                    variables[var] = regOpCodes[var];
                    line.replace(line.begin() + 1, line.end(), variables[var]);
                }
                else
                {
                    if(variables.find(var) == variables.end())
                    {
                        orderofvar.insert(orderofvar.end(), var);
                        variables[var] = "0";
                    }
                }
                break;
            }
            // store labels
            else if (line[i] == '(') 
            {
                string label = line.substr(i + 1, line.size() - 1);
                int pos = label.find(')');
                label.erase(pos);
                variables[label] = to_string(lineNo);
                line = "";
                break;
            }
        }
        if (line != "")
        {
            program.push_back(line);
            lineNo++;
        }
        
    }
    infile.close();

    // assign registers to predefined and user defined symbols
    int extReg = 16;
    for (auto i: orderofvar)
    {
        if(variables[i] == "0" )
        {
            variables[i] = to_string(extReg);
            extReg++;
            if(extReg > 264576) { break; } 
        }
    }
    
    for(int i = 0; i < program.size(); i++)
    {
        // A - Instruction: @value = 0binary(value) (16)
        if(program[i][0] == '@')
        {
            //cout<<program[i]<< ": ";
            string var = program[i].substr(1, program[i].size());
            string opcode = "0";
            if(isDigits(var)) { opcode += bitset<15> (stoi(var)).to_string(); }
            else { opcode += bitset<15> (stoi(variables[var])).to_string(); }
            //cout<<opcode<<endl;
            program[i].replace(program[i].begin(), program[i].end(), opcode);
            //cout<<program[i]<<endl;
            continue;
        }
        //cout<<program[i]<<": ";
        // C - Instruction : dest = comp ; jmp - 1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3
        size_t semiPos  = program[i].find(';');
        size_t equalPos = program[i].find('=');
        string destcode = "";
        string compinst = "";
        string jmpinst  = "";
        string opcode = "111";
        string a = "0";

        // instruction if of type dest = comp
        if(semiPos == string::npos) { 
            destcode = destOpCodes[program[i].substr(0, equalPos)];
            compinst = program[i].substr(equalPos + 1, program[i].size());
            if(compinst.find("M") != string::npos) { a = "1"; }
            compinst = compOpCodes[compinst];
            jmpinst = jumpOpCodes[jmpinst];
            opcode += a + compinst + destcode + jmpinst;
            program[i].replace(program[i].begin(), program[i].end(), opcode);
        }
        // instruction if of type comp ; jmp
        else if(equalPos == string::npos)
        {
            destcode = destOpCodes[destcode];
            compinst = program[i].substr(0, semiPos);
            if(compinst.find("M") != string::npos) { a = "1"; }
            compinst = compOpCodes[compinst];
            jmpinst = jumpOpCodes[program[i].substr(semiPos + 1, program[i].size())];
            opcode += a + compinst + destcode + jmpinst;
            program[i].replace(program[i].begin(), program[i].end(), opcode);
        }
        // instruction if of type dest = comp ; jmp
        else
        {
            destcode = destOpCodes[program[i].substr(0, equalPos)];
            compinst = program[i].substr(equalPos + 1, semiPos);
            if(compinst.find("M") != string::npos) { a = "1"; }
            compinst = compOpCodes[compinst];
            jmpinst = jumpOpCodes[program[i].substr(semiPos + 1, program[i].size())];
            opcode += a + compinst + destcode + jmpinst;
            program[i].replace(program[i].begin(), program[i].end(), opcode);
        }
        //cout<<program[i] << endl;
    }

    // write to file
    string filename = "";
    for(int i = 0; argv[1][i] != '\0'; i++)
    {
        if(argv[1][i] == '.') { break; }
        filename += argv[1][i];
    }
    filename += ".hack";
    ofstream outfile;
    outfile.open(filename);
    for(int i = 0; i < program.size(); i++)
    {
        outfile << program[i]<<endl;
    }
    return 0;
}