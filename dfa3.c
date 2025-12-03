
// ✅ EXP-05 – DFA for 1* 2* 3* string



#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    char choice;

    do {
        int state = 0;    // DFA state: 0 = 1*, 1 = 2*, 2 = 3*
        int valid = 1;    // assume valid until proven otherwise

        printf("Enter a string: ");
        scanf("%s", input);

        // Check each character of input
        for (int i = 0; i < strlen(input); i++) {
            char ch = input[i];

            // First, only allow characters 1, 2, 3
            if (ch != '1' && ch != '2' && ch != '3') {
                valid = 0;     // invalid character
                break;
            }

            switch (state) {
            case 0: // In 1* region
                if (ch == '1')
                    state = 0; // still in 1*
                else if (ch == '2')
                    state = 1; // move to 2* region
                else            // ch == '3'
                    state = 2; // directly to 3* region (no 2s)
                break;

            case 1: // In 2* region
                if (ch == '2')
                    state = 1; // still in 2*
                else if (ch == '3')
                    state = 2; // move to 3* region
                else           // ch == '1' → cannot go back to 1*
                    valid = 0;
                break;

            case 2: // In 3* region
                if (ch == '3')
                    state = 2; // continue in 3*
                else           // cannot see 1 or 2 after 3
                    valid = 0;
                break;
            }

            // if already invalid, break early
            if (!valid)
                break;
        }

        if (valid)
            printf("Accepted\n");
        else {
            printf("Rejected.\n");
            break;   // exit the loop if invalid string given
        }

        printf("Continue ? (y/n): ");
        scanf(" %c", &choice);   // note the space before %c to eat newline

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
