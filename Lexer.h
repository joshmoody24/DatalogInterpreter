//
// Created by joshm on 6/22/2022.
//

#ifndef LAB1_LEXER_H
#define LAB1_LEXER_H

#include <vector>
#include "Token.h"
#include "Automaton.h"
#include "IDAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "UndefinedCharAutomaton.h"
#include <iostream>

class Lexer {
public:
    void initializeAutomata() {
        // Here you will create and add each automaton to your automata vector
        automata.push_back(new ColonAutomaton());
        automata.push_back(new ColonDashAutomaton());
        automata.push_back(new IDAutomaton());
        automata.push_back(new UndefinedCharAutomaton());
    }

    vector<Token> run(string input) {
        initializeAutomata();

        // TODO:: write the parallel and max logic
        while(input.size() > 0) {
            Automaton *maxAutomaton = automata.at(0);
            unsigned int maxRead = 0;

            // TODO:: handle whitespace and count newlines
            for (unsigned int i = 0; i < automata.size(); i++) {
                Automaton *currentAutomaton = automata.at(i);
                unsigned int numRead = currentAutomaton->run(input);
                if (numRead > maxRead) {
                    maxAutomaton = currentAutomaton;
                    maxRead = numRead;
                }
            }

            Token currToken = Token(maxAutomaton->getType(), input.substr(0, maxRead),
                                    0/*defaults to 0, you will need to fix for the project*/);
            cout << currToken.toString() << endl;
            input = input.substr(maxRead);
            tokens.push_back(currToken);
        }

        return tokens;
    }

    vector<Token> getTokens(){
        return tokens;
    }

private:
    vector<Automaton*> automata;
    vector<Token> tokens;
};

#endif //LAB1_LEXER_H
