//
// Created by joshm on 6/22/2022.
//

#ifndef LAB1_UNDEFINEDCHARAUTOMATON_H
#define LAB1_UNDEFINEDCHARAUTOMATON_H

#include "Automaton.h"
class UndefinedCharAutomaton : public Automaton {
public:
    UndefinedCharAutomaton() {
        type = TokenType::UNDEFINED; // set the type
    }
private:
    void s0() {
        next(); // read next character
        return; // accept the input
    }
};

#endif //LAB1_UNDEFINEDCHARAUTOMATON_H
