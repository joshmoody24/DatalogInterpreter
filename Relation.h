//
// Created by joshm on 7/11/2022.
//

#ifndef LAB1_RELATION_H
#define LAB1_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>
#include <map>

class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;

    Header combineHeaders(Header &h1, Header &h2, vector<int> &uniqueCols){
	Header newHeader = Header();
	for(string attr : h1.getAttributes()){
		newHeader.push_back(attr);
	}

	for(int i : uniqueCols){
		newHeader.push_back(h2.at(i));
	}
	return newHeader;
    }

    bool isJoinable(Tuple &t1, Tuple &t2, map<int, int> &overlap){
	for(auto item : overlap){
		if(t1.at(item.first) != t2.at(item.second)){
			return false;
		}
	}

	return true;
    }

    Tuple combineTuples(Tuple &t1, Tuple &t2, vector<int> &uniqueCols){
	Tuple newTuple = Tuple();
	for(string val : t1.getValues()){
		newTuple.push_back(val);	
	}
	for(int i : uniqueCols){
		newTuple.push_back(t2.at(i));
	}
	return newTuple;
    }

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

    bool addTuple(Tuple t) {
        return tuples.insert(t).second;
    }

    set<Tuple> getTuples(){
	return tuples;
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

    Relation* unionWith(Relation* other){
        Relation* output = new Relation();

        output->setName(this->name + " " + other->getName());
        output->setHeader(this->header);

        for (Tuple t : this->tuples){
            output->addTuple(t);
        }

        for (Tuple t : other->getTuples()){
            output->addTuple(t);
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
        for(unsigned int i = 0; i < indiciesToKeep.size(); i++){
            newHeader.push_back(header.at(indiciesToKeep.at(i)));
        }
        output->setHeader(newHeader);
        // loop through all the tuples
        // for each tuple "re-order" it
        for(Tuple t : tuples){
            Tuple newTuple = Tuple();
            for(unsigned int j = 0; j < indiciesToKeep.size(); j++){
                newTuple.push_back(t.at(indiciesToKeep.at(j)));
            }
            output->addTuple(newTuple);
        }
        return output;
    }

    Relation* natJoin(Relation* other){
	Relation* r1 = this;
	Relation* r2 = other;

	Relation* output = new Relation();

	// set name
	output->setName(r1->getName() + " |x| " + r2->getName());

	// calculate header overlap
	Header h1 = r1->getHeader();
	Header h2 = r2->getHeader();
	map<int, int> overlap = map<int, int>();
	vector<int> uniqueCols = vector<int>();
	for(unsigned int i2 = 0; i2 < h2.size(); i2++){
		bool found = false;
		for(unsigned int i1 = 0; i1 < h1.size(); i1++){
			if(h1.at(i1) == h2.at(i2)){
				found = true;
				overlap[i1] = i2;
			}
		}

		if(!found){
			uniqueCols.push_back(i2);
		}
	}
	
	// combine headers
	Header newHeader = combineHeaders(h1, h2, uniqueCols);
	output->setHeader(newHeader);	

	// combine tuples
	for(Tuple t1 : r1->getTuples()){
		for(Tuple t2 : r2->getTuples()){
			if(isJoinable(t1, t2, overlap)){
				Tuple newTuple = combineTuples(t1, t2, uniqueCols);
				output->addTuple(newTuple);
			}
		}
	}
	
	return output;
    }
};

#endif //LAB1_RELATION_H
