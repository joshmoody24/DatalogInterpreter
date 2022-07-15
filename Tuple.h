//
// Created by joshm on 7/11/2022.
//

#ifndef LAB1_TUPLE_H
#define LAB1_TUPLE_H

#include <vector>
#include <iostream>
#include <sstream>
#include "Header.h"
using namespace std;

class Tuple {

private:

    vector<string> values;

public:
    Tuple() { }
    Tuple(vector<string> values) : values(values) { }

    //You must define this to allow tuples to be put into a set
    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    // Tuple :
    unsigned int size() {
        return values.size();
    }

    string at(unsigned int index) {
        return values.at(index);
    }

    void push_back(string value) {
        values.push_back(value);
    }

    // This goes in your tuple class, note that tuple must include Header.h
    string toString(Header header) {
        // for the toString
        if (size() != header.size()) {
            throw "Error: mismatched tuple and header sizes";
        }
        stringstream out;
        string sep = "";
        for (unsigned i = 0; i < size(); i++) {
            string name = header.at(i);
            string value = at(i);
            out << sep << name << "=" << value;
            sep = ", ";
        }
        return out.str();
    }
};

#endif //LAB1_TUPLE_H
