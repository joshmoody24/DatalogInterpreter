//
// Created by joshm on 6/22/2022.
//

#ifndef LAB1_TOKENTYPE_H
#define LAB1_TOKENTYPE_H

#include <string>
#include <sstream>
using namespace std;

enum TokenType {
    COMMA,
    COLON,
    COLON_DASH,
    UNDEFINED,
    ID,
    COMMENT,
    STRING,
    QUERIES,
    SCHEMES,
    LEFT_PAREN,
    RIGHT_PAREN,
    Q_MARK,
    RULES,
    PERIOD,
    END_OF_FILE,
    MULTIPLY,
    ADD,
    FACTS,
};

#endif //LAB1_TOKENTYPE_H
