#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
    if(argv[1] != NULL)
    {
        std::ifstream infile(argv[1]);
        std::string line;
        while(std::getline(infile, line))
        {
                       
        }
    }
    
    return 0;
}