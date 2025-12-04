

//=========================================================================================

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"   // token definitions from YACC
%}

%%

/* Data types */
"int"           { return INT; }
"float"         { return FLOAT; }
"char"          { return CHAR; }
"void"          { return VOID; }

/* Identifier: function name or parameter name */
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

/* Symbols */
"("             { return LP; }
")"             { return RP; }
"{"             { return LBR; }
"}"             { return RBR; }
","             { return COMMA; }

/* Ignore spaces, tabs, newlines */
[ \t\n]+        ;

/* Any other character – pass it as is (may cause parse error) */
.               { return yytext[0]; }

%%

int yywrap() { return 1; }




//=========================================================================================


%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *s);
%}

/* Tokens from Lex */
%token INT FLOAT CHAR VOID
%token ID
%token LP RP LBR RBR COMMA

%%

/* Start rule: Complete function definition */
S : Type ID LP ParamOpt RP LBR RBR
    {
        printf("Valid function definition\n");
    }
  ;

/* Type of function: int, float, char, void */
Type : INT
     | FLOAT
     | CHAR
     | VOID
     ;

/* Parameters are optional: either some params or empty */
ParamOpt : ParamList
         | /* empty */
         ;

/* ParamList: one or more parameters separated by comma */
ParamList : Param
          | ParamList COMMA Param
          ;

/* One parameter: type + identifier */
Param : Type ID
      ;

%%

int main() {
    printf("Enter a function definition:\n");
    yyparse();    // start parsing
    return 0;
}

/* Called when input doesn't match grammar */
int yyerror(char *s) {
    printf("Invalid function definition\n");
    return 0;
}










//=========================================================================================






//=========================================================================================