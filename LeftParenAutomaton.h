//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_LEFTPARENAUTOMATON_H
#define LAB1_LEFTPARENAUTOMATON_H

#include "Automaton.h"
class LeftParenAutomaton : public Automaton {
public:
    LeftParenAutomaton() {
        type = TokenType::LEFT_PAREN; // set the type
    }
private:
    void s0() {
        if (match('(')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_LEFTPARENAUTOMATON_H
