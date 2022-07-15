//
// Created by joshm on 7/11/2022.
//

#ifndef LAB1_RELATION_H
#define LAB1_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>

class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;

public:
    Relation() {}

    string getName() {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }

    Header getHeader() {
        return header;
    }

    void setHeader(Header newHeader) {
        header = newHeader;
    }

    void addTuple(Tuple t) {
        tuples.insert(t);
    }

    string toString() {
        stringstream out;
        for (Tuple t: tuples) {
            if (t.size() > 0) {
                out << "  " << t.toString(header) << endl;
            }
        }
        return out.str();
    }

    unsigned int size() {
        return tuples.size();
    }

    Relation* copy(){
        Relation* output = new Relation();
        output->setName(this->name); // copy over name
        output->setHeader(this->header); // copy over header
        for(Tuple currTuple : this->tuples){
            output->addTuple(currTuple);
        }
        return output;
    }

    Relation* select(unsigned int col, string value) {
        Relation* output = new Relation(); // make a new empty relation

        output->setName(this->name); // copy over name
        output->setHeader(this->header); // copy over header

        for (Tuple currTuple : this->tuples) { // loop through each tuple
            if (currTuple.at(col) == value) {
                output->addTuple(currTuple);
            }
        }

        return output;
    }

    Relation* select(unsigned int col1, unsigned int col2) {
        Relation* output = new Relation();
        // check to make sure both columns are in bounds
        // write your code here
        if(col1 >= header.size() || col2 >= header.size()){
            throw "Error: column indices out of bounds";
        }

        output->setName(this->name); // copy over name
        output->setHeader(this->header); // copy over header

        for (Tuple currTuple : this->tuples) { // loop through each tuple
            if (currTuple.at(col2) == currTuple.at(col1)) {
                output->addTuple(currTuple);
            }
        }

        return output;
    }

    Relation* rename(vector<string> newAttributes) {
        // Make a new empty relation
        Relation* output = new Relation();
        // Make a new Header with newAttributes as its contents
        Header newHeader = Header(newAttributes);
        output->setHeader(newHeader);
        // copy over the old name
        output->setName(name);
        // copy over all of the existing tuples
        for (Tuple currTuple : this->tuples) { // loop through each tuple
            output->addTuple(currTuple);
        }
        return output;
    }

    Relation* project(vector<unsigned int> indiciesToKeep) {
        // Make a new empty relation
        Relation* output = new Relation();
        // copy over the old name
        output->setName(name);
        // keep only the columns in the
        // vector in the order they are given
        Header newHeader = Header();
        for(int i = 0; i < indiciesToKeep.size(); i++){
            newHeader.push_back(header.at(indiciesToKeep.at(i)));
        }
        output->setHeader(newHeader);
        // loop through all the tuples
        // for each tuple "re-order" it
        for(Tuple t : tuples){
            Tuple newTuple = Tuple();
            for(int j = 0; j < indiciesToKeep.size(); j++){
                newTuple.push_back(t.at(indiciesToKeep.at(j)));
            }
            output->addTuple(newTuple);
        }
        return output;
    }
};

#endif //LAB1_RELATION_H
