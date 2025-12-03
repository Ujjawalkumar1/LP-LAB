%{
#include <stdio.h>
#include <string.h>

int id_count = 0, assign_count = 0, relop_count = 0;
int keyword_count = 0, int_count = 0, stmt_count = 0;

// List of C keywords
char *keywords[] = {
    "int","float","char","if","else","for","while","return","void",
    "break","continue","switch","case","default","do","static","const"
};
int n = 16;  // number of keywords

int isKeyword(char *word) {
    for(int i=0; i<n; i++) {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%%
";"                { stmt_count++; }                             // count statements
"="                { assign_count++; }                           // assignment operator
"=="|"<="|">="|"<"|">"|"!=" { relop_count++; }                   // relational operators
[0-9]+             { int_count++; }                              // integers
[a-zA-Z_][a-zA-Z0-9_]* {
                        if(isKeyword(yytext))
                            keyword_count++;
                        else
                            id_count++;
                    }
[ \t\n]+           ;                                             // ignore spaces, tabs, newlines
.                  ;                                             // ignore others
%%

int main() {
    yyin = fopen("input.c", "r");  // read from file input.c
    if(!yyin) {
        printf("Error: cannot open input.c\n");
        return 1;
    }
    yylex();  // start lexical analysis
    fclose(yyin);

    printf("\n----- FINAL OUTPUT -----\n");
    printf("Statements: %d\n", stmt_count);
    printf("Identifiers: %d\n", id_count);
    printf("Assignment Operators: %d\n", assign_count);
    printf("Relational Operators: %d\n", relop_count);
    printf("Keywords: %d\n", keyword_count);
    printf("Integers: %d\n", int_count);
    return 0;
}

int yywrap() {
    return 1;
}
