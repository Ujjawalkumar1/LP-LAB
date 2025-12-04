%{
#include "y.tab.h"    // token definitions from YACC
%}

%%

// Keywords
"if"            { return IF; }
"else"          { return ELSE; }

// Relational operators
"=="            { return EQ; }
"!="            { return NE; }
">="            { return GE; }
"<="            { return LE; }
">"             { return GT; }
"<"             { return LT; }

// Identifier rule (variable names)
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

// Numbers
[0-9]+         { yylval = atoi(yytext); return NUM; }

// Symbols
"="            { return ASSIGN; }
";"            { return SEMI; }
"("            { return LP; }
")"            { return RP; }

// Ignore whitespace
[ \t\n]+       ;

// Catch other characters → return as is (may cause syntax error)
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
%token IF ELSE
%token ID NUM
%token EQ NE GE LE GT LT
%token ASSIGN SEMI LP RP

%%

// Start rule: an IF statement must reduce to S
S : IF LP C RP Stmt              { printf("Valid IF statement\n"); }
  | IF LP C RP Stmt ELSE Stmt    { printf("Valid IF-ELSE statement\n"); }
  ;

// Condition rule
C : ID RelOp ID
  | ID RelOp NUM
  | NUM RelOp ID
  ;

// Relational operator rule
RelOp : EQ | NE | GT | LT | GE | LE ;

// Statement rule
Stmt : ID ASSIGN ID SEMI
     | ID ASSIGN NUM SEMI
     ;

%%

// main() function
int main() {
    printf("Enter IF/IF-ELSE statement:\n");
    yyparse();      // start parsing
    return 0;
}

// yyerror() called when syntax fails
int yyerror(char *s) {
    printf("Invalid IF statement\n");
    return 0;
}





//=========================================================================================

valid=>

if(a<5) a=10;
if(x==10) y=3;
if(a>5) b=3; else c=2;
if(a<3) if(b!=2) x=1; else y=4;





//=========================================================================================






//=========================================================================================