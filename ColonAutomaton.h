//
// Created by joshm on 6/22/2022.
//

#ifndef LAB1_COLONAUTOMATON_H
#define LAB1_COLONAUTOMATON_H

#include "Automaton.h"
class ColonAutomaton : public Automaton {
public:
    ColonAutomaton() {
        type = TokenType::COLON; // set the type
    }
private:
    void s0() {
        if (match(':')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_COLONAUTOMATON_H
