#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define KEY_SOM 27
#define KEY_IF 29
#define KEY_READ 30
#define LESSER_OP 31
#define SEMICOLON 33
#define GREATER_OP 32
#define LE_OP 33
#define GE_OP 34
#define COLON 35
#define NE_OP 36
#define DEC_OP 37
#define EOF_TOKEN 38
#define KEY_FI 39
#define NEQUAL_OP 40
#define KEY_WRITE 41
#define KEY_ELSE 42
#define KEY_THEN 43
#define INC_OP 44
#define LEQUAL_OP 45
#define INC_OP 44
#define GEQUAL_OP 46
#define EQUAL_OP 47
#define MOD_OP 48


int lex();

#endif
