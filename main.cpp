#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DatalogProgram.h"

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
    vector<Token> tokens = lexer.run(fileContents);

    try {
        Parser p = Parser(tokens);
        DatalogProgram program = p.parse();
        cout << "Success!" << endl;
        cout << program.toString();
    }
    catch(Token errorToken) {
        cout << "Failure!" << endl << "  " << errorToken.toString();
    }
    catch(const char* errorMsg) {
        cout << errorMsg;
    }
}