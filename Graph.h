//
// Created by joshm on 8/3/2022.
//

#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H

#include "Rule.h"
#include <map>
#include <set>
#include <sstream>
using namespace std;

class Graph{
private:
    map<int, set<int>> adjacencyList;
public:
    Graph(){}
    void addConnection(int from, int to){
        if(adjacencyList.count(from) == 0){
            adjacencyList[from] = set<int>();
        }
        if(adjacencyList.count(to) == 0){
            adjacencyList[to] = set<int>();
        }
        adjacencyList.at(from).insert(to);
    }

    Graph getReverse(){
        Graph reversed = Graph();
        for(const auto &pair : adjacencyList){
            int from = pair.first;
            set<int> toList = pair.second;
            for(int to : toList){
                reversed.addConnection(to, from);
            }
        }
        return reversed;
    }

    string toString(){
        stringstream out;
        for (auto iter = adjacencyList.begin(); iter != adjacencyList.end(); ++iter){
            out << "R" << iter->first << ":";
            string sep = "";
            for(int r : iter->second){
                out << sep << "R" << r;
                sep = ",";
            }
            out << endl;
        }
        return out.str();
    }
};

#endif //LAB1_GRAPH_H
