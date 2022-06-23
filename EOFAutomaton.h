//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_EOFAUTOMATON_H
#define LAB1_EOFAUTOMATON_H

#include "Automaton.h"
class EOFAutomaton : public Automaton {
public:
    EOFAutomaton() {
        type = TokenType::END_OF_FILE; // set the type
    }
private:
    void s0() {
        // peek at the next character
        currCharIndex++;
        if (endOfFile()) {
            currCharIndex--;
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};

#endif //LAB1_EOFAUTOMATON_H
