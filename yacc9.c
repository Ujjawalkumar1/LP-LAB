

Allowed declarations:
int a;
float x;
char c;
int a, b, c;
float x = 10;
int a = b;

Not allowed:
int 1a;
float ;
char a b;
int = 5;
//=========================================================================================

%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"char"          { return CHAR; }

/* identifier */
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

/* numbers */
[0-9]+         { return NUM; }

/* symbols */
","            { return COMMA; }
";"            { return SEMI; }
"="            { return ASSIGN; }

/* ignore spaces */
[ \t\n]+       ;

// return any other character (may cause error)
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
%token INT FLOAT CHAR
%token ID NUM
%token ASSIGN COMMA SEMI

%%

/* Start rule: Declaration must end with ; */
S : Type DeclList SEMI
    {
        printf("Valid declaration\n");
    }
  ;

/* Type rule */
Type : INT
     | FLOAT
     | CHAR
     ;

/* List of one or more declarations */
DeclList : Decl
         | DeclList COMMA Decl
         ;

/* Single declaration: ID OR ID=NUM OR ID=ID */
Decl : ID
     | ID ASSIGN NUM
     | ID ASSIGN ID
     ;

%%

int main() {
    printf("Enter a declaration:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Invalid declaration\n");
    return 0;
}

//=========================================================================================






//=========================================================================================