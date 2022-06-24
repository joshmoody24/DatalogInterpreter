//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_BLOCKCOMMENTAUTOMATON_H
#define LAB1_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"
class BlockCommentAutomaton : public Automaton {
public:
    BlockCommentAutomaton(){
        type = TokenType::COMMENT;
    }
private:
    void s0(){
        if(match('#')){
            next();
            s1();
        }
        else sError();
    }
    void s1(){
        if(endOfFile()){
            sError();
            return;
        }
        if(match('|')){
            next();
            s2();
        }
        else return sError();
    }

    void s2(){
        if(endOfFile()){
            sError();
            return;
        }
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
        if(endOfFile()){
            sError();
            return;
        }
        if(match('#')){
            return;
        }
    }
};

#endif //LAB1_BLOCKCOMMENTAUTOMATON_H
