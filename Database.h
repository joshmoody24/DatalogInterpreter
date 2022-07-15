//
// Created by joshm on 7/15/2022.
//

#ifndef LAB1_DATABASE_H
#define LAB1_DATABASE_H

#include "Relation.h"
#include <map>
#include <set>

class Database{
private:
    map<string, Relation> relations;
public:
    Database(){};

    void addRelation(Predicate scheme){
        Relation r = Relation();
        r.setName(scheme.getName());
        Header h = Header();
        for(Parameter p : scheme.getParameters()){
            h.push_back(p.getValue());
        }
        r.setHeader(h);
        relations[r.getName()] = r;
    }

    void addFact(Predicate f){
        Tuple t = Tuple();
        for(Parameter p : f.getParameters()){
            t.push_back(p.getValue());
        }
        relations[f.getName()].addTuple(t);
    }

    Relation* query(Predicate q){
        // Get the Relation from the Database with the same name as the predicate name in the query.
        Relation relevantTable = relations[q.getName()];
        Relation* output = relevantTable.copy();

        // Use one or more select operations to select the tuples from the Relation that match the query.
        // Iterate over the parameters of the query:
        // If the parameter is a constant,
        // select the tuples from the Relation that have the same value as the constant in the same position as the constant.
        // If the parameter is a variable and the same variable name appears later in the query,
        // select the tuples from the Relation that have the same value in both positions where the variable name appears.
        map<string, int> variablePositions;
        vector<string> variables;
        vector<unsigned int> indicesToKeep;
        vector<Parameter> params = q.getParameters();
        for(int i = 0; i < params.size(); i++){
            Parameter param = params.at(i);
            // if it starts with single quote, it's a constant
            bool isConstant = param.getValue()[0] == '\'';
            if(isConstant){
                output = output->select(i, param.getValue());
            }
            // if it's a variable and it's appeared before
            else if(variablePositions.find(param.getValue()) != variablePositions.end()) {
                int prevColumn = variablePositions.at(param.getValue());
                output = output->select(prevColumn, i);
            }
            // if it's a variable and it has NOT appeared before
            else{
                indicesToKeep.push_back(i);
                variables.push_back(param.getValue());
            }
            variablePositions[param.getValue()] = i;
        }

        // After selecting the matching tuples,
        // use the project operation to keep only the columns from the Relation
        // that correspond to the positions of the variables in the query.
        // Make sure that each variable name appears only once in the resulting relation.
        // If the same name appears more than once,
        // keep the first column where the name appears and remove any later columns where the same name appears.
        // (This makes a difference when there are other columns in between the ones with the same name.)
        output = output->project(indicesToKeep);

        // After projecting, use the rename operation to rename the header of the Relation to the names of the variables found in the query.
        output = output->rename(variables);

        return output;
    }

    string toString(){
        stringstream out;
        for(auto &item : relations){
            out << item.second.toString() << endl;
        }
        return out.str();
    }
};

#endif //LAB1_DATABASE_H
