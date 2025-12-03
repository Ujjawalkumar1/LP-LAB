

%{
#include <stdio.h>
int removed = 0;
%}

%%

// Digits → remove them (do not print)
[0-9]      { removed++; }

// Print everything else
.|\n       { printf("%s", yytext); }

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) { printf("Error opening file\n"); return 1; }

    printf("Modified Output:\n");
    yylex();
    fclose(yyin);

    printf("\nTotal Digits Removed = %d\n", removed);

    return 0;
}

int yywrap() { return 1; }
