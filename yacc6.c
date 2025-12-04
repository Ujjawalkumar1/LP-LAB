
%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"     // token definitions from YACC
%}

%%

// Keywords
"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"break"         { return BREAK; }

// Identifiers (variable names)
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

// Numbers
[0-9]+         { return NUM; }

// Symbols
"("            { return LP; }
")"            { return RP; }
"{"            { return LBR; }
"}"            { return RBR; }
":"            { return COLON; }
";"            { return SEMI; }
"="            { return ASSIGN; }

// Ignore spaces, tabs, newlines
[ \t\n]+       ;

// Any other character is invalid – return it as is (may cause error in YACC)
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

// Tokens from Lex
%token SWITCH CASE DEFAULT BREAK
%token ID NUM
%token LP RP LBR RBR COLON SEMI ASSIGN

%%

// Start rule: a valid switch statement
S : SWITCH LP ID RP LBR CaseList OptDefault RBR
    {
        printf("Valid switch statement\n");
    }
  ;

// CaseList: one or more case blocks
CaseList : CaseList CaseBlock
         | CaseBlock
         ;

// One case block:  case NUM: ID = NUM; break;
CaseBlock : CASE NUM COLON Stmt BREAK SEMI
          ;

// Default part is optional
OptDefault : DEFAULT COLON Stmt
           | /* empty */
           ;

// Simple statement:  ID = NUM;  OR  ID = ID;
Stmt : ID ASSIGN NUM SEMI
     | ID ASSIGN ID SEMI
     ;

%%

int main() {
    printf("Enter a switch statement:\n");
    yyparse();   // start parsing
    return 0;
}

// Called when syntax does NOT match grammar
int yyerror(char *s) {
    printf("Invalid switch statement\n");
    return 0;
}









//=========================================================================================

Start Rule:
S : SWITCH LP ID RP LBR CaseList OptDefault RBR


This matches:

switch ( ID ) { CaseList OptDefault }


Example:

switch(x) {
    case 1: ...
    default: ...
}





//=========================================================================================



switch(x){
case 1: a = 10; break;
case 2: a = 20; break;
default: a = 0;
}



//=========================================================================================