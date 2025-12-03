// ✅ EXP-03 – DFA for strings ending with 00


#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int state = 0;   // DFA start state: q0

    printf("Enter a binary string: ");
    scanf("%s", str);

    // Scan the string character by character
    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        switch (state) {
        case 0: // q0: start state
            if (c == '0')
                state = 1;      // seen last bit = 0
            else if (c == '1')
                state = 0;      // last bit = 1, stay in q0
            else {
                printf("input invalid\n"); // not 0 or 1
                return 1;
            }
            break;

        case 1: // q1: last bit was 0 (only one 0 at end)
            if (c == '0')
                state = 2;      // last two bits = 00 → go to q2
            else if (c == '1')
                state = 0;      // last bit becomes 1 → back to q0
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 2: // q2: last two bits were 00
            if (c == '0')
                state = 2;      // still ends in 00 (…000, still valid end)
            else if (c == '1')
                state = 0;      // new last bit 1 → back to q0
            else {
                printf("input invalid\n");
                return 1;
            }
            break;
        }
    }

    // Accept if final state is q2 (ends with 00)
    if (state == 2)
        printf("accepted\n");
    else
        printf("rejected\n");

    return 0;
}
