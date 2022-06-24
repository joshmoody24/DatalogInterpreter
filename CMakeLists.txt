cmake_minimum_required(VERSION 3.16)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp Token.h TokenType.h Automaton.h Lexer.h ColonAutomaton.h ColonDashAutomaton.h UndefinedCharAutomaton.h IDAutomaton.h QueriesAutomaton.h LeftParenAutomaton.h StringAutomaton.h CommaAutomaton.h QMarkAutomata.h PeriodAutomaton.h EOFAutomaton.h RulesAutomaton.h FactsAutomaton.h LineCommentAutomaton.h BlockCommentAutomaton.h UnterminatedStringAutomaton.h UnterminatedCommentAutomaton.h SchemesAutomaton.h MultiplyAutomaton.h AddAutomation.h)
