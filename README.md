# Lexical-and-Syntax-Analyzers
C/C++ implementation of a Lexical Analyzer and Syntax Parser for the Cooke Programming Language featuring tokenization, recursive descent parsing, and compiler front-end error handling.


Lexical and Syntax Analyzers 
Overview

This repository contains two compiler construction projects for CS3361 – Spring 2025:

    Lexical Analyzer 

    Syntax Analyzer 

Both projects are designed to work with the Cooke Programming Language, a small imperative language defined with a concise BNF grammar. These assignments provide practical, hands-on experience with tokenization and parsing, which are the first critical stages of compilation.
Project 1 – Lexical Analyzer
Purpose

The lexical analyzer reads a source file written in the Cooke language, identifies lexemes, and classifies them into tokens according to the provided grammar and token table.
Key Features

    Implements tokenization using whitespace, tabs, and EOL characters as delimiters (ignored in output).

    Matches lexemes against a predefined token set (keywords, operators, literals, identifiers).

    Reports UNKNOWN for any invalid lexeme without stopping execution.

    First line of output follows grading format:

    Cooke Analyzer :: R11792077

    Compatible with GNU C/C++ 10.2.0.

Example Usage

./cooke_analyzer test_file.dc

Example Output

Cooke Analyzer :: RNUMBER
Lexeme: f     Token: IDENT
Lexeme: :=    Token: ASSIGN_OP
Lexeme: 15    Token: INT_LIT
Lexeme: ;     Token: SEMICOLON

Project 2 – Syntax Analyzer
Purpose

The syntax analyzer uses the output from the lexical analyzer to validate grammatical correctness of the Cooke source code using recursive descent parsing.
Key Features

    Parses tokens according to BNF grammar rules.

    Detects syntax errors and provides meaningful error messages.

    Handles branching (if-else), loops, arithmetic expressions, and nested structures.

    Ensures proper handling of identifiers (V) and integer literals (N).

The Cooke Programming Language

The language’s syntax is defined using Backus–Naur Form (BNF) rules, supporting:

    Variable assignments (V := E)

    Input/Output operations (read(V), print(E))

    Increment/Decrement operators (++V, --V)

    Conditional statements (if / else)

    Arithmetic operators (+, -, *, /, **)

    Comparison operators (<, >, =, <>, <=, >=)

Example Source Code

read(x);
if x < 10:
begin
    print(x);
end

Requirements

    Language: C or C++

    Compiler: GNU C/C++ 10.2.0

    Platform: HPCC cluster environment

    Makefile included for easy compilation

    Standard library only – no external dependencies

Repository Structure

├── cooke_analyzer.c           # Lexical Analyzer source
├── cooke_parser.c             # Syntax Analyzer source
├── cooke.h                    # Shared headers / token definitions
├── Makefile                   # Build instructions
├── sample_program.dc          # Example Cooke language file
└── README.md

Educational Outcomes

By completing these projects, you will:

    Understand tokenization and parsing in compiler design.

    Gain experience with recursive descent parsing.

    Learn robust error handling for compiler front-ends.

    Connect theory with practical implementation.

Author

Dakota Hawkins
CS3361 – Spring 2025 – Texas Tech University
