//
// Created by joshm on 6/22/2022.
//

#ifndef LAB1_TOKEN_H
#define LAB1_TOKEN_H

#include "TokenType.h"

class Token {
public:
    Token(TokenType _type, string _contents, unsigned int _line){
        type = _type;
        contents = _contents;
        line = _line;
    }
    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << contents << "\"" << "," << line << ")";
        return out.str();
    }
private:
    TokenType type;
    string contents;
    unsigned int line;
    string typeName(TokenType type) const {
        switch(type) {
            case COMMA:
                return "COMMA";
            case COLON:
                return "COLON";
            case UNDEFINED:
                return "UNDEFINED";
            case ID:
                return "ID";
            case COLON_DASH:
                return "COLON_DASH";
            default:
                return "UNDEFINED";
        }
    }
};

#endif //LAB1_TOKEN_H
