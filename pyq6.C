

%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int total_words = 0, upper_words = 0, lower_words = 0;
int start_vowel = 0, end_consonant = 0;

int isVowel(char c) {
    return strchr("aeiouAEIOU", c) != NULL;
}
%}

%%

[a-zA-Z]+ {
    total_words++;
    int len = strlen(yytext);

    // Uppercase word
    if(isupper(yytext[0]))
        upper_words++;

    // Lowercase word
    if(islower(yytext[0]))
        lower_words++;

    // Word starting with vowel
    if(isVowel(yytext[0]))
        start_vowel++;

    // Word ending with consonant
    if(!isVowel(yytext[len-1]))
        end_consonant++;
}

[ \t\n]+    ;    // ignore spaces
.           ;    // ignore punctuation

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) { printf("Error opening file\n"); return 1; }

    yylex();
    fclose(yyin);

    printf("\n--- RESULT ---\n");
    printf("Total Words               : %d\n", total_words);
    printf("Uppercase Words           : %d\n", upper_words);
    printf("Lowercase Words           : %d\n", lower_words);
    printf("Words Starting with Vowel : %d\n", start_vowel);
    printf("Words Ending with Consonant: %d\n", end_consonant);

    return 0;
}

int yywrap() { return 1; }
