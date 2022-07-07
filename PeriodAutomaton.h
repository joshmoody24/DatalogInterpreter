//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_PERIODAUTOMATON_H
#define LAB1_PERIODAUTOMATON_H

#include "Automaton.h"
class PeriodAutomaton : public Automaton {
public:
    PeriodAutomaton() {
        type = TokenType::PERIOD; // set the type
    }
private:
    void s0() {
        if (match('.')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_PERIODAUTOMATON_H
