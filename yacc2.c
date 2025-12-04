%{
#include "y.tab.h"   // to get token definitions: ID, PLUS, MINUS
%}

%%

// Single alphabet (a, b, c, ...)
[a-zA-Z]        { return ID; }

// '+' symbol
\+              { return PLUS; }

// '-' symbol
\-              { return MINUS; }

// ignore spaces, tabs, newlines
[ \t\n]         ;

// any other single character → return it as its ASCII value
.               return yytext[0];

%%

// tells Lex there is no more input file
int yywrap() { return 1; }


//=========================================================================================

%{
#include <stdio.h>
%}

%token ID PLUS MINUS   // tokens from Lex

%%

// S is the start symbol
S : E  { printf("Valid expression\n"); }
  ;

E : E PLUS E
  | E MINUS E
  | ID
  ;

%%

int main() {
    printf("Enter expression: ");
    yyparse();                  // start parsing
    return 0;
}

int yyerror(char *msg) {
    printf("Invalid expression\n");
    return 0;
}





//=========================================================================================




//=========================================================================================






//=========================================================================================