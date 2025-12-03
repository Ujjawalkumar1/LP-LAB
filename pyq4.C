%{
#include <stdio.h>
#include <string.h>

int count_ab = 0;          // words having one 'a' AND one 'b'
int count_len5_noa = 0;    // word length 5 and no 'a'
int count_4digit = 0;      // 4-digit numbers
int count_bbb = 0;         // words containing substring "bbb"

// helper: count occurrences of a character
int countChar(char *s, char c) {
    int cnt = 0;
    for(int i=0; s[i]; i++)
        if(s[i] == c) cnt++;
    return cnt;
}

// helper: check substring
int containsBBB(char *s) {
    return strstr(s, "bbb") != NULL;
}
%}

%%

// WORDS
[a-zA-Z]+ {
    int len = strlen(yytext);
    int a = countChar(yytext, 'a');
    int b = countChar(yytext, 'b');

    // 1) word having one 'a' and one 'b'
    if(a == 1 && b == 1)
        count_ab++;

    // 2) word length is 5 AND no 'a'
    if(len == 5 && a == 0)
        count_len5_noa++;

    // 4) string containing substring "bbb"
    if(containsBBB(yytext))
        count_bbb++;
}

// 3) count 4-digit numbers
[0-9]{4}    { count_4digit++; }

// ignore everything else
.|\n        ;

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
    printf("1) Words with exactly one 'a' and one 'b'      : %d\n", count_ab);
    printf("2) Words with length 5 and NO 'a'              : %d\n", count_len5_noa);
    printf("3) Count of 4-digit numbers                    : %d\n", count_4digit);
    printf("4) Words containing substring \"bbb\"           : %d\n", count_bbb);

    return 0;
}

int yywrap() { return 1; }
