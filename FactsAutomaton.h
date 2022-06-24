//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_FACTSAUTOMATON_H
#define LAB1_FACTSAUTOMATON_H

#include "Automaton.h"
#include <iostream>

class FactsAutomaton : public Automaton {
public:
    FactsAutomaton() {
        type = TokenType::FACTS;
    }
private:
    void s0() {
        if(match('F')){
            next();
            s1();
        }
        else sError();
    }

    void s1(){
        if(endOfFile()){
            sError();
            return;
        }
        if(match('a')){
            next();
            s2();
        }
        else sError();
    }

    void s2(){
        if(endOfFile()){
            sError();
            return;
        }
        if(match('c')){
            next();
            s3();
        }
        else sError();
    }

    void s3() {
        if(endOfFile()){
            sError();
            return;
        }
        if (match('t')) {
            next();
            s4();
        }
        else sError();
    }

    void s4(){
        if(endOfFile()){
            sError();
            return;
        }
        if(match('s')){
            next();
            return;
        }
        else sError();
    }

};

#endif //LAB1_FACTSAUTOMATON_H
