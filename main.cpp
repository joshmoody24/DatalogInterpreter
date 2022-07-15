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
/*
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

    */

    Tuple snap_t1;  
    snap_t1.push_back("33333");  
    snap_t1.push_back("Snoopy");  
    snap_t1.push_back("12 Apple St.");  
    snap_t1.push_back("555-1234");  
  
    Tuple snap_t2;  
    snap_t2.push_back("12345");  
    snap_t2.push_back("C. Brown");  
    snap_t2.push_back("12 Apple St.");  
    snap_t2.push_back("555-1234");  
  
    Tuple snap_t3;  
    snap_t3.push_back("22222");  
    snap_t3.push_back("P. Patty");  
    snap_t3.push_back("56 Grape Blvd");  
    snap_t3.push_back("555-9999");  
  
  
    Tuple csg_t1;  
    csg_t1.push_back("cs101");  
    csg_t1.push_back("12345");  
    csg_t1.push_back("A");  
  
    Tuple csg_t2;  
    csg_t2.push_back("cs101");  
    csg_t2.push_back("22222");  
    csg_t2.push_back("B");  
  
    Tuple csg_t3;  
    csg_t3.push_back("cs101");  
    csg_t3.push_back("33333");  
    csg_t3.push_back("C");  
  
    Tuple csg_t4;  
    csg_t4.push_back("EE200");  
    csg_t4.push_back("12345");  
    csg_t4.push_back("B+");  
  
    Tuple csg_t5;  
    csg_t5.push_back("EE200");  
    csg_t5.push_back("22222");  
    csg_t5.push_back("B");  
  
    Header h1;  
    h1.push_back("StudentID");  
    h1.push_back("Name");  
    h1.push_back("Address");  
    h1.push_back("Phone");  
  
    Header h2;  
    h2.push_back("Course");  
    h2.push_back("StudentID");  
    h2.push_back("Grade");  
  
    Relation r1;  
    r1.setName("snap");  
    r1.setHeader(h1);  
    r1.addTuple(snap_t1);  
    r1.addTuple(snap_t2);  
    r1.addTuple(snap_t3);  
  
    Relation r2;  
    r2.setName("csg");  
    r2.setHeader(h2);  
    r2.addTuple(csg_t1);  
    r2.addTuple(csg_t2);  
    r2.addTuple(csg_t3);  
    r2.addTuple(csg_t4);  
    r2.addTuple(csg_t5);  
  
    cout << r1.natJoin(&r2)->toString() << endl << endl;

}
