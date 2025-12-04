
6️⃣ YACC – Validate do…while Loop
🎯 Accept loops like:
do x = 5; while(a<10);
do count = count; while(count != 0);
do i = i; while(i>=1);


We’ll use simplified syntax:

do  Stmt  while ( Cond );


Where:

Stmt → ID = ID; or ID = NUM;

Cond → relational expression like a<10, x!=0, num>=1

//=========================================================================================

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

/* Keywords */
"do"            { return DO; }
"while"         { return WHILE; }

/* Relational operators */
"=="            { return EQ; }
"!="            { return NE; }
">="            { return GE; }
"<="            { return LE; }
">"             { return GT; }
"<"             { return LT; }

/* Identifier */
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

/* Number */
[0-9]+         { return NUM; }

/* Symbols */
"="            { return ASSIGN; }
";"            { return SEMI; }
"("            { return LP; }
")"            { return RP; }

/* Ignore spaces, tabs, newlines */
[ \t\n]+       ;

/* Any other character */
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
%token DO WHILE
%token ID NUM
%token EQ NE GT LT GE LE
%token ASSIGN SEMI LP RP

%%

/* Start rule: do Stmt while ( Cond ); */
S : DO Stmt WHILE LP Cond RP SEMI
    {
        printf("Valid do-while statement\n");
    }
  ;

/* Simple assignment statement:
   ID = NUM;  OR  ID = ID; */
Stmt : ID ASSIGN NUM SEMI
     | ID ASSIGN ID SEMI
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

%%

int main() {
    printf("Enter a do-while statement:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid do-while statement\n");
    return 0;
}






//=========================================================================================






//=========================================================================================