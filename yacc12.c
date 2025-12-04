
4️⃣ YACC Program – Validate Array Declaration
🎯 We will accept:
int a[10];
float arr[5];
char ch[1];
int x[10], y[20];

//=========================================================================================

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

/* Data types */
"int"           { return INT; }
"float"         { return FLOAT; }
"char"          { return CHAR; }

/* Identifier */
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

/* Number (array size) */
[0-9]+         { return NUM; }

/* Symbols */
"["            { return LSB; }   // left square bracket
"]"            { return RSB; }   // right square bracket
","            { return COMMA; }
";"            { return SEMI; }

/* Ignore spaces */
[ \t\n]+       ;

// Any other character
.              { return yytext[0]; }

%%

int yywrap() { return 1; }





//=========================================================================================
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *s);
%}

/* Tokens */
%token INT FLOAT CHAR
%token ID NUM
%token LSB RSB COMMA SEMI

%%

/* Start rule: Type followed by one or more array declarations and ; */
S : Type ArrList SEMI
    {
        printf("Valid array declaration\n");
    }
  ;

/* Type: int, float, char */
Type : INT
     | FLOAT
     | CHAR
     ;

/* One or more array declarations separated by comma */
ArrList : ArrDecl
        | ArrList COMMA ArrDecl
        ;

/* Single array declaration: ID[NUM] */
ArrDecl : ID LSB NUM RSB
        ;

%%

int main() {
    printf("Enter an array declaration:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid array declaration\n");
    return 0;
}


//=========================================================================================






//=========================================================================================