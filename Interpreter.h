//
// Created by joshm on 7/20/2022.
//

#ifndef LAB1_INTERPRETER_H
#define LAB1_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Interpreter{
	private:
		Database db;
		DatalogProgram program;
	public:
		Interpreter(DatalogProgram program){
			db = Database();
			this->program = program;
		};

		void interpret(){

			// add all the db tables
			for(Predicate s : program.getSchemes()){
				db.addRelation(s);
			}

			// add all the tuples into those tables
			for(Predicate f : program.getFacts()){
				db.addFact(f);
			}

			// evaluating rules = big complicated
            // Build the dependency graph
            Graph dependencyGraph = Graph();
            vector<Rule> rules = program.getRules();
            for(unsigned int i = 0; i < rules.size(); i++){
                // add i to dependecy list (if not already in it)
                dependencyGraph.addNode(i);
                for(unsigned int j = 0; j < rules.size(); j++){
                    // if r2 generates something r1 depends on
                    for(Predicate pConsumed : rules.at(i).getBody()){
                        if(rules.at(j).getHead().getName() == pConsumed.getName()){
                            dependencyGraph.addConnection(i, j);
                        }
                    }
                }
            }
            cout << "Dependency Graph\n" << dependencyGraph.toString() << endl;
            // reverse it
            Graph reversedGraph = dependencyGraph.getReverse();
            // Run DFS-Forest on the reverse dependency graph to get the post-order.
            vector<int> postOrder = reversedGraph.dfsForest();
            // reverse it
            vector<int> reversedPostOrder;
            for(unsigned int i = 0; i < postOrder.size(); i++){
                int index = postOrder.size() - i - 1;
                reversedPostOrder.push_back(postOrder.at(index));
            }

            // Use the post-order for a DFS-Forest on the forward dependency graph to find the strongly connected components (SCCs).
            vector<set<int>> sccList = dependencyGraph.dfsForest(reversedPostOrder);

            // Evaluate the rules in each component.
			cout << "Rule Evaluation" << endl;
            for(set<int> scc : sccList){
                if(scc.size() == 0) continue;
                cout << "SCC: ";
                string sep = "";
                for(int i : scc){
                    cout << sep << "R" << i;
                    sep = ",";
                }
                cout << endl;

                bool newRules = true;
                int iterations = 0;
                do{
                    newRules = evaluateRulesOnePass(scc, dependencyGraph);
                    iterations++;
                } while(newRules);

                cout << iterations << " passes: ";
                sep = "";
                for(int i : scc){
                    cout << sep << "R" << i;
                    sep = ",";
                }
                cout << endl;
            }

			cout << "\nQuery Evaluation" << endl;
			for(Predicate q : program.getQueries()){
				Relation* result = db.evaluate(q);
				cout << q.toString() << "?";
				if(result->size() > 0) cout << " Yes(" << result->size() << ")" << endl;
				else cout << " No" << endl;
				cout << result->toString();
			}
		}

		bool evaluateRulesOnePass(set<int> scc, Graph dependecyGraph){
            vector<Rule> rules = program.getRules();
			// evaluate the rules (project 4)
			// Evaluate each rule using relational algebra operations as follows:
			bool newRules = false;
			for(int r : scc){
				// 1. Evaluate the predicates on the right-hand side of the rule in the same way as queries from the last project
                cout << rules[r].toString() << "." << endl;
				Relation* finalResult = nullptr;
				for(Predicate b : rules[r].getBody()){
					Relation* result = db.evaluate(b);
					// 2. Join the relations that result
					if(finalResult == nullptr){
						finalResult = result;
					}
					else{
						finalResult = finalResult->natJoin(result);
					}
				}

				// 3. Project the columns that appear in the head predicate:
				// The predicates in the body of a rule may have variables that are not used in the head of the rule.
				// The variables in the head may also appear in a different order than those in the body.
				// Use a project operation on the result from Step 2 to remove the columns that don't appear in the head of the rule
				// and to reorder the columns to match the order in the head.
				vector<unsigned int> indicesToKeep = vector<unsigned int>();
				vector<string> resultAttributes = finalResult->getHeader().getAttributes();
				vector<Parameter> headParameters = rules[r].getHead().getParameters();
				for(Parameter p : headParameters) {
					for (unsigned int i = 0; i < resultAttributes.size(); i++) {
						if(p.getValue() == resultAttributes.at(i)){
							indicesToKeep.push_back(i);
							continue;
						}
					}
				}
				finalResult = finalResult->project(indicesToKeep);

				// 4. Rename the relation to make it union-compatible:
				// Rename the relation that results from Step 3 to make it union compatible with the relation that matches the head of the rule.
				// Rename each attribute in the result from Step 3 to the attribute name found
				// in the corresponding position in the relation that matches the head of the rule.
				Relation* headRelation = db.evaluate(rules[r].getHead());
				Header newHeader = Header();
				Relation relevantRelation = db.getRelation(rules[r].getHead().getName());
				for(unsigned int i = 0; i < headRelation->getHeader().getAttributes().size(); i++){
					string name = relevantRelation.getHeader().getAttributes().at(i);
					newHeader.push_back(name);
				}
				finalResult->setHeader(newHeader);

				// 5. Union with the relation in the database:
				// Union the result from Step 4 with the relation in the database whose name matches the name of the head of the rule.
				// Evaluate the rules in the order they are given in the input file.
				for(Tuple t : finalResult->getTuples()){
					if(db.addTuple(rules[r].getHead().getName(), t)) {
						newRules = true;
						cout << "  " << t.toString(newHeader) << endl;
					}
				}
			}
            //If an SCC contains only one rule and that rule does not depend on itself, the rule is only evaluated once.
            //If an SCC contains more than one rule, or a single rule that depends on itself, repeat the evaluation of the rules in the SCC until the evaluation reaches a fixed point.
            //When an SCC contains more than one rule, evaluate the rules in the SCC in the numeric order of the rule identifiers.

            // check if scc has size of 1 and rule depends on itself
            if(scc.size() == 1){
                int rule = *scc.begin();
                set<int> dependencies = dependecyGraph.getDependencies(rule);
                if(dependencies.count(rule) == 0){
                    newRules = false;
                }
            }
			return newRules;
		}
};

#endif //LAB1_INTERPRETER_H
