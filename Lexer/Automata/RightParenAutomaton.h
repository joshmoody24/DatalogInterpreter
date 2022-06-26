//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_RIGHTPARENAUTOMATON_H
#define LAB1_RIGHTPARENAUTOMATON_H

#include "Automaton.h"
class RightParenAutomaton : public Automaton {
public:
    RightParenAutomaton() {
        type = TokenType::RIGHT_PAREN; // set the type
    }
private:
    void s0() {
        if (match(')')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_RIGHTPARENAUTOMATON_H
