//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_UNTERMINATEDSTRINGAUTOMATON_H
#define LAB1_UNTERMINATEDSTRINGAUTOMATON_H

#include "Automaton.h"

class UnterminatedStringAutomaton : public Automaton {
public:
    UnterminatedStringAutomaton(){
        type = TokenType::UNDEFINED;
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
            return;
        }
        else if(match('\'')){
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
            sError();
            return;
        }
    }
};

#endif //LAB1_UNTERMINATEDSTRINGAUTOMATON_H
