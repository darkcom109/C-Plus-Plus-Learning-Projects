#pragma once // Avoids code from being copied before compilation
#include <string>

using std::string;

// Function declarations (abstract)
bool validFile(const string &filename);
void deleteFile(const string &filename);
void listFiles();
void readFile(const string &filename);
void parseInput(const string &input);