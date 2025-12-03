%{
#include <stdio.h>
%}

%%
[a-zA-Z]+    printf("Word: %s\n", yytext);
[0-9]+       printf("Number: %s\n", yytext);
.|\n         ;
%%

int main() {
    yylex();
    return 0;
}




