

%{
#include <stdio.h>
#include <string.h>

int total_words = 0;
int same_start_end = 0;
int three_vowels = 0;
int repeating_char = 0;

int countVowel(char *s) {
    int c = 0;
    for(int i=0; s[i]; i++)
        if(strchr("aeiouAEIOU", s[i])) c++;
    return c;
}

int hasRepeat(char *s) {
    int freq[256] = {0};
    for(int i=0; s[i]; i++) {
        if(freq[(unsigned char)s[i]]++) return 1;
    }
    return 0;
}
%}

%%

[a-zA-Z]+ {
    total_words++;
    int len = strlen(yytext);

    // start and end with same letter
    if(tolower(yytext[0]) == tolower(yytext[len-1]))
        same_start_end++;

    // exactly 3 vowels
    if(countVowel(yytext) == 3)
        three_vowels++;

    // repeating characters
    if(hasRepeat(yytext))
        repeating_char++;
}

[ \t\n]+    ;  
.           ;

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) { printf("Error opening file\n"); return 1; }

    yylex();
    fclose(yyin);

    printf("\n--- RESULT ---\n");
    printf("Total Words                        : %d\n", total_words);
    printf("Words with same start & end letter : %d\n", same_start_end);
    printf("Words with exactly 3 vowels        : %d\n", three_vowels);
    printf("Words with repeating characters    : %d\n", repeating_char);

    return 0;
}

int yywrap() { return 1; }
