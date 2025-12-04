%{
#include "y.tab.h"
%}

%%

[0-9]+     { yylval = atoi(yytext); return NUMBER; }
"if"       { return IF; }
"else"     { return ELSE; }
[a-zA-Z]+  { return ID; }
"=="       { return EQ; }
">"        { return GT; }
"<"        { return LT; }
"+"        { return '+'; }
"-"        { return '-'; }
"*"        { return '*'; }
"/"        { return '/'; }
"("        { return '('; }
")"        { return ')'; }

[ \t\n]    ;
.          { return yytext[0]; }

%%

int yywrap() { return 1; }








//=========================================================================================


%{
#include <stdio.h>
#include <stdlib.h>

int flag = 0;  // 0 = valid, 1 = error
%}

%token NUMBER ID IF ELSE EQ GT LT

%%

S : E { printf("Valid\n"); }
  ;

E : E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | '(' E ')'
  | NUMBER
  ;

%%

int main() {
    printf("Enter expression:\n");
    yyparse();
    return 0;
}

int yyerror() {
    printf("Invalid\n");
    exit(0);
}



//=========================================================================================

yacc -d file.y
lex file.l
gcc y.tab.c lex.yy.c -o output -ll
./output





//=========================================================================================


🔵 STEP 5 – Understanding $$, $1, $2, etc.

These are used to compute values, not just check syntax.

Example:

E : E '+' E { $$ = $1 + $3; }
  | NUMBER  { $$ = $1; }
  ;





//=========================================================================================

🔵 STEP 6 – Operator precedence: %left, %right, %nonassoc

These lines:

%left '+' '-'
%left '*' '/'