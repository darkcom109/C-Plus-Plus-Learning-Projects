#include <iostream>
#include <string>

// File streams act as a pipe where data can flow
// Input stream = data flows into your program
// Output stream = data flows out of your program
// cin = input stream from keyboard
// cout = output stream to console
// ifstream/ofstream/fstream = for files
// ofstream = is the output file stream, used only for writing to files
#include <fstream>

// To seperate a string into an array
#include <sstream>

using std::cout;
using std::cin;
using std::ofstream;
using std::stringstream;
using std::string;
using std::ios;

// Three arguments in the string
// {action} {filename} {input}
void parseInput(const string & input) {
    ofstream writer;
    stringstream stringParser(input);
    string word;
    string arr[3];
    int i = 0;

    string action;
    string filename;
    string content;
    
    while(stringParser >> word && i < 2){
        arr[i++] = word;
    }

    action = arr[0];
    filename = arr[1];

    cout << "Input$ ";
    getline(cin, content);

    // -o == overwrite
    if(action == "-o") {
        writer.open(filename);
        writer << content;
    }
    // -a == append
    else if(action == "-a"){
        writer.open(filename, ios::app);
        writer << content;
    }

    writer.close();
}
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

        if(input == "exit"){
            isOperational = false;
            break;
        }
        else if(input == "help"){
            cout << "---------------HELP---------------\n";
            cout << "----------------------------------\n";
            cout << "{filename}";
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