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
        return tokens.at(currTokenIndex).getType();
    }
    void advanceToken() {
        currTokenIndex++;
    }
    void throwError() {
        throw tokens.at(currTokenIndex);
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
        if (currTokenIndex < 1) throw "previous token contents error: attempted to read before the first token";
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
            ids = idList(ids);
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

        ids = idList(ids);
        match(RIGHT_PAREN);

        for(Parameter i : ids){
            newScheme.addParameter(i);
        }

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
        Predicate newFact;
        newFact.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        match(STRING);
        Parameter first = Parameter(getPrevTokenContents());
        vector<Parameter> params = vector<Parameter>();
        params.push_back(first);
        params = stringList(params);
        newFact.setParameters(params);
        // add strings to the domain
        for(Parameter p : params){
            program.addDomainItem(p.toString());
        }

        match(RIGHT_PAREN);
        match(PERIOD);
        program.addFact(newFact);
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

    vector<Parameter> stringList(vector<Parameter> params){
        if(tokenType() == COMMA){
            match(COMMA);
            match(STRING);
            params.push_back(Parameter(getPrevTokenContents()));
            params = stringList(params);
            return params;
        }
        else {
            // lambda
            return params;
        }
    }

    Rule rule(){
        Rule rule;
        Predicate head = headPredicate();
        rule.setHead(head);
        match(COLON_DASH);
        vector<Predicate> predicates = vector<Predicate>();
        Predicate first = predicate();
        predicates.push_back(first);
        predicates = predicateList(predicates);
        for(Predicate p : predicates){
            rule.addPredicate(p);
        }
        match(PERIOD);
        return rule;
    }

    void ruleList(){
        if(tokenType() == ID) {
            Rule r = rule();
            program.addRule(r);
            ruleList();
        }
        else {
            // lambda
        }
    }

    void query(){
        Predicate p = predicate();
        program.addQuery(p);
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

    Predicate predicate(){
        if(tokenType() == ID){
            Predicate p = Predicate();
            match(ID);
            p.setName(getPrevTokenContents());
            match(LEFT_PAREN);
            vector<Parameter> ids;
            Parameter first = parameter();
            ids.push_back(first);
            ids = parameterList(ids);
            p.setParameters(ids);
            match(RIGHT_PAREN);
            return p;
        }
        else{
            // lambda
        }
    }

    Predicate headPredicate(){
        if(tokenType() == ID){
            Predicate hp;
            match(ID);
            hp.setName(getPrevTokenContents());
            match(LEFT_PAREN);
            match(ID);
            vector<Parameter> ids = vector<Parameter>();
            ids.push_back(getPrevTokenContents());
            ids = idList(ids);
            hp.setParameters(ids);
            match(RIGHT_PAREN);
            return hp;
        }
        else{
            // lambda
            return Predicate();
        }
    }

    vector<Predicate> predicateList(vector<Predicate> ids){
        if(tokenType() == COMMA){
            match(COMMA);
            Predicate p = predicate();
            ids.push_back(p);
            predicateList(ids);
            return ids;
        }
        else {
            // lambda
            return ids;
        }
    }

    Parameter parameter(){
        if(tokenType() == STRING){
            match(STRING);
            return Parameter(getPrevTokenContents());
        }
        else if(tokenType() == ID){
            match(ID);
            Parameter p = Parameter(getPrevTokenContents());
            return p;
        }
        else{
            throwError();
            return Parameter();
        }
    }

    vector<Parameter> parameterList(vector<Parameter> ids){
        if(tokenType() == COMMA){
            match(COMMA);
            Parameter p = parameter();
            ids.push_back(p);
            ids = parameterList(ids);
            return ids;
        }
        else{
            // lambda
            return ids;
        }
    }
};

#endif //LAB1_PARSER_H
