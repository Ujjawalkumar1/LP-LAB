⭐ 2️⃣ YACC PROGRAM – Validate Assignment Statements
Allowed assignments:
a = b;
x = 5;
value = total;
count = 10;

Not allowed:
= a;
a = ;
10 = x;
a == b;


//=========================================================================================

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

/* identifier */
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

/* number */
[0-9]+                   { return NUM; }

/* operators */
"="                      { return ASSIGN; }
";"                      { return SEMI; }

/* ignore spaces */
[ \t\n]+                 ;

// invalid characters
.                        { return yytext[0]; }

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
%token ID NUM ASSIGN SEMI

%%

/* Start rule: assignment must end with ; */
S : ID ASSIGN Rvalue SEMI
    {
        printf("Valid assignment statement\n");
    }
  ;

/* Right side can be identifier or number */
Rvalue : ID
       | NUM
       ;

%%

int main() {
    printf("Enter an assignment statement:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid assignment\n");
    return 0;
}


//=========================================================================================






//=========================================================================================