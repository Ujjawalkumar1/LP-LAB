

%{
#include <stdio.h>

FILE *out;
int replace_count = 0;
%}

%%

"CSE"   { fprintf(out, "Dept"); replace_count++; }
"2024"  { fprintf(out, "Year"); replace_count++; }

.|\n    { fprintf(out, "%s", yytext); }

%%

int main() {
    FILE *in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    if(!in || !out) {
        printf("Error opening files\n");
        return 1;
    }

    yyin = in;
    yylex();

    fclose(in);
    fclose(out);

    printf("Replacements done = %d\n", replace_count);
    printf("Modified content written to output.txt\n");

    return 0;
}

int yywrap() { return 1; }
