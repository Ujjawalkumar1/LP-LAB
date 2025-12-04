%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"   // token definitions from YACC
%}

%%

// Keyword
"for"           { return FOR; }

// Relational operators
"=="            { return EQ; }
"!="            { return NE; }
">="            { return GE; }
"<="            { return LE; }
">"             { return GT; }
"<"             { return LT; }

// Increment / Decrement
"++"            { return INC; }
"--"            { return DEC; }

// Identifier: variable names like i, count, x1, etc.
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

// Numbers
[0-9]+         { yylval = atoi(yytext); return NUM; }

// Symbols
"="            { return ASSIGN; }
";"            { return SEMI; }
"("            { return LP; }
")"            { return RP; }

// Ignore spaces, tabs, newlines
[ \t\n]+       ;

// Any other character → return as itself (may cause error)
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
%token FOR
%token ID NUM
%token EQ NE GE LE GT LT
%token INC DEC
%token ASSIGN SEMI LP RP

%%

// Start symbol: a For-loop must match this rule
S : FOR LP Init SEMI Cond SEMI Incr RP Stmt
    {
        printf("Valid for loop statement\n");
    }
  ;

// Initialization part: i = 0; or i = j;
Init : ID ASSIGN NUM
     | ID ASSIGN ID
     ;

// Condition part: i < 10, i <= j, 5 >= i etc.
Cond : ID RelOp ID
     | ID RelOp NUM
     | NUM RelOp ID
     ;

// Relational operator
RelOp : EQ | NE | GT | LT | GE | LE ;

// Increment part: i++ or i--
Incr : ID INC
     | ID DEC
     ;

// Statement after for-loop header
// Example: i = i + 1;  (here simplified as assignment only)
Stmt : ID ASSIGN ID SEMI
     | ID ASSIGN NUM SEMI
     ;

%%

int main() {
    printf("Enter a for-loop statement:\n");
    yyparse();   // start parsing
    return 0;
}

// Called when syntax does not match grammar
int yyerror(char *s) {
    printf("Invalid for loop statement\n");
    return 0;
}







//=========================================================================================


🧠 Explanation of Grammar (Plain English)
S : FOR LP Init SEMI Cond SEMI Incr RP Stmt


This matches:

for (   Init   ;    Cond    ;   Incr   )   Stmt


Example:

for(i=0; i<10; i++)  i = i + 1;



//=========================================================================================






//=========================================================================================