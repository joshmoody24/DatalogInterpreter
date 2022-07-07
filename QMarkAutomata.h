//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_QMARKAUTOMATA_H
#define LAB1_QMARKAUTOMATA_H

#include "Automaton.h"
class QMarkAutomaton : public Automaton {
public:
    QMarkAutomaton() {
        type = TokenType::Q_MARK; // set the type
    }
private:
    void s0() {
        if (match('?')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_QMARKAUTOMATA_H
