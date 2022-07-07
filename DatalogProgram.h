//
// Created by joshm on 7/6/2022.
//

#ifndef LAB1_DATALOGPROGRAM_H
#define LAB1_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <set>
#include <vector>
#include <iostream>
using namespace std;

class DatalogProgram{
public:
    DatalogProgram(){};
    void addFact(Predicate p){
        facts.push_back(p);
    }
    void addScheme(Predicate p){
        schemes.push_back(p);
    }
    void addRule(Rule r){
        rules.push_back(r);
    }
    void addQuery(Predicate p){
        queries.push_back(p);
    }
    void addDomainItem(string s){
        domain.insert(s);
    }
    string toString(){
        stringstream out;
        out << "Schemes(" << schemes.size() << "):\n";
        for(Predicate s : schemes) {
            out << "  " << s.toString() << "\n";
        }
        out << "Facts(" << facts.size() << "):\n";
        for(Predicate f : facts){
            out << "  " << f.toString() << "." << "\n";
        }
        out << "Rules(" << rules.size() << "):\n";
        for(Rule r : rules){
            out << "  " << r.toString() << ".\n";
        }
        out << "Queries(" << queries.size() << "):\n";
        for(Predicate q : queries){
            out << "  " << q.toString() << "?\n";
        }
        out << "Domain(" << domain.size() << "):\n";
        for(string d : domain){
            out << "  " << d << "\n";
        }
        return out.str();
    }
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;
};

#endif //LAB1_DATALOGPROGRAM_H
