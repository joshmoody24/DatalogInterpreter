//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_STRINGAUTOMATON_H
#define LAB1_STRINGAUTOMATON_H

#include "Automaton.h"
class StringAutomaton : public Automaton {
public:
    StringAutomaton() {
        type = TokenType::STRING; // set the type
    }
private:
    void s0() {
        if (match('\'')) {
            next();
            s1();
        }
        else
            sError();
    }

    void s1(){
        if(endOfFile()){
            sError();
        }
        if(match('\'')){
            next();
            s2();
        }
        else{
            next();
            s1();
        }
    }

    void s2(){
        if(match('\'')){
            next();
            s1();
        }
        else{
            return;
        }
    }
};

#endif //LAB1_STRINGAUTOMATON_H
