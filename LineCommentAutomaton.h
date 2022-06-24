//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_LINECOMMENTAUTOMATON_H
#define LAB1_LINECOMMENTAUTOMATON_H

#include "Automaton.h"
class LineCommentAutomaton : public Automaton {
public:
    LineCommentAutomaton(){
        type = TokenType::COMMENT;
    }
private:
    void s0(){
        if(match('#')){
            next();
            s1();
        }
        else return sError();
    }
    void s1(){
        if(match('|')){
            sError();
            return;
        }
        else s2();
    }
    void s2(){
        if(!match('\n')){
            next();
            s2();
        }
        else return;
    }
};

#endif //LAB1_LINECOMMENTAUTOMATON_H
