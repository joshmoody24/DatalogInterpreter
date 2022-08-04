//
// Created by joshm on 8/3/2022.
//

#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H

#include "Rule.h"
#include <map>
#include <set>
#include <unordered_set>
#include <sstream>
using namespace std;

class Graph {
private:
    map<int, set<int>> adjacencyList;
    unordered_set<int> visited;

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

    set<int> getDependencies(int node){
        return adjacencyList.at(node);
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

    // returns postorder
    vector<int> dfs(int node, vector<int> postOrder){
        if(visited.count(node) != 0) return postOrder;
        visited.insert(node);
        for(int next : adjacencyList.at(node)){
            postOrder = dfs(next, postOrder);
        }
        postOrder.push_back(node);
        return postOrder;
    }

    // returns SCCs
    set<int> generateSCC(int node, set<int> tree){
        if(visited.count(node) != 0) return tree;
        visited.insert(node);
        tree.insert(node);
        for(int next : adjacencyList.at(node)){
            set<int> subTree = generateSCC(next, tree);
            for(int i : subTree){
                tree.insert(i);
            }
        }
        return tree;
    }

    vector<int> dfsForest(){
        visited.clear();
        vector<int> postOrder;
        for(auto pair : adjacencyList){
            int node = pair.first;
            vector<int> postOrderSub = dfs(node, vector<int>());
            for(int i : postOrderSub){
                postOrder.push_back(i);
            }
        }
        return postOrder;
    }

    vector<set<int>> dfsForest(vector<int> priorityList){
        visited.clear();
        vector<set<int>> forest;
        while(priorityList.size() > 0){
            int nextNode = priorityList.at(0);
            set<int> tree = generateSCC(nextNode, set<int>());
            forest.push_back(tree);
            priorityList.erase(priorityList.begin());
        }
        return forest;
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
