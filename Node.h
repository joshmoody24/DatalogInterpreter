//
// Created by joshm on 8/3/2022.
//

#ifndef LAB1_NODE_H
#define LAB1_NODE_H

#include <vector>
using namespace std;

class Node{
private:
    vector<Node> to;
public:
    Node(){};
    Node(vector<Node> to){
        this.to = to;
    }
};

#endif //LAB1_NODE_H
