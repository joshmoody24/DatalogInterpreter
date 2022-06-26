cmake_minimum_required(VERSION 3.16)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp Token.h TokenType.h Lexer/Automata/Automaton.h Lexer/Lexer.h Lexer/Automata/ColonAutomaton.h Lexer/Automata/ColonDashAutomaton.h Lexer/Automata/UndefinedCharAutomaton.h Lexer/Automata/IDAutomaton.h Lexer/Automata/QueriesAutomaton.h Lexer/Automata/LeftParenAutomaton.h Lexer/Automata/StringAutomaton.h Lexer/Automata/CommaAutomaton.h Lexer/Automata/QMarkAutomata.h Lexer/Automata/PeriodAutomaton.h Lexer/Automata/EOFAutomaton.h Lexer/Automata/RulesAutomaton.h Lexer/Automata/FactsAutomaton.h Lexer/Automata/LineCommentAutomaton.h Lexer/Automata/BlockCommentAutomaton.h Lexer/Automata/UnterminatedStringAutomaton.h Lexer/Automata/UnterminatedCommentAutomaton.h Lexer/Automata/SchemesAutomaton.h Lexer/Automata/MultiplyAutomaton.h Lexer/Automata/AddAutomation.h)
