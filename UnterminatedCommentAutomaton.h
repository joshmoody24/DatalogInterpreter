//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_UNTERMINATEDCOMMENTAUTOMATON_H
#define LAB1_UNTERMINATEDCOMMENTAUTOMATON_H

#include "Automaton.h"

class UnterminatedCommentAutomaton : public Automaton {
public:
    UnterminatedCommentAutomaton(){
        type = TokenType::UNDEFINED;
    }
private:
    void s0() {
        if (match('#')) {
            next();
            s1();
        }
        else
            sError();
    }

    void s1(){
        if(endOfFile()){
            return;
        }
        if(match('|')){
            next();
            s2();
        }
        else sError();
    }

    void s2(){
        if(endOfFile()) return;
        if(match('|')){
            next();
            s3();
        }
        else{
            next();
            s2();
        }
    }

    void s3(){
        if(match('#')){
            sError();
            return;
        }
        else {
            next();
            s2();
        }
    }
};

#endif //LAB1_UNTERMINATEDCOMMENTAUTOMATON_H
