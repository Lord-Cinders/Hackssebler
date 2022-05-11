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
using namespace std;

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
    while(getline(infile, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            line.erase(remove(line.begin(), line.end(), ' '), line.end()); // remove whitespaces
            if (line[i] == '/' && line[i + 1] == '/' ) // remove comments
            {
                line = "";
                break;
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