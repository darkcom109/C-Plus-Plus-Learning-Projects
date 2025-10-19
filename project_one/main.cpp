#include "filemanager.h"
#include <iostream>

using std::cout;
using std::getline;
using std::cin;

// File manager
int main(){
    // If the file does not exist, it is created
    // If it does, it overwrites it by default
    // Always check if it is_open() before using it

    bool isOperational = true;

    cout << "---------- FILE MANAGER ----------\n";
    cout << "----------------------------------\n";
    while(isOperational){
        string input;
        cout << "User$:";
        getline(cin, input);
        
        if(input.empty()) continue;
        else if(input == "exit"){
            isOperational = false;
            break;
        }
        else if(input == "-l"){
            listFiles();
            continue;
        }
        else if(input.substr(0, 4) == "echo"){
            cout << input.substr(5) << "\n";
            continue;
        }

        try{
            parseInput(input);
        }
        catch(...){
            cout << "Input was unsuccessful";
        }
    }
    cout << "Exited Successfully";
    return 0;
}