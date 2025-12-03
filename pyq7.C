

%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int digit_count = 0, number_count = 0;
int alphabet_count = 0, special_count = 0;
int alnum_strings = 0;
%}

%%

// multi-digit number
[0-9]+        { number_count++; digit_count += strlen(yytext); }

// alphabets only
[a-zA-Z]+     { alphabet_count += strlen(yytext); }

// alphanumeric strings
[a-zA-Z0-9]+  { alnum_strings++; }

// special characters
[^a-zA-Z0-9 \n\t]   { special_count++; }

// newlines/spaces ignored
[ \t\n]+      ;

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) { printf("Error opening file\n"); return 1; }

    yylex();
    fclose(yyin);

    printf("\n--- RESULT ---\n");
    printf("Digits Count              : %d\n", digit_count);
    printf("Number Count              : %d\n", number_count);
    printf("Alphabet Count            : %d\n", alphabet_count);
    printf("Special Characters Count  : %d\n", special_count);
    printf("Alphanumeric Strings      : %d\n", alnum_strings);

    return 0;
}

int yywrap() { return 1; }
