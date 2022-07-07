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
#include "QueriesAutomaton.h"
#include "RightParenAutomaton.h"
#include "LeftParenAutomaton.h"
#include "StringAutomaton.h"
#include "CommaAutomaton.h"
#include "QMarkAutomata.h"
#include "PeriodAutomaton.h"
#include "EOFAutomaton.h"
#include "RulesAutomaton.h"
#include "FactsAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "LineCommentAutomaton.h"
#include "UnterminatedStringAutomaton.h"
#include "UnterminatedCommentAutomaton.h"
#include "SchemesAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomation.h"

#include <iostream>
#include <cctype>

class Lexer {
public:
    void initializeAutomata() {
        // Here you will create and add each automaton to your automata vector
        // order matters (higher = higher precedence)
        automata.push_back(new ColonAutomaton());
        automata.push_back(new ColonDashAutomaton());
        automata.push_back(new QueriesAutomaton());
        automata.push_back(new RulesAutomaton());
        automata.push_back(new LeftParenAutomaton());
        automata.push_back(new RightParenAutomaton());
        automata.push_back(new StringAutomaton());
        automata.push_back(new CommaAutomaton());
        automata.push_back(new QMarkAutomaton());
        automata.push_back(new PeriodAutomaton());
        automata.push_back(new FactsAutomaton());
        automata.push_back(new BlockCommentAutomaton());
        automata.push_back(new LineCommentAutomaton());
        automata.push_back(new UnterminatedStringAutomaton());
        automata.push_back(new UnterminatedCommentAutomaton());
        automata.push_back(new SchemesAutomaton());
        automata.push_back(new AddAutomaton());
        automata.push_back(new MultiplyAutomaton());

        // currently, my EOFAutomaton is a bit buggy (shows newline in contents)
        // so I'm just gonna fake it by tacking on an EOF token at the end always
        // and will reevaluate later
        //automata.push_back(new EOFAutomaton());

        // make sure these ones are run last
        automata.push_back(new IDAutomaton());
        automata.push_back(new UndefinedCharAutomaton());
    }

    vector<Token> run(string input) {

        unsigned int currentLine = 1;
        initializeAutomata();

        while(input.size() > 0) {

            Automaton *maxAutomaton = automata.at(0);
            unsigned int maxRead = 0;

            // TODO:: handle whitespace and count newlines

            for (unsigned int i = 0; i < automata.size(); i++) {
                Automaton *currentAutomaton = automata.at(i);
                unsigned int numRead = currentAutomaton->run(input);
                //Token t = Token(currentAutomaton->getType(), "X", 0);
                //std::cout << '\t' << t.toString() << ", " << numRead << ", " << input[0] << endl;
                if (numRead > maxRead) {
                    maxAutomaton = currentAutomaton;
                    maxRead = numRead;
                }
            }

            Token currToken = Token(maxAutomaton->getType(), input.substr(0, maxRead),
                                    currentLine);

            // update the current line based on the number of newlines read
            currentLine += maxAutomaton->getNewLines();

            // ignore whitespace tokens
            if(currToken.getType() != UNDEFINED || currToken.getContents().size() != 1 || !isspace(currToken.getContents()[0])){
                // cout << currToken.toString() << endl;
                // ignore comments
                if(currToken.getType() != COMMENT){
                    tokens.push_back(currToken);
                }
            }

            input = input.substr(maxRead);
        }

        // add the EOF Token
        Token EOFToken = Token(END_OF_FILE, "", currentLine);
        // cout << EOFToken.toString() << endl;

        tokens.push_back(EOFToken);

        //cout << "Total Tokens = " << tokens.size() << endl;
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
