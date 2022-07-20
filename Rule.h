//
// Created by joshm on 7/6/2022.
//

#ifndef LAB1_RULE_H
#define LAB1_RULE_H

#include <vector>
#include "Predicate.h"
#include <sstream>
class Rule{
public:
    Rule(){};
    void setHead(Predicate _head){
        head = _head;
    }
    void addPredicate(Predicate p){
        body.push_back(p);
    }
    string toString(){
        string sep = "";
        stringstream out;
        out << head.toString() << " :- ";
        for(Predicate p : body){
            out << sep << p.toString();
            sep = ",";
        }
        return out.str();
    }

    vector<Predicate> getBody(){
        return body;
    }

    Predicate getHead(){
        return head;
    }
private:
    Predicate head;
    vector<Predicate> body;
};

#endif //LAB1_RULE_H
