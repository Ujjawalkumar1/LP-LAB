#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ----------------------------------------------
// LIST OF KEYWORDS (these are NOT valid identifiers)
// ----------------------------------------------
const char* key[] = {
    "int", "float", "char", "if", "else",
    "while", "switch", "for", "do", "case"
};

// Count how many keywords are in the list
int kc = sizeof(key) / sizeof(key[0]);

// --------------------------------------------------
// FUNCTION: DFA to check VALID IDENTIFIER
// --------------------------------------------------
// Rules for valid identifier:
// 1. First character: letter or underscore
// 2. Other characters: letters, digits, underscore
// --------------------------------------------------
int dfa_accepts_string(const char* input) {

    int state = 0;  // Start state q0

    // Scan each character of input
    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];

        switch (state) {

        // -------------------------
        // q0 → first character rule
        // -------------------------
        case 0:
            // First character must be A-Z, a-z or _
            if (isalpha(c) || c == '_')
                state = 1;   // move to valid state
            else
                return 0;    // reject immediately
            break;

        // -------------------------
        // q1 → remaining characters
        // -------------------------
        case 1:
            // After the first character → letters, digits, underscore allowed
            if (isalnum(c) || c == '_')
                state = 1;   // stay in q1
            else
                return 0;    // invalid character → reject
            break;
        }
    }

    // If we end in state 1, it's a valid identifier
    return (state == 1);
}

// --------------------------------------------------
// FUNCTION: Check if input is a keyword
// --------------------------------------------------
int iskey(const char* input) {

    // Compare input with each keyword
    for (int i = 0; i < kc; i++) {
        if (strcmp(input, key[i]) == 0)
            return 1;   // Yes, it is a keyword
    }

    return 0;   // Not a keyword
}

// --------------------------------------------------
// MAIN FUNCTION
// --------------------------------------------------
int main() {

    char input[200];

    // Take input string
    printf("Enter a string: ");
    scanf("%[^\n]%*c", input);  // read full line including underscores

    // ------------- Check for keyword -------------
    if (iskey(input)) {
        printf("The string '%s' is a keyword → REJECTED\n", input);
        return 0;
    }

    // ------------- Run DFA -------------
    if (dfa_accepts_string(input)) {
        printf("The string '%s' is a VALID IDENTIFIER → ACCEPTED\n", input);
    } 
    else {
        printf("The string '%s' is NOT a valid identifier → REJECTED\n", input);
    }

    return 0;
}
