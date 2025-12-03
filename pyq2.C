%{
#include <stdio.h>
#include <string.h>

int word_count = 0;
int line_count = 0;
int char_count = 0;
int small_count = 0;
int capital_count = 0;
int special_count = 0;
int aabb_count = 0;
%}

%%

// Count words
[a-zA-Z]+ {
    word_count++;

    // Check if word starts with aa and ends with bb
    int len = strlen(yytext);
    if(len >= 4 &&
       yytext[0]=='a' && yytext[1]=='a' &&
       yytext[len-2]=='b' && yytext[len-1]=='b')
        aabb_count++;
}

// Words of type aa...bb (in case teacher wants direct regex)
aa[a-zA-Z]*bb   { aabb_count++; word_count++; }

// Count lines
\n      { line_count++; char_count++; }

// Count small letters
[a-z]   { small_count++; char_count++; }

// Count capital letters
[A-Z]   { capital_count++; char_count++; }

// Count special characters
[^a-zA-Z0-9\n ]  { special_count++; char_count++; }

// Count space
[ ]     { char_count++; }

// Count digits as characters
[0-9]   { char_count++; }

// Ignore tabs
[\t]    { char_count++; }

// Everything else (catch-all)
.       { char_count++; }

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) {
        printf("Error opening input.txt\n");
        return 1;
    }

    yylex();
    fclose(yyin);

    printf("\n----- FINAL RESULT -----\n");
    printf("Total Words                : %d\n", word_count);
    printf("Total Lines                : %d\n", line_count);
    printf("Total Characters           : %d\n", char_count);
    printf("Small Letters              : %d\n", small_count);
    printf("Capital Letters            : %d\n", capital_count);
    printf("Special Characters         : %d\n", special_count);
    printf("Strings starting with aa and ending with bb : %d\n", aabb_count);

    return 0;
}

int yywrap() { return 1; }
