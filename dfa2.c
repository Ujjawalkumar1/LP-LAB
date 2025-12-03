// ✅ EXP-04 – DFA for “00 followed by 1”

#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int state = 0;  // start state q0

    printf("Enter a binary string: ");
    scanf("%s", str);

    // Process each character
    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        switch (state) {
        case 0: // q0
            if (c == '0')
                state = 1;   // saw first 0
            else if (c == '1')
                state = 0;   // stay in q0 on 1
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 1: // q1: last bit was 0
            if (c == '0')
                state = 2;   // now we have 00
            else if (c == '1')
                state = 0;   // 01 → back to q0
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 2: // q2: just saw 00
            if (c == '0')
                state = 3;   // 000 → go to trap-like state q3
            else if (c == '1')
                state = 0;   // 001 → back to q0
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 3: // q3: trap state (after 000)
            if (c == '0')
                state = 3;   // stay in trap
            else if (c == '1')
                state = 3;   // stay in trap
            else {
                printf("input invalid\n");
                return 1;
            }
            break;
        }
    }

    // Accepting states are 0 and 1 (as in original code)
    if (state == 0 || state == 1)
        printf("accepted\n");
    else
        printf("rejected\n");

    return 0;
}
