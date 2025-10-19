#include "filemanager.h"
#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::cin;
using std::ios;

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
    // "for every file/folder inside the path, store it in entry"
    for(const auto &entry : fs::directory_iterator(".")){
        // Gets the path -> filename -> converts to a string
            cout << entry.path().filename().string() << " ";
    }
    cout << "\n";
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