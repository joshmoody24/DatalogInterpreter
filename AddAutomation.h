//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_ADDAUTOMATION_H
#define LAB1_ADDAUTOMATION_H

#include "Automaton.h"
class AddAutomaton : public Automaton {
public:
    AddAutomaton() {
        type = TokenType::ADD; // set the type
    }
private:
    void s0() {
        if (match('+')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_ADDAUTOMATION_H
