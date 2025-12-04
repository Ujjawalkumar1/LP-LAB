
5️⃣ YACC – Validate Relational Expression
🎯 Accept things like:
a < b
x >= 10
10 != y
count == max

❌ Reject things like:
a <
< b
a ==== b
10 x < y

//=========================================================================================


%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

/* Relational operators */
"=="        { return EQ; }
"!="        { return NE; }
">="        { return GE; }
"<="        { return LE; }
">"         { return GT; }
"<"         { return LT; }

/* Identifiers: a, x1, total, etc. */
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

/* Numbers */
[0-9]+     { return NUM; }

/* Ignore spaces, tabs, newlines */
[ \t\n]+   ;

/* Any other single character → send as is (will cause error in YACC) */
.          { return yytext[0]; }

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
%token ID NUM
%token EQ NE GT LT GE LE

%%

/* Start symbol: one relational expression */
S : R
    {
        printf("Valid relational expression\n");
    }
  ;

/* R can be: ID op ID, ID op NUM, NUM op ID */
R : ID RelOp ID
  | ID RelOp NUM
  | NUM RelOp ID
  ;

/* All relational operators */
RelOp : EQ
      | NE
      | GT
      | LT
      | GE
      | LE
      ;

%%

int main() {
    printf("Enter a relational expression:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid relational expression\n");
    return 0;
}

//=========================================================================================






//=========================================================================================