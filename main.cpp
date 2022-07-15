#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"

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

    // lexer
    Lexer lexer;
    vector<Token> tokens = lexer.run(fileContents);

    // parser
    try {
        Parser p = Parser(tokens);
        DatalogProgram program = p.parse();

        // interpreter
        Database db = Database();

        // add all the db tables
        for(Predicate s : program.getSchemes()){
            db.addRelation(s);
        }

        // add all the tuples into those tables
        for(Predicate f : program.getFacts()){
            db.addFact(f);
        }

        for(Predicate q : program.getQueries()){
            Relation* result = db.query(q);
            cout << q.toString() << "?";
            if(result->size() > 0) cout << " Yes(" << result->size() << ")" << endl;
            else cout << " No" << endl;
            cout << result->toString();
        }

        // print the schema for debug
        // cout << db.toString() << endl;
    }
    catch(Token errorToken) {
        cout << "Failure!" << endl << "  " << errorToken.toString();
    }
    catch(const char* errorMsg) {
        cout << errorMsg;
    }

}