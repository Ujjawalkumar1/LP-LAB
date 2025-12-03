#include <stdio.h>
#include <string.h>
#include <ctype.h>

// list of some C keywords (you can write fewer if you want)
char key[][10] = {"int","float","char","if","else","while","for","do","case","return"};
int kc = 10;   // number of keywords

int isKeyword(char *s) {
    for (int i = 0; i < kc; i++) {
        if (strcmp(s, key[i]) == 0)
            return 1;   // it is a keyword
    }
    return 0;           // not a keyword
}

// DFA to check valid identifier
int dfa_valid_identifier(char *s) {
    int state = 0;   // 0 = start, 1 = valid, 2 = dead

    if (s[0] == '\0')   // empty string
        return 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        switch (state) {
        case 0: // first character
            if (isalpha(c) || c == '_')
                state = 1;
            else
                return 0;   // invalid first char
            break;

        case 1: // remaining characters
            if (isalnum(c) || c == '_')
                state = 1;  // stay valid
            else
                return 0;   // invalid char
            break;
        }
    }

    return (state == 1);
}

int main() {
    char input[100];

    printf("Enter a string: ");
    scanf("%s", input);   // simple input (no spaces)

    // check keyword first
    if (isKeyword(input)) {
        printf("'%s' is a KEYWORD → REJECTED\n", input);
    }
    else if (dfa_valid_identifier(input)) {
        printf("'%s' is a VALID IDENTIFIER → ACCEPTED\n", input);
    }
    else {
        printf("'%s' is NOT a valid identifier → REJECTED\n", input);
    }

    return 0;
}
