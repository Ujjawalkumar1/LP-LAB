
3️⃣ YACC Program – Validate while Loop
🎯 We will accept:
while(a<5) x=3;
while(x!=0) y = 10;
while(num >= 1) count = count;


Syntax pattern:

while ( condition ) statement;

//=========================================================================================

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

// Keyword
"while"         { return WHILE; }

// Relational operators
"=="            { return EQ; }
"!="            { return NE; }
">="            { return GE; }
"<="            { return LE; }
">"             { return GT; }
"<"             { return LT; }

// Identifiers
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

// Numbers
[0-9]+         { return NUM; }

// Symbols
"("            { return LP; }
")"            { return RP; }
"="            { return ASSIGN; }
";"            { return SEMI; }

// Ignore spaces, tabs, newlines
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

/* Tokens from Lex */
%token WHILE
%token ID NUM
%token EQ NE GT LT GE LE
%token LP RP ASSIGN SEMI

%%

/* Start rule: while ( Cond ) Stmt; */
S : WHILE LP Cond RP Stmt
    {
        printf("Valid while statement\n");
    }
  ;

/* Condition: relational expression */
Cond : ID RelOp ID
     | ID RelOp NUM
     | NUM RelOp ID
     ;

/* Relational operators */
RelOp : EQ
      | NE
      | GT
      | LT
      | GE
      | LE
      ;

/* Simple assignment statement: ID = NUM; or ID = ID; */
Stmt : ID ASSIGN NUM SEMI
     | ID ASSIGN ID SEMI
     ;

%%

int main() {
    printf("Enter a while statement:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid while statement\n");
    return 0;
}





//=========================================================================================






//=========================================================================================