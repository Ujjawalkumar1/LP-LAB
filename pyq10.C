

%{
#include <stdio.h>
#include <string.h>

int id_count = 0, key_count = 0, op_count = 0;
int num_count = 0, line_count = 0;

char *keywords[] = {"int","float","char","if","else","for","while","return"};
int n = 8;

int isKeyword(char *s) {
    for(int i=0; i<n; i++)
        if(strcmp(s, keywords[i]) == 0)
            return 1;
    return 0;
}
%}

%%

// Keywords / Identifiers
[a-zA-Z_][a-zA-Z0-9_]* {
    if(isKeyword(yytext))
        key_count++;
    else
        id_count++;
}

// Numbers
[0-9]+      { num_count++; }

// Operators
[+\-*/=]    { op_count++; }

// Count lines
\n          { line_count++; }

// Ignore spaces
[ \t]+      ;

// Ignore everything else
.           ;

%%

int main() {
    yyin = fopen("input.c", "r");
    if(!yyin) { printf("Error opening file\n"); return 1; }

    yylex();
    fclose(yyin);

    printf("\n----- RESULT -----\n");
    printf("Identifiers : %d\n", id_count);
    printf("Keywords    : %d\n", key_count);
    printf("Operators   : %d\n", op_count);
    printf("Numbers     : %d\n", num_count);
    printf("Lines       : %d\n", line_count);

    return 0;
}

int yywrap() { return 1; }
