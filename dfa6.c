
// ✅ **EXP-09 – Strings with NO “101” substring




#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int state = 0;   // q0 = start

    printf("Enter a binary string: ");
    scanf("%s", str);

    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        switch (state) {

        case 0: // q0
            if (c=='0')
                state = 0;      // still safe
            else if (c=='1')
                state = 1;      // possible start of 101
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 1: // q1: saw '1', expecting '0'
            if (c=='0')
                state = 2;      // saw "10"
            else if (c=='1')
                state = 1;      // "11" still okay
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 2: // q2: saw "10", expecting '1'
            if (c=='0')
                state = 0;      // "100" does NOT form 101 (safe)
            else if (c=='1')
                state = 3;      // saw "101" → go to trap state
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 3: // q3 = TRAP state because "101" found
            if (c=='0' || c=='1')
                state = 3;      // permanently stuck
            else {
                printf("input invalid\n");
                return 1;
            }
            break;
        }
    }

    // Accept if we never reached trap state q3
    if (state == 0 || state == 1 || state == 2)
        printf("accepted\n");
    else
        printf("rejected\n");

    return 0;
}
