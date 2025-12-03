

%{
#include <stdio.h>
%}

%%

// 10-digit Mobile Number
^[0-9]{10}$                 { printf("Valid Mobile Number\n"); }

// PAN: 5 letters + 4 digits + 1 letter
^[A-Z]{5}[0-9]{4}[A-Z]$     { printf("Valid PAN Number\n"); }

// Vehicle Number: KL-07-AB-1234
^[A-Z]{2}-[0-9]{2}-[A-Z]{2}-[0-9]{4}$   { printf("Valid Vehicle Number\n"); }

// Anything else → invalid
.*                           { printf("Invalid Input\n"); }

%%

int main() {
    printf("Enter input: ");
    yylex();
    return 0;
}

int yywrap() { return 1; }
