

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "front.h"
#include "parser.h"
#define KEY_BEGIN 55
#define KEY_END 56
#define KEY_PRINT 57
#define POW_OP 58
/* Global Variable */
int nextToken;
/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();



int isKeyword(const char *lexeme) {
    // List of keywords
    const char *keywords[] = {"if", "else", "int", "print", "read", "fi", "begin", "end" };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    int i;
    for (i = 0; i < numKeywords; ++i) {
        if (strcmp(lexeme, keywords[i]) == 0) {
            return KEY_SOM; // Return token code for keyword
        }
    }
    return IDENT; // Not a keyword, treat as an identifier
}

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) 
{
   if(argc !=2) {
    printf("Usage: %s <input_file>\n", argv[0]);
    return 1;
   }
   if ((in_fp = fopen(argv[1], "r")) == NULL){
    printf("ERROR - cannot open %s\n", argv[1]);
    return 1;
   } else {
       printf("Cooke Analyzer :: R11792077\n\n");
        getChar();
        do {
            lex();
        
        } while (nextToken != EOF);
   }
   fclose(in_fp);
   return 0;
}
   
    /* Open the input data file and process its contents */
   /* if ((in_fp = fopen("front.in", "r")) == NULL) {
        printf("ERROR - cannot open front.in \n");
    } else {
        getChar();
        do {
            lex();
            expr();
        } while (nextToken != EOF);
    }

    return 0;*/


/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static int lookup(char ch) {
    switch (ch) {
         case '>':
            addChar();
        
            nextToken = UNKNOWN;
            
            //printf("UNKNOWN!!  ");
            
            break;
         case'<':
            addChar();
            nextToken = LESSER_OP;
            //printf("UNKNOWN ");
            break;
         case ';':
            addChar();
            nextToken = SEMICOLON;
            //printf("Unknown  ");
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            //printf("UKNOWN  ");
            break;
        case ':':
            addChar();
            nextToken = COLON;
            break;
            //printf("Unknown  ");
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            //printf("LEFT_PAREN  ");
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            //printf("RIGHT_PAREN  ");
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            //printf("ADD_OP  ");
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            //printf("SUB_OP  ");
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            //printf("MULT_OP  ");
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            //printf("DIV_OP  ");
            break;
        case '%':
            addChar();
            nextToken = MOD_OP;
            //printf("DIV_OP  ");
            break;
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    
    return nextToken;

}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */




/* Main lexical analyzer function */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers and keywords */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            if (strcmp(lexeme, "if") == 0) {
                nextToken = KEY_IF;
            } else if (strcmp(lexeme, "read") == 0) {
                nextToken = KEY_READ;
            } else if (strcmp(lexeme, "write") == 0) {
                nextToken = KEY_WRITE;
            } else if (strcmp(lexeme, "else") == 0) {
                nextToken = KEY_ELSE;
            } else if (strcmp(lexeme, "then") == 0) {
                nextToken = KEY_THEN;
            } else if (strcmp(lexeme, "end") == 0) {
                nextToken = KEY_END;
            } else if (strcmp(lexeme, "print") == 0) {
                nextToken = KEY_PRINT;
            } else if (strcmp(lexeme, "fi") == 0) {
                nextToken = KEY_FI;
            } else if (strcmp(lexeme, "V") == 0) {
                nextToken = IDENT;
            } else if (strcmp(lexeme, "N") == 0) {
                nextToken = INT_LIT;
            } else if (strcmp(lexeme, "begin") == 0) {
                nextToken = KEY_BEGIN;
            } else {
                nextToken = IDENT;
            }
            break;
        
        /* Parse integer literals */
        case DIGIT:
            addChar(); // Add the first digit
            getChar();
            while (charClass == DIGIT) {
            addChar(); // Add subsequent digits
            getChar();
        }
        nextToken = INT_LIT;
        break;


        /* Operators and other characters */
        case UNKNOWN:
            switch (nextChar) {
                case ':':
                    addChar();
                    getChar();
                    if (nextChar == '=') {
                        addChar(); // Add '=' to lexeme
                        nextToken = ASSIGN_OP;
                        getChar(); // Move to the next character after '='
                    } else {
                        nextToken = COLON;
                    }
                    break;
                case '>':
                    addChar();
                    getChar();
                    if (nextChar == '=') {
                        addChar(); // Add '=' to lexeme
                        nextToken = GEQUAL_OP;
                        getChar(); // Move to the next character after '='
                    } else {
                        nextToken = GREATER_OP;
                    }
                    break;
                case '<':
                    addChar();
                    getChar();
                    if (nextChar == '>') {
                        addChar(); // Add '=' to lexeme
                        nextToken = NEQUAL_OP;
                        getChar(); // Move to the next character after '='
                    } else if (nextChar == '=') {
                        addChar(); // Add '=' to lexeme
                        nextToken = LEQUAL_OP;
                        getChar(); // Move to the next character after '='
                    } else {
                        nextToken = LESSER_OP;
                    }
                    break;
                case '*':
                    addChar();
                    getChar();
                    if (nextChar == '*') {
                        addChar(); // Add the second '-' to the lexeme
                        nextToken = POW_OP; // Decrement operator token
                        getChar(); // Move to the next character after '--'
                    } else {
                        nextToken = MULT_OP; // Unknown token
                    }
                    break;
                case '+':
                    addChar();
                    getChar();
                    if (nextChar == '+') {
                        addChar(); // Add the second '-' to the lexeme
                        nextToken = INC_OP; // Decrement operator token
                        getChar(); // Move to the next character after '--'
                    } else {
                        nextToken = ADD_OP; // Unknown token
                    }
                    break;
                case '-':
                    addChar();
                    getChar();
                    if (nextChar == '-') {
                        addChar(); // Add the second '-' to the lexeme
                        nextToken = DEC_OP; // Decrement operator token
                        getChar(); // Move to the next character after '--'
                    } else {
                        nextToken = SUB_OP; // Unknown token
                    }
                    break;
                default:
                    nextToken = lookup(nextChar);
                    getChar();
                    break;
            }
            break;

        /* Parentheses */
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            getChar(); // Move to the next character after '('
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            getChar(); // Move to the next character after ')'
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 0;
            
            break;
    }

    printf("%s ", lexeme);
    switch (nextToken) {
        case IDENT:
            printf("\tIDENT\n");
            break;
        case LEQUAL_OP:
            printf("\tLEQUAL_OP\n");
            break;
        case GEQUAL_OP:
            printf("\tGEQUAL_OP\n");
            break;
        case INT_LIT:
            printf("\tINT_LIT\n");
            break;
        case ASSIGN_OP:
            printf("\tASSIGN_OP\n");
            break;
        case KEY_IF:
            printf("\tKEY_IF\n");
            break;
        case KEY_FI:
            printf("\tKEY_FI\n");
            break;
        case KEY_READ:
            printf("\tKEY_READ\n");
            break;
        case KEY_WRITE:
            printf("\tKEY_WRITE\n");
            break;
        case LEFT_PAREN:
            printf("\tLEFT_PAREN\n");
            break;
        case RIGHT_PAREN:
            printf("\tRIGHT_PAREN\n");
            break;
        case GREATER_OP:
            printf("\tGREATER_OP\n");
            break;
        case DEC_OP:
            printf("\tDEC_OP\n");
            break;
        case LESSER_OP:
            printf("\tLESSER_OP\n");
            break;
        case UNKNOWN:
            printf("\tUNKNOWN\n");
            break;
        case SEMICOLON:
            printf("\tSEMICOLON\n");
            break;
        case POW_OP:
            printf("\tPOW_OP\n");
            break;
        case EOF:
            //printf("\tEOF\n");
            break;
        case COLON:
            printf("\tCOLON\n");
            break;
        case ADD_OP:
            printf("\tADD_OP\n");
            break;
        case NEQUAL_OP:
            printf("\tNEQUAL_OP\n");
            break;
        case KEY_END:
            printf("\tKEY_END\n");
            break;
        case KEY_ELSE:
            printf("\tKEY_ELSE\n");
            break;
        case KEY_THEN:
            printf("\tKEY_THEN\n");
            break;
        case MULT_OP:
            printf("\tMULT_OP\n");
            break;
        case DIV_OP:
            printf("\tDIV_OP\n");
            break;
        case EQUAL_OP:
            printf("\tEQUAL_OP\n");
            break;
        case INC_OP:
            printf("\tINC_OP\n");
            break;
        case SUB_OP:
            printf("\tSUB_OP\n");
            break;
        case MOD_OP:
            printf("\tMOD_OP\n");
            break;
        case KEY_BEGIN:
            printf("\tKEY_BEGIN\n");
            break;
        case KEY_PRINT:
            printf("\tKEY_PRINT\n");
            break;
        default:
            break;
    }

    return 0;
}
