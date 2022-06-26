//
// Created by joshm on 6/25/2022.
//

#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H

#include "../Token.h"
#include <vector>

class Parser {
private:
    vector<Token> tokens;
public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}
    TokenType tokenType() const {
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    void throwError() {
        throw tokens.at(0);
    }
};

#endif //LAB1_PARSER_H
