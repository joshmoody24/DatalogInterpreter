//
// Created by joshm on 6/25/2022.
//

#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser {
private:
    vector<Token> tokens;
    DatalogProgram program;
    int currTokenIndex = 0;
public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}
    TokenType tokenType() const {
        if(tokens.empty()) throw "Attempted to get token type in empty vector";
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
        currTokenIndex++;
    }
    void throwError() {
        throw tokens.at(0);
    }

    DatalogProgram parse() {
        datalogProgram();
        return program;
    }

    string match(TokenType t) {
        string tokenValue = "DATA UNCAUGHT";
        if (tokenType() == t){
            tokenValue = "MATCH";
            if(!tokens.empty()) advanceToken();
        }
        else{
            throwError();
        }
        return tokenValue;
    }

    string getPrevTokenContents() {
        if (currTokenIndex < 0) throw "previous token contents error: attempted to read before the first token";
        return tokens.at(currTokenIndex - 1).getContents();
    }

    string getCurrTokenContents() {
        if (currTokenIndex >= tokens.size()) throw "current token contents error: attempted to read past the end of the tokens";
        return tokens.at(currTokenIndex).getContents();
    }

    void datalogProgram(){
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(END_OF_FILE);
    }

    vector<Parameter> idList(vector<Parameter> ids) {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            ids.push_back(Parameter(getPrevTokenContents()));
            idList(ids);
            return ids;
        } else {
            // lambda
            return ids;
        }
    }

    void scheme() {
        Predicate newScheme;

        match(ID);
        newScheme.setName(getPrevTokenContents());

        match(LEFT_PAREN);
        match(ID);

        vector<Parameter> ids = vector<Parameter>();
        Parameter firstParameter;
        firstParameter.setValue(getPrevTokenContents());
        ids.push_back(firstParameter);

        idList();
        match(RIGHT_PAREN);

        program.addScheme(newScheme);
    }

    void schemeList(){
        if(tokenType() == ID){
            scheme();
            schemeList();
        }
        else{
            // lambda
        }
    }

    void fact(){
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }

    void factList(){
        if(tokenType() == ID) {
            fact();
            factList();
        }
        else{
            // lambda
        }
    }

    void stringList(){
        if(tokenType() == COMMA){
            match(COMMA);
            match(STRING);
            stringList();
        }
        else {
            // lambda
        }
    }

    void rule(){
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }

    void ruleList(){
        if(tokenType() == ID) {
            rule();
            ruleList();
        }
        else {
            // lambda
        }
    }

    void query(){
        predicate();
        match(Q_MARK);
    }

    void queryList(){
        if(tokenType() == ID){
            query();
            queryList();
        }
        else{
            // lambda
        }
    }

    void predicate(){
        if(tokenType() == ID){
            match(ID);
            match(LEFT_PAREN);
            parameter();
            parameterList();
            match(RIGHT_PAREN);
        }
        else{
            // lambda
        }
    }

    void headPredicate(){
        if(tokenType() == ID){
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
        else{
            // lambda
        }
    }

    void predicateList(){
        if(tokenType() == COMMA){
            match(COMMA);
            predicate();
            predicateList();
        }
        else {
            // lambda
        }
    }

    void parameter(){
        if(tokenType() == STRING){
            match(STRING);
        }
        else if(tokenType() == ID){
            match(ID);
        }
        else{
            throwError();
        }
    }

    void parameterList(){
        if(tokenType() == COMMA){
            match(COMMA);
            parameter();
            parameterList();
        }
        else{
            // lambda
        }
    }
};

#endif //LAB1_PARSER_H
