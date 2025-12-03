
// ✅ 9️⃣ Lex Program – Pattern Matching

// 👉 Count:

// Strings containing “aaa”

// Strings containing exactly two 'b'

// Strings ending with "ing"

// Total matched strings








%{
#include <stdio.h>
#include <string.h>

int contain_aaa = 0;
int two_b = 0;
int end_ing = 0;
int total = 0;

// count occurrences of a character
int countChar(char *s, char c) {
    int cnt = 0;
    for(int i=0; s[i]; i++)
        if(s[i] == c) cnt++;
    return cnt;
}
%}

%%

// WORDS only
[a-zA-Z]+ {
    total++;

    // contains "aaa"
    if(strstr(yytext, "aaa"))
        contain_aaa++;

    // contains exactly two 'b'
    if(countChar(yytext, 'b') == 2)
        two_b++;

    // ends with "ing"
    int len = strlen(yytext);
    if(len >= 3 &&
       yytext[len-3]=='i' &&
       yytext[len-2]=='n' &&
       yytext[len-1]=='g')
        end_ing++;
}

// ignore all else
[ \t\n]+     ;
.            ;

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) { printf("Error opening input\n"); return 1; }

    yylex();
    fclose(yyin);

    printf("\n----- RESULT -----\n");
    printf("Strings containing 'aaa'        : %d\n", contain_aaa);
    printf("Strings with exactly two 'b'    : %d\n", two_b);
    printf("Strings ending with 'ing'       : %d\n", end_ing);
    printf("Total strings                   : %d\n", total);

    return 0;
}

int yywrap() { return 1; }
