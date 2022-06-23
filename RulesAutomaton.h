//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_RULESAUTOMATON_H
#define LAB1_RULESAUTOMATON_H

#include "Automaton.h"
#include <iostream>

class RulesAutomaton : public Automaton {
public:
    RulesAutomaton() {
        type = TokenType::RULES;
    }
private:
    void s0() {
        if(match('R')){
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
        if(match('u')){
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
        if(match('l')){
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
        if (match('e')) {
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

#endif //LAB1_RULESAUTOMATON_H
