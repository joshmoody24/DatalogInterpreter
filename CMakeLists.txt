cmake_minimum_required(VERSION 3.16)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp Token.h TokenType.h Automaton.h Lexer.h ColonAutomaton.h ColonDashAutomaton.h UndefinedCharAutomaton.h IDAutomaton.h)
