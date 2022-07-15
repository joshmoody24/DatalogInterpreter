//
// Created by joshm on 7/11/2022.
//

#ifndef LAB1_HEADER_H
#define LAB1_HEADER_H

#include <iostream>
#include <vector>
using namespace std;

class Header {

private:
    vector<string> attributes;

public:
    Header() { }
    Header(vector<string> attributes) : attributes(attributes) { }

// Header :
    unsigned int size() {
        return attributes.size();
    }

    string at(unsigned int index) {
        if (index >= size()) {
            throw "Error: index extends past header size";
        }
        return attributes.at(index);
    }

    void push_back(string value) {
        attributes.push_back(value);
    }

    vector<string> getAttributes(){
        return attributes;
    }


};

#endif //LAB1_HEADER_H
