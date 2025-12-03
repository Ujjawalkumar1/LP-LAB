%{
#include <stdio.h>
%}

%%

// Valid Email Pattern
^[a-zA-Z0-9_.]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,3}$   {
                                                printf("Valid Email\n");
                                              }

// If anything else → invalid
.*                                          { printf("Invalid Email\n"); }

%%

int main() {
    printf("Enter email: ");
    yylex();
    return 0;
}

int yywrap() { return 1; }
