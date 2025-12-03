%{
#include <stdio.h>
#include <string.h>

int total_words = 0;
int words_with_vowel2 = 0;
int words_len_gt5 = 0;
int words_no_vowel = 0;
int line_count = 0;

// Function to count vowels in a word
int countVowel(char *s) {
    int c = 0;
    for(int i=0; s[i]; i++) {
        if(strchr("aeiouAEIOU", s[i])) c++;
    }
    return c;
}
%}

%%

// WORD pattern
[a-zA-Z]+ {
    total_words++;

    int v = countVowel(yytext);
    int len = strlen(yytext);

    if(v > 2) words_with_vowel2++;
    if(len > 5) words_len_gt5++;
    if(v == 0) words_no_vowel++;
}

// Count lines
\n      { line_count++; }

// Ignore spaces, tabs, punctuation
[ \t]+  ;
.       ;

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) {
        printf("Error opening input.txt\n");
        return 1;
    }

    yylex();
    fclose(yyin);

    printf("\n--- FINAL RESULTS ---\n");
    printf("Total Words                : %d\n", total_words);
    printf("Words with vowel > 2       : %d\n", words_with_vowel2);
    printf("Words length > 5           : %d\n", words_len_gt5);
    printf("Words with NO vowel        : %d\n", words_no_vowel);
    printf("Total Lines                : %d\n", line_count);

    return 0;
}

int yywrap() { return 1; }
