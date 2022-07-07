//
// Created by joshm on 7/6/2022.
//

#ifndef LAB1_PARAMETER_H
#define LAB1_PARAMETER_H

#include<iostream>
using namespace std;

class Parameter{
public:
    Parameter(){};
    Parameter(string val){
        value = val;
    }
    void setValue(string _value){
        value = _value;
    }
    string getValue(){
        return value;
    }
    string toString(){
        return getValue();
    }
private:
    string value;
};

#endif //LAB1_PARAMETER_H
