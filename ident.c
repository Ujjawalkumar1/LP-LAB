#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to check if the given string is a C keyword
int isKeyword(char* str) {
    char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int kc = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < kc; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1; // It's a keyword
    }
    return 0; // Not a keyword
}

// DFA function to check valid identifier
int isValidIdentifier(char str[]) {
    int i = 0, state = 0;

    while (str[i] != '\0') {
        switch (state) {
            case 0: // Start state
                if (isalpha(str[i]) || str[i] == '_')
                    state = 1; // Valid start
                else
                    state = -1; // Invalid start
                break;

            case 1: // After first character
                if (isalnum(str[i]) || str[i] == '_')
                    state = 1; // Still valid
                else
                    state = -1; // Invalid character
                break;

            default:
                state = -1;
        }

        if (state == -1)
            break; // Stop if invalid

        i++;
    }

    return (state == 1); // 1 = Accepted, 0 = Rejected
}

int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%[^\n]%*c", str); // Read full line including spaces

    if (isKeyword(str)) {
        printf("Rejected — '%s' is a keyword.\n", str);
    } 
    else if (isValidIdentifier(str)) {
        printf("Accepted — '%s' is a valid identifier.\n", str);
    } 
    else {
        printf("Rejected — '%s' is not a valid identifier.\n", str);
    }

    return 0;
}
