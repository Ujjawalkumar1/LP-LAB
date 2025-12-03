

%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sentence_count = 0;
int capital_start_words = 0;
int num_gt_100 = 0;
int email_count = 0;
int lines_with_CS = 0;

char current_line[1000];
int idx = 0;
%}

%%

// Store entire line to check for "CS"
\n {
    current_line[idx] = '\0';
    if(strstr(current_line, "CS"))
        lines_with_CS++;

    idx = 0;
}

// Collect characters of current line
. {
    current_line[idx++] = yytext[0];

    // 1) Sentence ending
    if(yytext[0]=='.' || yytext[0]=='?' || yytext[0]=='!')
        sentence_count++;
}


[ ]+    ;   // ignore spaces


// 2) Word starting with capital letter
[A-Z][a-zA-Z]*   { capital_start_words++; }

// 3) Numbers > 100
[0-9]+ {
    int num = atoi(yytext);
    if(num > 100)
        num_gt_100++;
}

// 4) Email-like pattern
[a-zA-Z0-9_.]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,3} {
    email_count++;
}

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) { printf("Error opening input.txt\n"); return 1; }

    yylex();
    fclose(yyin);

    printf("\n----- RESULT -----\n");
    printf("Sentences                      : %d\n", sentence_count);
    printf("Words starting with capital    : %d\n", capital_start_words);
    printf("Numbers > 100                  : %d\n", num_gt_100);
    printf("Email-like patterns            : %d\n", email_count);
    printf("Lines containing 'CS'          : %d\n", lines_with_CS);

    return 0;
}

int yywrap() { return 1; }
