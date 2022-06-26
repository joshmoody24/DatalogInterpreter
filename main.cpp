#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
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

    /* Lexer lexer;
    lexer.run(fileContents);
    return 0;
     */

    vector<Token> tokens = {
            Token(ID,"Ned",2),
            Token(LEFT_PAREN,"(",2),
            Token(RIGHT_PAREN,")",2),
    };
    try {
        Parser p = Parser(tokens);
        cout << p.tokenType() << endl;
        p.advanceToken();
        cout << p.tokenType() << endl;
        p.advanceToken();
        cout << p.tokenType() << endl;
        p.throwError();
    }
    catch(Token errorToken) {
        cout << errorToken.toString();
    }

}