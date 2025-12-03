
// ✅ EXP-07 – Detect “abc” substring


#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int state = 0;   // start at q0

    printf("Enter a string: ");
    scanf("%s", str);

    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        switch (state) {

        case 0: // q0: looking for first 'a'
            if (c == 'a')
                state = 1;       // found 'a'
            else if (c == 'b' || c == 'c')
                state = 0;       // still haven't started "abc"
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 1: // q1: we have seen 'a', now expecting 'b'
            if (c == 'a')
                state = 1;       // still seeing 'a', stay in q1
            else if (c == 'b')
                state = 2;       // correct next char after 'a'
            else if (c == 'c')
                state = 0;       // reset because "ac" breaks pattern
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 2: // q2: we saw "ab", now expecting 'c'
            if (c == 'a')
                state = 1;       // restart pattern
            else if (c == 'b')
                state = 0;       // "abb" break → restart
            else if (c == 'c')
                state = 3;       // "abc" found!
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 3: // q3: substring "abc" FOUND → trap accepting state
            if (c=='a' || c=='b' || c=='c')
                state = 3;       // remain accepted
            else {
                printf("input invalid\n");
                return 1;
            }
            break;
        }
    }

    if (state == 3)
        printf("accepted\n");    // “abc” appeared in the string
    else
        printf("rejected\n");

    return 0;
}
