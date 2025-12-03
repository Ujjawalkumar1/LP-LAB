

%{
#include <stdio.h>
#include <string.h>

int total_words = 0;
int pal_words   = 0;
int len4_words  = 0;
int novowel_words = 0;

int isPalindrome(char *s) {
    int i = 0, j = strlen(s) - 1;
    while(i < j) {
        if(s[i] != s[j]) return 0;
        i++; j--;
    }
    return 1;
}

int hasVowel(char *s) {
    for(int i=0; s[i]; i++) {
        char c = s[i];
        if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
           c=='A'||c=='E'||c=='I'||c=='O'||c=='U')
            return 1;
    }
    return 0;
}
%}

%%

[a-zA-Z]+ {
    total_words++;

    if(isPalindrome(yytext))
        pal_words++;

    if(strlen(yytext) == 4)
        len4_words++;

    if(!hasVowel(yytext))
        novowel_words++;
}

[ \t\n]+    ;      /* ignore spaces, tabs, newlines */
.           ;      /* ignore other characters */

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) {
        printf("Error opening input.txt\n");
        return 1;
    }

    yylex();
    fclose(yyin);

    printf("\n----- RESULT -----\n");
    printf("Total words              : %d\n", total_words);
    printf("Palindromic words        : %d\n", pal_words);
    printf("Words of length 4        : %d\n", len4_words);
    printf("Words with NO vowels     : %d\n", novowel_words);

    return 0;
}

int yywrap() { return 1; }
