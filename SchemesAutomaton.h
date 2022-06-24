//
// Created by joshm on 6/23/2022.
//

#ifndef LAB1_SCHEMESAUTOMATON_H
#define LAB1_SCHEMESAUTOMATON_H

class SchemesAutomaton : public Automaton {
public:
    SchemesAutomaton() {
        type = TokenType::QUERIES;
    }
private:
    void s0() {
        if(match('S')){
            next();
            s1();
        }
        else sError();
    }

    void s1(){
        if(endOfFile()) {
            sError();
            return;
        }
        if(match('c')){
            next();
            s2();
        }
        else sError();
    }

    void s2(){
        if(endOfFile()) {
            sError();
            return;
        }
        if(match('h')){
            next();
            s3();
        }
        else sError();
    }

    void s3() {
        if(endOfFile()) {
            sError();
            return;
        }
        if (match('e')) {
            next();
            s4();
        }
        else sError();
    }

    void s4(){
        if(endOfFile()) {
            sError();
            return;
        }
        if(match('m')){
            next();
            s5();
        }
        else sError();
    }

    void s5(){
        if(endOfFile()) {
            sError();
            return;
        }
        if(match('e')){
            next();
            s6();
        }
        else sError();
    }

    void s6(){
        if(endOfFile()) {
            sError();
            return;
        }
        if(match('s')){
            next();
            return;
        }
        else sError();
    }

};

#endif //LAB1_SCHEMESAUTOMATON_H
