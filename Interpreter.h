//
// Created by joshm on 7/20/2022.
//

#ifndef LAB1_INTERPRETER_H
#define LAB1_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"

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

			// evaluating rules = big complicatd
			cout << "Rule Evaluation" << endl;
			bool newRules = true;
			int iterations = 0;
			do{
				newRules = evaluateRulesOnePass();
				iterations++;
			} while(newRules);
			
			cout << "\nSchemes populated after " << iterations << " passes through the Rules.\n" << endl;

			cout << "Query Evaluation" << endl;
			for(Predicate q : program.getQueries()){
				Relation* result = db.evaluate(q);
				cout << q.toString() << "?";
				if(result->size() > 0) cout << " Yes(" << result->size() << ")" << endl;
				else cout << " No" << endl;
				cout << result->toString();
			}
		}

		bool evaluateRulesOnePass(){
			// evaluate the rules (project 4)
			// Evaluate each rule using relational algebra operations as follows:
			bool newRules = false;
			for(Rule r : program.getRules()){
				// 1. Evaluate the predicates on the right-hand side of the rule in the same way as queries from the last project
				Relation* finalResult = nullptr;
				for(Predicate b : r.getBody()){
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
				vector<Parameter> headParameters = r.getHead().getParameters();
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
				Relation* headRelation = db.evaluate(r.getHead());
				Header newHeader = Header();
				Relation relevantRelation = db.getRelation(r.getHead().getName());
				for(unsigned int i = 0; i < headRelation->getHeader().getAttributes().size(); i++){
					string name = relevantRelation.getHeader().getAttributes().at(i);
					newHeader.push_back(name);
				}
				finalResult->setHeader(newHeader);

				// 5. Union with the relation in the database:
				// Union the result from Step 4 with the relation in the database whose name matches the name of the head of the rule.
				// Evaluate the rules in the order they are given in the input file.
				cout << r.toString() << "." << endl;
				for(Tuple t : finalResult->getTuples()){
					if(db.addTuple(r.getHead().getName(), t)) {
						newRules = true;
						cout << "  " << t.toString(newHeader) << endl;
					}
				}
			}
			return newRules;
		}
};

#endif //LAB1_INTERPRETER_H
