#include <iostream>
#include <string>
#include <vector>

// Listing files
#include <filesystem>

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
using std::ifstream;
using std::stringstream;
using std::string;
using std::ios;
using std::vector;

// Shortcut/namespace
namespace fs = std::filesystem;

bool validFile(const string & filename){
    vector<string> restrictedFiles = {"filemanager.cpp", "filemanager.exe"};
    for(int i = 0 ; i < restrictedFiles.size() ; i++) {
        if(filename == restrictedFiles[i]) return false;
    }
    return true;
}

void deleteFile(const string & filename){
    if(fs::exists(filename) && validFile(filename)){
        
        fs::remove(filename);
        cout << "File: '" << filename << "' deleted successfully\n"; 
    }
    else{
        cout << "File Deletion was not Successful\n";
    }
}
void listFiles(){ 
    cout << "--------- CURRENT FILES ----------\n";
    cout << "----------------------------------\n";
    // "for every file/folder inside the path, store it in entry"
    for(const auto &entry : fs::directory_iterator(".")){
        // Gets the path -> filename -> converts to a string
            cout << entry.path().filename().string() << "\n";
    }
}

void readFile(const string & filename){
    ifstream reader;
    reader.open(filename);
    string line;
    cout << "Contents$: ";

    while(getline(reader, line)){
        cout << line << " ";
    }
    cout << "\n";
    reader.close();
}
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

    if(action == "del") {
        deleteFile(filename);
        return;
    }

    readFile(filename);

    cout << "Input$: ";
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
        
        if(input.empty()) continue;
        else if(input == "exit"){
            isOperational = false;
            break;
        }
        else if(input == "-l"){
            listFiles();
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