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
    string getContents() const{
        return contents;
    }
    TokenType getType() const{
        return type;
    }
    unsigned int getLine() const{
        return line;
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
            case COMMENT:
                return "COMMENT";
            case STRING:
                return "STRING";
            case QUERIES:
                return "QUERIES";
            case SCHEMES:
                return "SCHEMES";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case Q_MARK:
                return "Q_MARK";
            case RULES:
                return "RULES";
            case PERIOD:
                return "PERIOD";
            case END_OF_FILE:
                return "EOF";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case FACTS:
                return "FACTS";
        }
    }
};

#endif //LAB1_TOKEN_H
