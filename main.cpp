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
        p.parse();
        cout << "Success!";
    }
    catch(Token errorToken) {
        cout << "Failure!" << endl << "  " << errorToken.toString();
    }
    catch(const char* errorMsg) {
        cout << errorMsg;
    }

    // datalog program test case
    Predicate scheme1 = Predicate();
    scheme1.setName("snap");
    scheme1.addParameter("S");
    scheme1.addParameter("N");
    scheme1.addParameter("A");
    scheme1.addParameter("P");
    Predicate scheme2 = Predicate();
    scheme2.setName("HasSameAddress");
    scheme2.addParameter("X");
    scheme2.addParameter("Y");
    Predicate fact = Predicate();
    fact.setName("snap");
    fact.addParameter("'12345'");
    fact.addParameter("'C. Brown'");
    fact.addParameter("'12 Apple'");
    fact.addParameter("'555-1234'");
    Rule rule = Rule();
    Predicate ruleHead = Predicate();
    ruleHead.setName("HasSameAddress");
    ruleHead.addParameter("X");
    ruleHead.addParameter("Y");
    Predicate ruleBody1 = Predicate();
    ruleBody1.setName("snap");
    ruleBody1.addParameter("S");
    ruleBody1.addParameter("N");
    ruleBody1.addParameter("A");
    ruleBody1.addParameter("P");
    Predicate ruleBody2 = Predicate();
    ruleBody2.setName("snap");
    ruleBody2.addParameter("S");
    ruleBody2.addParameter("N");
    ruleBody2.addParameter("A");
    ruleBody2.addParameter("P");
    rule.setHead(ruleHead);
    rule.addPredicate(ruleBody1);
    rule.addPredicate(ruleBody2);
    Predicate query = Predicate();
    query.setName("HasSameAddress");
    query.addParameter("'Snoopy'");
    query.addParameter("Who");

    DatalogProgram program = DatalogProgram();
    program.addScheme(scheme1);
    program.addScheme(scheme2);
    program.addFact(fact);
    program.addRule(rule);
    program.addQuery(query);
    program.addDomainItem("'12 Apple'");

    cout << program.toString() << endl;


}