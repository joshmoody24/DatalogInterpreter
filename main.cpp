#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {

    if(argc != 2){
        cout << "No input file specified" << endl;
        return 1;
    }

    string fileName = argv[1];
    //cout << "reading " << fileName << endl << "-----------" << endl;

    string fileContents;
    fstream newFile;
    newFile.open(fileName,ios::in);

    if (newFile.is_open()){
        string input;
        while(getline(newFile, input)){
            fileContents += input + "\n";
        }
        newFile.close();
    }
    else {
        std::cout << "An error occurred while opening the file" << endl;
        return 1;
    }

    // cout << fileContents << endl;

    Lexer lexer;
    lexer.run(fileContents);
    return 0;
}