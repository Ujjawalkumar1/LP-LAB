
a < b && b != 0
x == 10 || y > 5
!(a >= 5 && b < 3)



//=========================================================================================


%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"     // token definitions from YACC
%}

%%

/* Logical operators */
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }

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

/* Parentheses */
"("        { return LP; }
")"        { return RP; }

/* Ignore spaces, tabs, newlines */
[ \t\n]+   ;

/* Any other character → return as is (causes parse error) */
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

/* Tokens coming from Lex */
%token ID NUM
%token AND OR NOT
%token EQ NE GT LT GE LE
%token LP RP

/* Precedence and associativity (optional but nice) */
%right NOT
%left AND
%left OR

%%

/* Start symbol: complete logical expression */
S : E
    {
        printf("Valid logical expression\n");
    }
  ;

/* Logical expression rules */
E : E OR E        /* E || E */
  | E AND E       /* E && E */
  | NOT E         /* !E */
  | LP E RP       /* (E) */
  | R             /* relational expression */
  ;

/* Relational expression rules:
   a < b, a >= 5, 10 == x, etc. */
R : ID RelOp ID
  | ID RelOp NUM
  | NUM RelOp ID
  ;

/* All possible relational operators */
RelOp : EQ
      | NE
      | GT
      | LT
      | GE
      | LE
      ;

%%

int main() {
    printf("Enter a logical expression:\n");
    yyparse();          /* Start parsing */
    return 0;
}

/* Called when parsing fails (syntax error) */
int yyerror(char *s) {
    printf("Invalid logical expression\n");
    return 0;
}




//=========================================================================================


🔹 Expression E
E : E OR E
  | E AND E
  | NOT E
  | LP E RP
  | R
  ;


This means:

E OR E → E || E

E AND E → E && E

NOT E → !E

LP E RP → ( E )

R → relational expression (like a < b)

So you can write things like:

a < b && b != 0

!(x == 10 || y < 5)

(a>5) && (b<=3 || c!=4)

All will reduce to E using these rules.



//=========================================================================================