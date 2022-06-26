//
// Created by joshm on 6/22/2022.
//

#ifndef LAB1_IDAUTOMATON_H
#define LAB1_IDAUTOMATON_H

#include "Automaton.h"

// need these for isalnum and isalpha
#include <stdio.h>
#include <ctype.h>
class IDAutomaton : public Automaton {
public:
    IDAutomaton() {
        type = TokenType::ID; // set the type
    }
private:
    void s0() {
        if (isalpha(curr())) {
            next();
            s1();
        }
        else
            sError();
    }
    void s1() {
        if (endOfFile()) {
            return; // accept
        }
        else if (isalnum(curr())) {
            next();
            s1();
        }
        else
            return; //accept
    }
};

#endif //LAB1_IDAUTOMATON_H
